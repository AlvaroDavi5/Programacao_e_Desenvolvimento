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
		"(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, date TEXT, prod_name TEXT, value REAL)"
	)

def dataInsert():
	c.execute("INSERT INTO produtos VALUES(10, '2018-05-02 14:32:12', 'Teclado', 90)")
	conn.commit()

def data_insert_var():
	new_date = datetime.now()
	new_prod_name = 'Placa de Vídeo'
	new_value = random.randrange(300, 900)
	c.execute("INSERT INTO produtos (date, prod_name, value) VALUES (?, ?, ?)", (new_date, new_prod_name, new_value))
	conn.commit()

def read_all_data():
	c.execute("SELECT * FROM produtos")
	for row in c.fetchall():
		print(row)

def read_specific_data():
	c.execute("SELECT * FROM produtos WHERE value > 400.00")
	for row in c.fetchall():
		print(row)

def read_specific_column(col_num):
	c.execute("SELECT * FROM produtos")
	for row in c.fetchall():
		print(row[col_num])

def update_value():
	c.execute("UPDATE produtos SET value = 500.50 WHERE value < 400.00")
	conn.commit()

def main():
	createTable()

	dataInsert()
	for i in range(5):
		data_insert_var()

	print("\nTodos os Produtos:\n")
	read_all_data()
	print("\nProdutos Acima de R$ 400,00:\n")
	read_specific_data()
	print("\nTipos de Produtos:\n")
	read_specific_column(2)
	update_value()
	read_specific_data()

	c.close()
	conn.close()


if __name__ == '__main__':
	main()
