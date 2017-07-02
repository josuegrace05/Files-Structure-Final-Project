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
	char *cnpj, c;
	REGISTRO *novoreg;
	int teste;

	while(op1 != 8){															
		
		op1 = chooseOrganization();

		switch(op1){

			case 1:
				if(ler_arquivo_numfixreg())//Lê do arquivo csv de entrada
					printf("A operação foi bem succedida\n");
				else
					printf("A operação não foi bem succedida\n");
				break;

			case 2:
				if(listar_registros_numfixreg());//Lista os registros já adicionados
					printf("A operação foi bem succedida\n");
				else
					printf("A operação não foi bem succedida\n")
			break;

			case 3:
				if(criar_indices(&index1, &index2, &index3, &tam1)){//Cria os 3 arquivos de índice
					printf("A operação foi bem succedida\n")
					tam2 = tam1;
					tam3 = tam2;
				}
				else
					printf("A operação não foi bem succedida\n"); 
			break;
				
			case 4://remove um registro a partir da sua chave primária (cnpj)
				printf("Digite o cnpj\n");
				cnpj = readline(stdin);

				printf("Removendo usando a allocação first_fit....\n");
				if(remove_registro(cnpj, index1, &tam1))//remoção first_fit
					printf("A operação foi bem succedida\n");
				else
					printf("A operação não foi bem succedida\n", );

				printf("Removendo usando a allocação worst_fit....\n");
				if(remove_registro_worst(cnpj, index3, &tam3)) //remoção worst fit
					printf("A operação foi bem succedida\n");
				else
					printf("A operação não foi bem succedida\n", );	
			break;	
			
			case 5://adiciona um novo registro

				printf("Adicionar manualmente ? (S/N)\n");
				scanf("%c", &c);

				if(c == 'S' || c == 's'){  //caso queira gravar manualmente

					//scanf("%d",&teste); João dexei comentado pra vc fazer seus testes ta ??
					//novoreg = myRecord(&regtam,teste);
					novoreg = criar_registro(&regtam);
				}

				else if(c == 'N' || c == 'n'){//caso queria gravar de um arquivo
					ler_arquivo_numfixreg();//Lê do arquivo csv de entrada
				}

				printf("Inserindo usando a allocação first_fit....\n");
				if(inserir_first(index1, &tam1, regtam, novoreg))
					printf("A operação foi bem succedida\n");
				else
					printf("A operação não foi bem succedida\n");
				
				printf("Inserindo usando a allocação worst_fit....\n");
				inserir_worst(index3, &tam3, regtam, novoreg);

				
				printf("Quer vizualisar o índice (1) ? (S/N)\n");
				scanf("%c", &c);
				if(c == 'S' || c == 's')
					print_indice(index1, tam1);

				printf("Quer vizualisar o índice (3) ? (S/N)\n");
				scanf("%c", &c);
				if(c == 'S' || c == 's')
					print_indice(index3, tam3);

			break;	
			
			case 6:
				
				estatistica(index1, tam1, index2, tam2, index3, tam3);
				
			break;	
			
			case 7:
				printf("-------------Fist Fit--------------");
				listar_removidos();
				printf("-------------Worst Fit-------------");
				listar_worst_removidos();
				
			break;	
			
			case 8:
				
				printf("Gravando o índice....\n");
				if(gravaIndice(index1, tam1, index2, tam2, index3, tam3))
					printf("Operção bem succedida.\n");
				printf("Finalizando o programa.\n");
				
			break;	
			
			default:
				printf("\nOpção inválida. Tente de novo\n");

		}
	}

	return 0;
}
