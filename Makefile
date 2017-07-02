all: 
	gcc -o Trabmain Trabmain.c utils.c worst.c -Wall -I. -g

run: 
	./Trabmain
	
debug:
	valgrind --leak-check=full ./Trabmain

worst: 
	gcc -o Trabmain Trabmain.c worst.c utils.c -Wall -I. -g

clean:
	rm -f *.bin