#include <stdio.h>

int main (int argc, char *argv[]){
	
	FILE *fp = fopen("ftell.txt", "ab+");
	fseek(fp, 0, SEEK_END);
	
	if(ftell(fp) > 0)
		printf("Arquivo não vazio\n");
	else
		printf("arquivo vazio\n");

	return 0;
}