import time # timeset library
import requests # make requests of HTML file to server
import pandas as pd # to databases and data manipulation functions
from bs4 import BeautifulSoup # extract data from HTML file
from selenium import webdriver # do autotests on browser
from selenium.webdriver.opera.options import Options # opera webdriver options

import json # manipulate JSON files

''' get HTML content '''

url = "https://www.nba.com/stats/players/traditional/?sort=PLAYER_NAME&dir=-1" # NBA tabledata URL

option = Options()
option.headless = True

driver = webdriver.Opera() # call the webdriver to open the browser and get the URL		options=option
driver.get(url)
driver.quit()

''' save content in a data structure '''

''' show results '''
