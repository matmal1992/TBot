import yfinance as yf

# Define the ticker symbol for US500
ticker = "^GSPC"  # S&P 500 index (similar to US500)

# Download data for the last 7 days (1-minute intervals)
df = yf.download(ticker, period="7d", interval="1m")

# Extract only the "Close" price and round to 2 decimal places
prices = df[['Close']].round(2)

# Save to CSV
prices.to_csv("testing_data/US500_prices.csv", header=["Price"])

print("Data saved successfully!")
print(prices.head())  # Show first few rows
