import smtplib, ssl
from email.message import EmailMessage

SMTP_HOST = "smtp.gmail.com"
SMTP_PORT = 587
SMTP_USER = "nemezis.wma@gmail.com"
SMTP_PASS = "awrcnhldrzyazyil"

msg = EmailMessage()
msg["From"] = SMTP_USER
msg["To"] = SMTP_USER
msg["Subject"] = "Test z Pythona"
msg.set_content("Działa!")

context = ssl.create_default_context()
with smtplib.SMTP(SMTP_HOST, SMTP_PORT) as server:
    server.ehlo()
    server.starttls(context=context)
    server.ehlo()
    server.login(SMTP_USER, SMTP_PASS)
    server.send_message(msg)

print("OK, wysłano testowego maila")
