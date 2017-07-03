#include "worst.h"
#include "best.h"

//new é o lugar do registro removido, tsize é o tamanho
void makeBestList(FILE *fp, int new, int *topo, int tsize){

	int number = -1;
	int node = *topo;
	int ant = node;
	int nsize = -1;
	int naux;

	// a intenção desse algoritmo é simular a lista no arquivo como se realmente fosse uma estrutura de dados, com nós e ponteiros --- apenas analogias

	while(node != -1){
		fseek(fp,node + 1,SEEK_SET);//cursor no começo do arquivo
		fread(&nsize,sizeof(int),1, fp);//nsize vai receber o tamanho do registro removido deste nó
		fread(&naux,sizeof(int),1, fp); // node vai receber a posição do próximo nó na lista

		if(nsize < tsize) {//vai para o próximo -- ordenação crescente
			ant = node;
			node = naux;
		}

		// se encontrar o lugar para inserir o nó removido
		else{
			
			//caso o novo nó seja inserido na frente da lista, deve haver mudança do topo -- funcionando
			if(node == *topo){
				//printf("Frente da lista\n");
				*topo = new; // new vira o novo topo
				fseek(fp,new + 5,SEEK_SET); // vou para o ponteiro do próximo nó, do novo nó removido
				fwrite(&node,sizeof(int),1,fp); //escrevo o offset do próximo nó, que está armazenado no node
				return;
			}
			//caso entre no meio do nó
			else {
				//printf("No meio \n");
				fseek(fp,ant + 5,SEEK_SET); //Vai para o nó anterior, mudar o próximo nó para apontar para o novo
				fwrite(&new,sizeof(int),1,fp); // faço o nó anterio apontar para o novo nó removido

				fseek(fp,new + 5,SEEK_SET); // vou para o ponteiro do próximo nó, do novo nó removido
				fwrite(&node,sizeof(int),1,fp); //escrevo o offset do próximo nó, que está armazenado no node
				return;
			}
		} // insere o nó
	}

	// Se o topo for -1
	if(node == -1 && nsize == -1){
		//printf("Primeira vez");
		*topo = new;
		//printf("Topo do Trab = %d\n",*topo);
		fseek(fp,new + 5,SEEK_SET); //pula para gravar o próximo
		fwrite(&number,sizeof(int),1,fp); //escreve o -1 no próximo nó
	}


	//insere no final da lista
	else{
		//printf("Final\n");
		fseek(fp,-4,SEEK_CUR); //volto 4 pq o cursor sai do while depois do ultimo int
		fwrite(&new,sizeof(int),1,fp); // o ultimo nó recebe como próximo o novo nó a ser inserido
		
		fseek(fp,new + 5,SEEK_SET);// vai para o ponteiro do novo nó removido para o próximo
		fwrite(&number,sizeof(int),1,fp); //escreve o -1, indicando que não há próximo registro
	}
}


int remove_registro_best(char * cnpj, INDICE *index2, int *tam ){
	
	int pos, cont = 0, cabecalho = -1;
	FILE *arq2;
	char c = '*';

	pos = buscaBinaria(index2, 0, *tam, cnpj);
	
	arq2 = fopen("file2.bin", "r+");	
	
	if(arq2 == NULL){
		printf("Arquivo inexistente");
		return -1;
	}

	if(pos == -1){
		printf("CNPJ desejado não existe");
		return -2;
	}


	fread(&cabecalho, sizeof(int), 1, arq2);
							
	//printf("%d\n", index2[pos].offset);
	fseek(arq2, index2[pos].offset , SEEK_SET);						// vai ate offset

	
	fwrite(&c, sizeof(char), 1, arq2);								// escreve *
	
	while(c != '#'){												// le até #
		cont++;
		c = fgetc(arq2);
		//printf("%c", c);
	}
	
	fseek(arq2,-cont,SEEK_CUR);										// volta para frente do *
	
	cont += 1;														//marca tamanho
	
	fwrite(&cont, sizeof(int), 1, arq2);							//escreve o tamanho
	

	makeBestList(arq2,index2[pos].offset,&cabecalho,cont);

	fseek(arq2, 0, SEEK_SET);										// volta pro cabecalho
	fwrite(&cabecalho, sizeof(int), 1, arq2);				// escreve a pos offset
	//printf("Cabeçalho %d\n",cabecalho);
	removeIndex(index2, tam, pos);
	fclose(arq2);
	return 1;
}


void listar_best_removidos(){

	int topo;	
	int node;
	

	int i = 0;
	int size;
	int aux;

	FILE *fp = fopen("file2.bin","r");
	if(fp==NULL) {
		printf("Problemaa");
		return;
	}
	fread(&topo,sizeof(int),1,fp); //lendo o topo da lista
	node = topo;

	printf("Topo:%d\n",topo);
	while(node!=-1){
		fseek(fp,node + 1,SEEK_SET);//cursor no começo do arquivo vai até onde o node aponta --- o +1 serve para pular o asterisco
		fread(&size,sizeof(int),1, fp);//nsize vai receber o tamanho do registro removido deste nó
		fread(&aux,sizeof(int),1, fp);
		printf("%d - Size: %d  Offset :%d  Next :%d\n",i++,size,node,aux);
		node = aux;

	}
/*

	*/
}




int inserir_best(INDICE *index2, int *tam, int regtam,  REGISTRO *novo){
	FILE *fp;
	char ast = '*';

	int node, next,topo,nsize, offset;
	int diff;

	fp = fopen("file2.bin","r+");

	if(fp == NULL){
		printf("\nArquivo inexistente\n");
		return -1;
	}

	//andar na lista até achar o primeiro nó que é igual ou maior que o tamanho a ser inserido
	//inserir no final só quando chegar no -1


	fread(&topo,sizeof(int),1,fp); // pego o tamanho do topo

	node = topo;
	offset = topo;

	while(node!=-1){
		offset = node;
		fseek(fp,node + 1,SEEK_SET); //vou até o indicador de tamanho do registro do topo
		fread(&nsize,sizeof(int),1,fp); //lê o tamanho do registro
		fread(&next,sizeof(int),1,fp); // lê o byte offset do próximo registro

		diff = regtam - nsize; // se diff for zero, o espaço é perfeito, se for positivo = não cabe, se for negativo = tem espaço
		

		if(diff > 0 || diff == -1){ //Se não cabe, vai para o próximo
			node = next;
		}

		// vai acontecer a inserção
		else {
			
			fseek(fp,node,SEEK_SET); //vai para o começo do registro
			insere_registro(fp,novo); //insiro o novo registro no arquivo
			topo = next; // topo recebe o próximo nó

			//cabe perfeitamente -- testado e funcionando, apresentou um erro
			if(diff == 0 ){
				fseek(fp,0,SEEK_SET); //volta para o começo do arquivo para salvar o novo topo
				fwrite(&topo,sizeof(int),1,fp);
				fclose(fp);
				printf("Registrado com Sucesso de modo identico!!");
				//insereIndice(index2, tam,  novo->cnpj, offset);
				//ordeneIndice(index2, *tam);
				return 0;
			}
			// testado e funcionando
			// há pelo menos 2 bytes de espaço, mas menos que 10, fragmentação externa
			else if(diff < -1 && diff > -10){ 
				fwrite(&ast,sizeof(char),1,fp);
				fseek(fp,0,SEEK_SET); //volta para o começo do arquivo para salvar o novo topo
				fwrite(&topo,sizeof(int),1,fp);
				fclose(fp);
				printf("Registrado, mas há existẽncia de fragmentação externa");
				//insereIndice(index2, tam,  novo->cnpj, offset);
				//ordeneIndice(index2, *tam);
				return 0;
			}
			//Problemaa
			// caso há mais de 10 bytes sobrando 
			else if (diff < -9){
				printf("Tratamento de fragmentação!!\n");
				//node += regtam; // node vai receber o byte offset do novo registro a ser inserido na lista
				diff *=-1; // deixando positivo
				fwrite(&ast, sizeof(char), 1, fp);
				fwrite(&diff, sizeof(int), 1, fp); //o tamanho desse novo registro é a diferença entre o tamanho original e o novo
			
				// o node está indo no lugar certo para a função de ordenação???????			
				makeBestList(fp,node + regtam, &topo, diff); // vai adicionar esse registro na lista de removidos

				fseek(fp,0,SEEK_SET); //volta para o começo do arquivo para salvar o novo topo
				fwrite(&topo,sizeof(int),1,fp);
		
				printf("Inserido!!");
				//insereIndice(index2, tam,  novo->cnpj, offset);
				//ordeneIndice(index2, *tam);
				fclose(fp);
				return 0;
			}
		}
	}

	//se chegou aqui, insere no final
	fseek(fp,0,SEEK_END);
	offset = ftell(fp);
	insere_registro(fp,novo); //insiro o novo registro no arquivo
	//insereIndice(index2, tam,  novo->cnpj, offset);
	//ordeneIndice(index2, *tam);
	fclose(fp);

	return 0;
}