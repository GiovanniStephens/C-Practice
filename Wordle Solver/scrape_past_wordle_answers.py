"""
Python script to scrape past wordle answers
from the wordle website.

Author: Giovanni Stephens
Date:   11/05/2022
"""
from bs4 import BeautifulSoup
import requests
import pandas as pd

WORDLE_URL = 'https://game8.co/games/Wordle/archives/369779'

def main():
    # Get the html from the wordle website
    html = requests.get(WORDLE_URL).text
    # Parse the html
    soup = BeautifulSoup(html, 'html.parser')
    # Get the second table of class a-table a-table a-table 
    table = soup.find_all('table', class_='a-table a-table a-table')[1]
    # Get the table rows
    rows = table.find_all('tr')
    # Create a list to store the data
    data = []
    # Loop through the rows
    for row in rows:
        # Get the cells
        cells = row.find_all('td')
        # Create a list to store the cells
        row_data = []
        # Loop through the cells
        for cell in cells:
            # Get the text
            text = cell.get_text()
            # Add the text to the list
            row_data.append(text)
        # Add the list to the data list
        data.append(row_data)

    columns = ['No.', 'Answer', 'Date']
    # Create a dataframe from the data
    df = pd.DataFrame(data, columns=columns)
    # Remove the first row
    df = df.drop(0)
    # Save the dataframe to a csv file
    df.to_csv('wordle_answers.csv', index=False)


if __name__ == '__main__':
    main()
