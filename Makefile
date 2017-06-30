all: 
	gcc -o T2arquivos Trabmain.c utils.c -Wall -I. -g

run: 
	./T2arquivos
	
debug:
	valgrind --leak-check=full ./T2arquivos
