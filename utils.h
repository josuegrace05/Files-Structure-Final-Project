#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct indice INDICE;
typedef struct registro REGISTRO;



struct indice{																	//lista adaptada para ser usada como vetor e fila para o trab de grafos
	
	char *cnpj;
	int  offset;
	
};

struct registro{
	char *cnpj;
	char *dataregistro;
	char *datacancelamento;
	char *cnpjauditor;
	char *nomesocial;
	char *nomefantasia;
	char *motivocancelamento;
	char *nomeempresa;
};

int chooseOrganization();
char *readline(FILE *);
int toUtf8(char *);

int ler_arquivo_numfixreg();
int listar_registros_numfixreg();

int criar_indices(INDICE **, INDICE **, INDICE **);
void removeIndex(INDICE *, int *, int);
int buscaBinaria(INDICE *, int, int, char *);

int remove_registro(char * cnpj, INDICE *index1, int *tam );
int print_indice(INDICE *index1, int tam);

void listar_removidos();
int insere_registro(FILE *, REGISTRO *);

REGISTRO *cria_registro( int *tam );
int insereIndice(INDICE *indexArq, int *n, char * cnpj, int offset);

int inserir_first(INDICE *index1, int *tam, int regtam, REGISTRO *novo);

int estatistica(INDICE *index1, int tam1, INDICE *index2, int tam2, INDICE *index3, int tam3);


#endif
