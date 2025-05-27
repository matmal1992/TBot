import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('test.csv', header=None, names=['Price'])

df['SMA_5'] = df['Price'].rolling(window=5).mean()
df['SMA_15'] = df['Price'].rolling(window=15).mean()
df['SMA_60'] = df['Price'].rolling(window=60).mean()

plt.figure(figsize=(12, 6))
plt.plot(df['Price'], label='Bitcoin Price', color='blue')

plt.plot(df['SMA_5'], label='5-Point SMA', color='orange')
plt.plot(df['SMA_15'], label='15-Point SMA', color='green')
plt.plot(df['SMA_60'], label='60-Point SMA', color='red')

plt.title('Bitcoin Price with 5- and 15-Point Moving Averages')
plt.xlabel('Time (Index)')
plt.ylabel('Price')
plt.legend()
plt.grid(True)

plt.show()
