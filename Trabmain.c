#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "worst.h"



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

	int op1 = 1, tam1, tam2, tam3, regtam; 
	INDICE *index1 = NULL, *index2 = NULL, *index3 = NULL;													
	char *cnpj;
	REGISTRO *novoreg;

	while( op1 != 8){															
		
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
				tam1 = criar_indices(&index1, &index2, &index3);
				tam2 = tam1;
				tam3 = tam2;
				
			break;
				
			case 4:
				
				printf("digite o cnpj\n");
				cnpj = readline(stdin);
				remove_registro( cnpj, index1, &tam1 );
			//	remove_registro_worst( cnpj, index3, &tam1 ); //remoção worst fit
				
				printf("caso4\n");
				
			break;	
			
			case 5:

				novoreg = cria_registro(&regtam);
				
				inserir_first(index1, &tam1, regtam, novoreg);
				//inserir_worst(index3, &tam1, regtam, novoreg);
				
				printf("caso5\n");
				
			break;	
			
			case 6:
				
				listar_removidos();
				listar_worst_removidos();
				printf("caso6\n");
				
			break;	
			
			case 7:
				
				printf("caso7\n");
				print_indice(index1, tam1);
				
			break;	
			
			case 8:
				
				printf("Finalizando o programa.\n");
				
			break;	
			

			default:
				printf("\nOpção inválida. Tente de novo\n");

		}
	}

	return 0;
}
