import pyautogui
import pytesseract
from PIL import Image, ImageEnhance, ImageOps
import time
import csv
from datetime import datetime

pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"

# === Region of the BUY button (x, y, width, height) ===
PRICE_REGION = (830, 260, 80, 60)

CSV_FILE = "us500_prices.csv"

start_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
with open(CSV_FILE, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Prices", f"Start Time: {start_time}"])

print("📈 Logging US500 prices (price only)...")
print(f"📅 Start Time: {start_time}")
print("✅ Press Ctrl+C to stop\n")

try:
    while True:
        screenshot = pyautogui.screenshot(region=PRICE_REGION)

        width, height = screenshot.size
        price_area = screenshot.crop((0, height // 2, width, height))

        gray = ImageOps.grayscale(price_area)
        enhancer = ImageEnhance.Contrast(gray)
        processed = enhancer.enhance(2.0)

        price_text = pytesseract.image_to_string(
            processed,
            config='--psm 7 -c tessedit_char_whitelist=0123456789.,'
        ).strip()

        cleaned_price = price_text.replace(',', '.')
        cleaned_price = ''.join(c for c in cleaned_price if c in '0123456789.')

        with open(CSV_FILE, mode='a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([cleaned_price])

        print(f" Price: {cleaned_price}")
        time.sleep(1)

except KeyboardInterrupt:
    end_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open(CSV_FILE, mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([f"End Time: {end_time}"])

    print(f"\n⏹️ Logging stopped.")
    print(f"📅 End Time: {end_time}")
