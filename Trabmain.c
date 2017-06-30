#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"



//Joao Pedro Sousa dos Reis
//9293373
//Josué Grace Kabongo Kalala
//9770382
//Pedro Avellar Machado
//9779304
//Rafael Amaro Rolfsen
//9038648

// Este código foi testado em sistemas linux!


int main(int argc, char *argv[]){

	int op1 = 1; 
	INDICE *index;													

	while( op1 != 7){															
		
		op1 = chooseOrganization();

		switch(op1){

			case 1:
				
				printf("caso1 cria os 3 arquivos\n");
				ler_arquivo_numfixreg();
			
				break;

			case 2:
				
				printf("caso2 mostrar arquivo 1\n");
				listar_registros_numfixreg();

			break;

			case 3:
				
				printf("caso3 criar indice\n");
				index = criar_indices();
				
				
			break;
				
			case 4:
				
				printf("caso4\n");
				
			break;	
			
			case 5:
				
				printf("caso5\n");
				
			break;	
			
			case 6:
				
				printf("caso6\n");
				
			break;	
			
			case 7:
				
				printf("Finalizando o programa.\n");
				
			break;	
			

			default:
				printf("\nOpção inválida. Tente de novo\n");

		}
	}

	return 0;
}
