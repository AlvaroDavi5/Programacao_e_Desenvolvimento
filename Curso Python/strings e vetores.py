texto = "Meu nome é Álvaro"
# isso é uma string, mas em Python uma string é um vetor de caracteres

# logo, podemos separar as strings por índices
print(texto[0])
print(texto[11])
print(texto[12])
print(texto[3])
print(texto[4])

# fatiamento, ou 'slicing', para iniciar um vetor apartir de dado index
print(texto[3:]) # inclusivo (inclui a posição 3)
print(texto[:3]) # exclusivo (exclui a posição 3)

print(texto[0] * 3) # repete uma string ou caractere
print(texto.lower()) # para tornar string minúscula
print(texto.upper()) # para maiúscula
print(texto.split()) # divide uma string, como nada foi passado como parâmetro, ela divide por espaços em branco
print(texto.split('a')) # fragmenta/divide por cada 'a' na string
print (texto.count('e')) # conta quantidade de 'e'
print (texto.find('o')) # procura a primeira letra 'o' e retorna seu índice