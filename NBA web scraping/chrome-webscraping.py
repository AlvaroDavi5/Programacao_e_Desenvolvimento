import time # timeset library
from datetime import datetime # datetime consult library
import requests # make requests of HTML file to server
import pandas as pd # to databases and data manipulation functions
from bs4 import BeautifulSoup # extract data from HTML file
from selenium import webdriver # do autotests on browser
# simulate clicks and typing
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.select import Select # verify if tag is a 'select'
from selenium.webdriver.support.ui import WebDriverWait # makes webdrive wait page load
from selenium.webdriver.support import expected_conditions as ec # verify if expected conditions is valid
from selenium.webdriver.chrome.options import Options # chrome webdriver options
from webdriver_manager.chrome import ChromeDriverManager # chrome webdriver manager
import json # manipulate JSON files
from xhtml2pdf import pisa # to build PDF with HTML



""" get HTML content """

url = "https://www.nba.com/stats/players/traditional/?sort=PLAYER_NAME&dir=-1" # NBA tabledata URL

webdrive_path = './webdrive/chromedriver'

driver = webdriver.Chrome() # call the webdriver to open the browser and get the URL
#driver = webdriver.Chrome(webdrive_path) # call the webdriver - using bin/exe program file - to open the browser and get the URL
driver.get(url)
time.sleep(10) # delay do get data

driver.find_element_by_xpath("//div[@class='nba-stat-table']//table//thead//tr//th[@data-field='PTS']").click() # emulate click to sort by poits
element = driver.find_element_by_xpath("//div[@class='nba-stat-table']//table")

html_content = element.get_attribute("outerHTML") # html table content



""" parse to BS4 HTML structure """

soup = BeautifulSoup(html_content, features='lxml')

table = soup.find(name='table')



""" save content in a PD dataframe """

df_full = pd.read_html(str(table))[0].head(10)
df = df_full[['Unnamed: 0', 'PLAYER', 'TEAM', 'PTS']]
df.columns = ['pos', 'player', 'team', 'total']



""" save content in Python list """

top10ranking = {}
top10ranking['points'] = df.to_dict('records')

driver.quit()



""" save results in a JSON """

js = json.dumps(top10ranking)

fp = open('ranking.json', 'w')
fp.write(js)
fp.close()



""" export PDF """

source = "<link rel='stylesheet' href='./pdf_style.css'>"
source += "<h1>Top 10 Ranking</h1>" + "<br>"
source += df.to_html()

pdf_file = open("table-players.pdf", "w+b")

pisa_status = pisa.CreatePDF(src=source, dest=pdf_file)

pdf_file.close()
