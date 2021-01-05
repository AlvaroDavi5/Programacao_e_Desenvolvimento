"""

OBJETOS = elemento computacional que representa alguma entidade (abstrata ou concreta)
CLASSES = estrutura que abstrai um conjunto de objetos com caracteristicas similares, define o comportamento de seus objetos - atraves de metodos - e os estados possiveis destes objetos - atraves de atributos

ATRIBUTOS = elementos que definem a estrutura de uma classe
INSTANCIAS = um objeto cujo comportamento e estado sao definidos pela classe
METODOS = funcao associada de uma classe

MENSAGEM = chamada a um objeto para invocar um de seus metodos
HERANCA = mecanismo que permite a uma subclasse extender uma superclasse aproveitado seus atributos e metodos herdados
POLIMORFISMO = propriedade de duas ou mais classes derivadas de uma mesma superclasse responderem a mesma mensagem, cada uma de uma forma diferente
ENCAPSULAMENTO = encapsular os dados de uma aplicacao significa evitar que estes sofram acessos indevidos. Para isso, e criada uma estrutura que contem metodos que podem ser utilizados por qualquer outra classe, sem causar inconsistências no desenvolvimento de um codigo

"""


# isto e uma classe
class Livro(): # para receber parametros usa-se parenteses

	def __init__(self, isbn): # funcao (ou metodo, por estar dentro da classe) para inicializar cada objeto criado a partir desta classe
		# esses sao atributos
		self.nome = ""
		self.genero = "" # 'self' referencia cada atributo de um objeto criado a partir dessa classe
		self.ano = 0
		self.isbn = isbn

	def info(self): # metodos sao funcoes que recebem como parametro atributos do objeto criado
		print("LIVRO: %s \nGENERO: %s \nANO LANCA.: %s \nISBN: %s \n" %(self.nome, self.genero, self.ano, self.isbn)) # mostrar informacoes sobre objeto



# isto e um objeto (instancia)
livro1 = Livro(9780671577216) # instanciando classe 'Livro()' ao criar objeto 'livro1' na classe e passando parametro isbn

livro1.ano = 1912
livro1.nome = "O Mundo Perdido" # definindo valores dos atributos do objeto
livro1.genero = "ficção/fantasia"
print(str(type(livro1)) + '\n')



# isto e um metodo
livro1.info()



#
