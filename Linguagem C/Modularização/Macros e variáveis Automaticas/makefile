
# variavel 'BIN_NAME' recebe o nome do programa em arquivo binario
BIN_NAME=finalprogram


# macro 'C_SOURCE' usa funcao wildcard para obter os nomes de todos os arquivos de codigo-fonte com extensao .c
C_SOURCE=$(wildcard *.c)

# macro 'H_SOURCE' usa funcao wildcard para obter os nomes de todos os arquivos de codigo-fonte com extensao .h
H_SOURCE=$(wildcard *.h)


# macro 'OBJ' utiliza todos os nomes dos arquivos de 'C_SOURCE', entretanto substituindo .c por .o
OBJ=${C_SOURCE:.c=.o}
# ${} e $() podem igualmente ser usadas para macros


# definindo compilador e flags
CPL=gcc

CPL_FLAGS=-c     \
          -lm     \
          -Wall    \
# usado Space no lugar de Tab para evitar erros


# o target 'all' tem como pre-requisito a variavel 'BIN_NAME', que se torna um target
all: ${BIN_NAME}


# o target 'BIN_NAME' tem como pre-requisito a macro 'OBJ' e seus arquivos
${BIN_NAME}: ${OBJ}
	${CPL} -o $@ $^ ${CPL_FLAGS}
	#$@ nome do target, $^ todos os pre-requisitos, $< primeiro pre-equisito
	echo ''


# o target '%.o' pega o stem (tronco do nome) e o utiliza como referencia no pre-requisito
%.o: %.h %.c
	$(CPL) -o $@ $< $(CPL_FLAGS)


# os targets dos arquivos .o tem como pre-requisito os arquivos .c
main.o: main.c $(H_SOURCE)
	$(CPL) -o $@ $< $(CPL_FLAGS)
	echo ''


clean:
	rm -rf *.o *~ $(BIN_NAME)
	echo ''
