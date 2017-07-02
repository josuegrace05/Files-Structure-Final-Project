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

int criar_indices(INDICE **, INDICE **, INDICE **, int *);
void removeIndex(INDICE *, int *, int);
int buscaBinaria(INDICE *, int, int, char *);

int remove_registro(char *, INDICE *, int *);
int print_indice(INDICE *, int);

void listar_removidos();
int insere_registro(FILE *, REGISTRO *);

REGISTRO *cria_registro(int *);
int insereIndice(INDICE *, int *, char *, int);

int inserir_first(INDICE *, int *, int, REGISTRO *);

int estatistica(INDICE *, int, INDICE *, int, INDICE *, int);
int gravaIndice(INDICE *, int, INDICE *, int, INDICE *, int);

void ordeneIndice(INDICE *, int);


#endif
