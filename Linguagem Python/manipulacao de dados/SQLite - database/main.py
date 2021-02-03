import os
from datetime import datetime
import time
import random
import sqlite3

os.remove("dsa.db") if os.path.exists("dsa.db") else None

conn = sqlite3.connect("dsa.db")
c = conn.cursor()

def createTable():
	c.execute(
		"CREATE TABLE IF NOT EXISTS produtos" \
		"(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, date TEXT, prod_name TEXT, valor REAL)"
	)

def dataInsert():
	c.execute("INSERT INTO produtos VALUES(10, '2018-05-02 14:32:12', 'Teclado', 90)")
	conn.commit()

def data_insert_var():
	new_date = datetime.now()
	new_prod_name = 'Placa de Vídeo'
	new_valor = random.randrange(300, 900)
	c.execute("INSERT INTO produtos (date, prod_name, valor) VALUES (?, ?, ?)", (new_date, new_prod_name, new_valor))
	conn.commit()

# finalizacao
createTable()
dataInsert()
for i in range(5):
	data_insert_var()
c.close()
conn.close()
