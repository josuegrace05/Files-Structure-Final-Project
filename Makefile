all: 
	gcc -o T2arquivos Trabmain.c utils.c worst.c -Wall -I. -g

run: 
	./T2arquivos
	
debug:
	valgrind --leak-check=full ./T2arquivos

worst: 
	gcc -o T2arquivos Trabmain.c worst.c utils.c -Wall -I. -g

clean:
	rm -f *.bin