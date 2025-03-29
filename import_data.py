import yfinance as yf

# Define the ticker symbol for US500
ticker = "^GSPC"  # S&P 500 index (similar to US500)

# Download minute-level data for the last 7 days
df = yf.download(ticker, period="7d", interval="1m")

# Save to CSV file
df.to_csv("US500_price_data.csv")

print("Data saved successfully!")
print(df.head())  # Show first few rows
