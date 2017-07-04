#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "worst.h"
#include "best.h"

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

	int op1 = 1, tam1 = 0, tam2 = 0, tam3 = 0, regtam; 
	INDICE *index1 = NULL, *index2 = NULL, *index3 = NULL;													
	char *cnpj, c;
	//int teste;
	REGISTRO *novoreg;
	//int teste;

	while(op1 != 8){															
		
		op1 = chooseOrganization();

		switch(op1){

			case 1:
				if(ler_arquivo_numfixreg())//Lê do arquivo csv de entrada (entrada.csv)
					printf("\nA operação foi bem succedida\n");
				else
					printf("\nA operação não foi bem succedida\n");
				break;

			case 2:
				if(listar_registros_numfixreg())//Lista os registros já adicionados
					printf("\nA operação foi bem succedida\n");
				else
					printf("\nA operação não foi bem succedida\n");
			break;

			case 3:
				if(criar_indices(&index1, &index2, &index3, &tam1)){//Cria os 3 arquivos de índice
					printf("\nA operação foi bem succedida\n");
					tam2 = tam1;
					tam3 = tam2;
				}
				else
					printf("\nA operação não foi bem succedida\n"); 
				
				print_indice(index1, tam1);

			break;
				
			case 4://remove um registro a partir da sua chave primária (cnpj)
				printf("\nDigite o cnpj\n");
				cnpj = readline(stdin);

				printf("\nRemovendo usando a alocação first_fit....\n");
				if(remove_registro(cnpj, &index1, &tam1))//remoção first_fit

					printf("\nA operação foi bem succedida\n");
				else
					printf("\nA operação não foi bem succedida\n");

				printf("\nRemovendo usando a alocação best_fit....\n");
				if(remove_registro_best(cnpj, &index2, &tam2)) //remoção worst fit
					printf("\nA operação foi bem succedida\n");
				else
					printf("\nA operação não foi bem sucedida\n");	

				printf("\nRemovendo usando a alocação worst_fit....\n");
				if(remove_registro_worst(cnpj, &index3, &tam3)) //remoção worst fit
					printf("\nA operação foi bem sucedida\n");
				else
					printf("\nA operação não foi bem sucedida\n");
			break;	
			
			case 5://adiciona um novo registro

				novoreg = cria_registro(&regtam);

				printf("\nInserindo usando a allocação first_fit....\n");
				if(inserir_first(&index1, &tam1, regtam, novoreg))
					printf("\nA operação foi bem succedida\n");
				else
					printf("\nA operação não foi bem succedida\n");
				
				printf("\nInserindo usando a allocação worst_fit....\n");
				inserir_worst(&index3, &tam3, regtam, novoreg);
				
				//printf("Começou....\n");
				printf("\nInserindo usando a allocação best_fit....\n");
				inserir_best(&index2, &tam2, regtam, novoreg);
				
				printf("\nQuer vizualisar os índices ? (S/N)\n");
				scanf("%c", &c);
				scanf("%*c");

				if(c == 'S' || c == 's')
				{
					
					printf("\n Índice (1) \n");
					print_indice(index1, tam1);
					printf("\n Índice (2) \n");
					print_indice(index2, tam2);
					printf("\n Índice (3) \n");
					print_indice(index3, tam3);
				}

			break;	
			
			case 6:
				
				if(estatistica(index1, tam1, index2, tam2, index3, tam3))
					printf("\nOperação bem succedida.\n");
				else
					printf("\nOperação não foi bem succedida.\n");
				
			break;	
			
			case 7:
				printf("-------------Fist Fit--------------\n");
				listar_removidos();
				printf("-------------Best Fit--------------\n");
				listar_best_removidos();
				printf("-------------Worst Fit-------------\n");
				listar_worst_removidos();
				
			break;	
			
			case 8:
				
				printf("\nGravando o índice....\n");
				if(gravaIndice(index1, tam1, index2, tam2, index3, tam3))
					printf("\nOperção bem succedida.\n");
				else
					printf("\nOperação não bem succedida. Índice inexistente.\n");
				printf("\nFinalizando o programa.\n");
				
			break;	
			
			default:
				printf("\nOpção inválida. Tente de novo\n");

		}
	}

	return 0;
}
