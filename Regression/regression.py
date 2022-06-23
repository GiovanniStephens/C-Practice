# import a linear regressor
import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
# import the statsmodels pacf
from statsmodels.tsa.stattools import pacf 

def main():
    # read in the data
    df = pd.read_csv('BTC-USD.csv')
    # Calculate returns
    df['Returns'] = df['Adj Close'].pct_change()

    # Make df with returns and 5 lagged return series
    df['Returns_lag1'] = df['Returns'].shift(1)
    # df['Returns_lag2'] = df['Returns'].shift(2)
    # df['Returns_lag3'] = df['Returns'].shift(3)
    # df['Returns_lag4'] = df['Returns'].shift(4)
    # df['Returns_lag5'] = df['Returns'].shift(5)

    # Drop nans
    df = df.dropna()

    # Make a timer
    import time
    start = time.time()
    reg = LinearRegression()
    
    # regress lags vs returns
    # reg.fit(df[['Returns_lag1', 'Returns_lag2', 'Returns_lag3', 'Returns_lag4', 'Returns_lag5']], df['Returns'])
    reg.fit(df[['Returns_lag1']], df['Returns'])
    
    print('Time: \n', time.time() - start)
    
    # print the coefficients
    print('Coefficients: \n', reg.coef_)
    # print the intercept
    print('Intercept: \n', reg.intercept_)


if __name__ == '__main__':
    main()