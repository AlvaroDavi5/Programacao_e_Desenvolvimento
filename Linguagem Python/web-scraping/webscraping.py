import requests # make requests of HTML file to server
import pandas as pd # to databases and data manipulation functions
from bs4 import Beautifulsoup # extract data from HTML file
from selenium import webdriver # do autotests on browser
from selenium.webdriver.firefox.options import Options
import json # manipulate JSON files

''' get HTML content '''

URL = 'https://www.kabum.com.br/hardware/placa-de-video-vga'

''' save content in a data structure '''
''' show results '''
