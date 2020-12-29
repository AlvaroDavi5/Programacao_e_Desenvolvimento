"""

APIs e Datasets:

https://data.cityofchicago.org/Administration-Finance/Current-Employee-Names-Salaries-and-Position-Title/xzkq-xp2w

Tutoriais:

https://pyfpdf.readthedocs.io/en/latest/
https://github.com/reingart/pyfpdf
https://github.com/filipeaguilardeveloper/python-gerando-pdf

"""

import requests # biblioteca para requisicoes de paginas web
from fpdf import FPDF # biblioteca para gerar e tratar arquivos PDF
import json

unidade_federativa = input("Digite apenas a sigla da Unidade Federativa a qual se deseja obter os dados dos distritos: ")
if len(unidade_federativa) != 2:
	print("UF inválida!")
	exit()

datalist = requests.get("https://servicodados.ibge.gov.br/api/v1/localidades/estados/{}/distritos".format(unidade_federativa))
datalist = datalist.json()
print(datalist)

pdf = FPDF() # classe para gerar pdf

def layoutPagina(arqPDF):
	arqPDF.image("./IBGE.png",  link='', type='', w=1586/80, h=1920/80) # adiciona imagem

def defineTitulo(arqPDF):
	arqPDF.set_font("Helvetica", 'B', 18) # seleciona fonte do titulo
	arqPDF.set_text_color(178, 34, 34)
	arqPDF.cell(50, 10, "Relatorio")

def inserirTexto(arqPDF):
	arqPDF.set_font("Arial", 'B', 16) # seleciona fonte do texto
	arqPDF.set_text_color(0, 0, 0)
	arqPDF.cell(70, 67, "Teste")


pdf.add_page() # adiciona pagina
layoutPagina(pdf)
defineTitulo(pdf)
inserirTexto(pdf)
pdf.output('relatorio.pdf', 'F') # cria arquivo com o que foi definido previamente
