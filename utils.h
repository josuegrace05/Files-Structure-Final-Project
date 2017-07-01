#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct indice INDICE;
typedef struct registro REGISTRO;

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


REGISTRO *cria_registro( int *tam );
int inserir_first(INDICE *index1, int *tam, int regtam, REGISTRO *novo);

#endif
