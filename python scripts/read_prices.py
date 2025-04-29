import pandas as pd
import numpy as np

# Load the CSV file
df = pd.read_csv("testing_data/US500_prices.csv")

# Extract the "Price" column (assuming it's named "Price" in the CSV)
prices = df["Price"].tolist()

# Calculate the average price
average_price = np.mean(prices)

print(f"Average Price: {average_price:.2f}")
