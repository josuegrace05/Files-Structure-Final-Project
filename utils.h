#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct indice INDICE;

int chooseOption();
int chooseOrganization();
char *readline(FILE *);
int chooseField();
int toUtf8(char *);

int ler_arquivo_numfixreg();
int listar_registros_numfixreg();

INDICE *criar_indices();

#endif
