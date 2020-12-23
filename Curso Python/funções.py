import math # funcao pronta da biblioteca math

def potenciacao(num, expo): # definição de função
	i = 0
	res = num
	while i < expo-1:
		res *= num
		i += 1
	return res


# função principal

numero = int(input("digite um número: "))
potencia = int(input("digite um expoente: "))

result = potenciacao(numero, potencia)
print("Resultado: %s \n" %(result))

quadrado = int(input("Digite o quadrado de um número: "))
print("Raiz quadrada: %s \n" %(math.sqrt(quadrado)))
