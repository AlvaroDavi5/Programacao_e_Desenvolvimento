index = 0

while index <= 15:
	print(index)
	index += 1

print ('\n')



for x in range(12): # gerar lista com valores de 0 a 12
	if x == 0:
		print("Zero ignorado")
		continue # sai da iteração do loop temporarioamente
	if x % 2 == 0:
		print(x)

print ('\n')

for x in range(15, 50): # gerar lista com valores de 15 a 20
	print(x)
	if x == 25:
		break # sai completamente do loop
