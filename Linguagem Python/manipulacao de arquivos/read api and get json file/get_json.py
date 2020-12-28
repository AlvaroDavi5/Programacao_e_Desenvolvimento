"""

Used API:

http://servicodados.ibge.gov.br/api/v1/publicacoes/{produto}

"""

import requests # make requests of web pages
import fileinput # manipule file inputs
import unicodedata # unicode convert data
from fpdf import FPDF # generate pdf fine
import json # to manipule json files

produto = str(input("Digite uma palavra chave para buscar uma publicação: \n"))

try:
	filename = produto + "_pubs_ibge.json"

	file = open(filename, "w")

	request = requests.get("http://servicodados.ibge.gov.br/api/v1/publicacoes/{}".format(produto)) # request data from IBGE Publications API

	content = json.dumps(request.json())
	content = str(content.encode('utf-8').decode('ascii', 'ignore'))
	file.write(content)

	file.close()
	print("Dados obtidos e arquivo criado!")

except:
	print("Erro ao obter dados e criar arquivo!")
