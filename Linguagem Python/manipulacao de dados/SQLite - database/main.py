import os
import sqlite3

os.remove("dsa.db") if os.path.exists("dsa.db") else None

conn = sqlite3.connect("dsa.db")
c = conn.cursor()

def createTable():
	c.execute("CREATE TABLE IF NOT EXISTS produtos(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, date TEXT, prod_name TEXT, valor REAL)")

def dataInsert():
	c.execute("INSERT INTO produtos VALUES(10, 2018-05-02 14:32:12, 'Teclado', 90)")
	conn.commit()
	c.close()
	conn.close()

createTable()
dataInsert()
