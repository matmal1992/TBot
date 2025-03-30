import time
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options

# Function to get Bitcoin price from XTB
def get_bitcoin_price():
    chrome_options = Options()
    chrome_options.add_argument("--headless")
    chrome_options.add_argument("--disable-gpu")
    chrome_options.add_argument("--no-sandbox")
    
    service = Service("C:\\chromedriver\\chromedriver.exe")  # Replace with your ChromeDriver path
    driver = webdriver.Chrome(service=service, options=chrome_options)
    
    try:
        driver.get("https://www.xtb.com")  # Adjust the URL if necessary
        time.sleep(5)  # Allow time for the page to load
        time.sleep(5)  # Let the page load
        print(driver.page_source)  # Print the entire HTML


    
        
        # Locate the Bitcoin price element (Update selector based on actual page structure)
        price_element = driver.find_element(By.CSS_SELECTOR, "//div[@class='btc-price']")
        btc_price = float(price_element.text.replace(",", ""))  # Convert to float
        
        print(f"Current BTC Price: ${btc_price}")
        driver.quit()
        return btc_price
    except Exception as e:
        print("Error getting Bitcoin price:", e)
        driver.quit()
        return None

# Function to write BTC price to a file
def write_price_to_file():
    btc_price = get_bitcoin_price()
    if btc_price:
        with open("btc_price.txt", "a") as file:
            file.write(f"{time.strftime('%Y-%m-%d %H:%M:%S')} - BTC Price: ${btc_price}\n")
        print("Price written to file.")

# Run the bot continuously every 10 seconds
while True:
    write_price_to_file()
    time.sleep(10)
