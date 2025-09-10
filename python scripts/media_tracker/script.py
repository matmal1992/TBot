#!/usr/bin/env python3
"""
crypto_news_monitor.py
Monitoruje RSS/strony pod kątem newsów o kryptowalutach i wysyła e-mail alerty.
Uruchom w środowisku z .env skonfigurowanym.
"""

import asyncio
import logging
import sqlite3
import time
import os
from dataclasses import dataclass
from typing import List, Optional
import ssl
import smtplib
from email.message import EmailMessage

import aiohttp
import feedparser
from bs4 import BeautifulSoup
from dotenv import load_dotenv
import aioschedule as schedule
import aiofiles

# --- load config ---
load_dotenv()
SMTP_HOST = os.getenv("SMTP_HOST")
SMTP_PORT = int(os.getenv("SMTP_PORT", "465"))
SMTP_USER = os.getenv("SMTP_USER")
SMTP_PASS = os.getenv("SMTP_PASS")
ALERT_TO = os.getenv("ALERT_TO")
ALERT_FROM = os.getenv("ALERT_FROM", SMTP_USER)
POLL_INTERVAL = int(os.getenv("POLL_INTERVAL", "300"))
DB_PATH = os.getenv("DB_PATH", "news_monitor.db")

# --- logging ---
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s %(levelname)s %(message)s"
)
logger = logging.getLogger("crypto-monitor")

# --- sources (RSS or pages) ---
RSS_SOURCES = [
    # przykładowe RSS - możesz dodać/zmienić
    "https://www.coindesk.com/arc/outboundfeeds/rss/",
    "https://cointelegraph.com/rss",
    "https://www.reuters.com/markets/cryptocurrencies/rss",
    "https://www.theblock.co/feed",
]
# możesz dodać też bezpośrednie linki do stron które będziesz scrapować

# --- keywords + weights (prosty scoring) ---
KEYWORDS = {
    "bitcoin": 5,
    "btc": 4,
    "ethereum": 4,
    "eth": 3,
    "sec": 4,
    "etf": 5,
    "regulation": 4,
    "regulacja": 4,
    "zakaz": 4,
    "ban": 4,
    "china": 3,
    "trump": 3,
    "biden": 2,
    "hack": 5,
    "ftx": 5,
    "binance": 4,
    "tesla": 2,
    "microstrategy": 3,
}

SCORE_THRESHOLD = 4  # minimalny wynik aby wysłać alert

# --- DB utilities ---
def init_db():
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    c.execute("""
    CREATE TABLE IF NOT EXISTS seen (
        id TEXT PRIMARY KEY,
        title TEXT,
        url TEXT,
        fetched_at INTEGER
    )
    """)
    conn.commit()
    conn.close()

def mark_seen(item_id: str, title: str, url: str):
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    c.execute("INSERT OR IGNORE INTO seen (id,title,url,fetched_at) VALUES (?,?,?,?)",
              (item_id, title, url, int(time.time())))
    conn.commit()
    conn.close()

def is_seen(item_id: str) -> bool:
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    c.execute("SELECT 1 FROM seen WHERE id = ?", (item_id,))
    found = c.fetchone() is not None
    conn.close()
    return found

# --- email sending ---
def send_email(subject: str, body: str):
    msg = EmailMessage()
    msg["From"] = ALERT_FROM
    msg["To"] = ALERT_TO
    msg["Subject"] = subject
    msg.set_content(body)

    context = ssl.create_default_context()
    with smtplib.SMTP_SSL(SMTP_HOST, SMTP_PORT, context=context) as server:
        server.login(SMTP_USER, SMTP_PASS)
        server.send_message(msg)
    logger.info("Wysłano e-mail: %s", subject)

# --- scoring function ---
def score_text(text: str) -> int:
    t = text.lower()
    score = 0
    for k, w in KEYWORDS.items():
        if k in t:
            score += w
    return score

# --- fetch and process RSS feeds ---
async def fetch(session: aiohttp.ClientSession, url: str) -> Optional[str]:
    try:
        async with session.get(url, timeout=30) as resp:
            if resp.status == 200:
                return await resp.text()
            else:
                logger.warning("Fetch %s -> status %s", url, resp.status)
                return None
    except Exception as e:
        logger.exception("Błąd pobierania %s: %s", url, e)
        return None

async def process_rss(session: aiohttp.ClientSession, url: str):
    logger.debug("Pobieram RSS: %s", url)
    text = await fetch(session, url)
    if not text:
        return
    feed = feedparser.parse(text)
    for entry in feed.entries:
        # unikaj pustych pól
        link = entry.get("link") or entry.get("id") or ""
        if not link:
            continue
        uid = link
        title = entry.get("title", "")[:300]
        summary = (entry.get("summary") or entry.get("description") or "")[:2000]
        combined = f"{title}\n\n{summary}"
        if is_seen(uid):
            continue
        sc = score_text(combined)
        logger.info("Nowy wpis: %s | score=%s", title, sc)
        if sc >= SCORE_THRESHOLD:
            # wyślij alert e-mail
            body = f"Tytuł: {title}\nLink: {link}\nScore: {sc}\n\nFragment:\n{summary}"
            try:
                send_email(f"[Crypto ALERT] {title}", body)
            except Exception as e:
                logger.exception("Błąd wysyłania emaila: %s", e)
        # oznacz jako przeczytane bez względu na score, żeby nie spamować
        mark_seen(uid, title, link)

# --- (opcjonalne) fetch article content to improve detection ---
async def fetch_article_text(session: aiohttp.ClientSession, url: str) -> str:
    txt = await fetch(session, url)
    if not txt:
        return ""
    soup = BeautifulSoup(txt, "html.parser")
    # heurystyka: zebrać paragrafy
    paragraphs = [p.get_text(separator=" ", strip=True) for p in soup.find_all("p")]
    return "\n".join(paragraphs)[:4000]

# --- main job ---
async def job():
    logger.info("Start job: pobieranie RSS...")
    async with aiohttp.ClientSession() as session:
        tasks = [process_rss(session, u) for u in RSS_SOURCES]
        await asyncio.gather(*tasks, return_exceptions=True)
    logger.info("Job zakończony.")

# --- scheduler loop using aioschedule ---
async def scheduler_loop():
    schedule.every(POLL_INTERVAL).seconds.do(lambda: asyncio.create_task(job()))
    # immediately run once
    asyncio.create_task(job())
    while True:
        await schedule.run_pending()
        await asyncio.sleep(1)

# --- entrypoint ---
def main():
    init_db()
    try:
        asyncio.run(scheduler_loop())
    except KeyboardInterrupt:
        logger.info("Zatrzymano ręcznie.")

if __name__ == "__main__":
    main()
