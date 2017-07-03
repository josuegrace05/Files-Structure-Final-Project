#include "worst.h"

//tomar cuidado com arquivos duplicados, sempre verificar se eles estão com 30Kbytes



//new é o lugar do registro removido, tsize é o tamanho
void makeWorstList(FILE *fp, int new, int *topo, int tsize){

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

		if(nsize > tsize) {//vai para o próximo
			ant = node;
			node = naux;
		}

		// se encontrar o lugar para inserir o nó removido
		else{
			
			//caso o novo nó seja inserido na frente da lista, deve haver mudança do topo -- funcionando
			if(node == *topo){
				printf("Frente da lista\n");
				*topo = new; // new vira o novo topo
				fseek(fp,new + 5,SEEK_SET); // vou para o ponteiro do próximo nó, do novo nó removido
				fwrite(&node,sizeof(int),1,fp); //escrevo o offset do próximo nó, que está armazenado no node
				return;
			}
			//caso entre no meio do nó
			else {
				printf("No meio \n");
				fseek(fp,ant + 5,SEEK_SET); //Vai para o nó anterior, mudar o próximo nó para apontar para o novo
				fwrite(&new,sizeof(int),1,fp); // faço o nó anterio apontar para o novo nó removido

				fseek(fp,new + 5,SEEK_SET); // vou para o ponteiro do próximo nó, do novo nó removido
				fwrite(&node,sizeof(int),1,fp); //escrevo o offset do próximo nó, que está armazenado no node
				return;
			}
		} // insere o nó
	}

	// primeira remoção --- funcionando
	if(node == -1 && nsize == -1){
		printf("Primeira vez");
		*topo = new;
		fseek(fp,new + 5,SEEK_SET); //pula para gravar o próximo
		fwrite(&number,sizeof(int),1,fp); //escreve o -1 no próximo nó
	}


	//insere no final da lista --- funcionando
	else{
		printf("Final\n");
		fseek(fp,-4,SEEK_CUR); //volto 4 pq o cursor sai do while depois do ultimo int
		fwrite(&new,sizeof(int),1,fp); // o ultimo nó recebe como próximo o novo nó a ser inserido
		
		fseek(fp,new + 5,SEEK_SET);// vai para o ponteiro do novo nó removido para o próximo
		fwrite(&number,sizeof(int),1,fp); //escreve o -1, indicando que não há próximo registro
	}
}


int remove_registro_worst(char * cnpj, INDICE *index3, int *tam ){
	
	int pos, cont = 0, cabecalho = -1;
	FILE *arq3;
	char c = '*';

	pos = buscaBinaria(index3, 0, *tam, cnpj);
	
	arq3 = fopen("file3.bin", "r+");	
	
	if(arq3 == NULL){
		printf("Arquivo inexistente");
		return -1;
	}

	if(pos == -1){
		printf("CNPJ desejado não existe");
		return -2;
	}


	fread(&cabecalho, sizeof(int), 1, arq3);
							
	printf("%d\n", index3[pos].offset);
	fseek(arq3, index3[pos].offset , SEEK_SET);						// vai ate offset

	
	fwrite(&c, sizeof(char), 1, arq3);								// escreve *
	
	while(c != '#'){												// le até #
		cont++;
		c = fgetc(arq3);
		printf("%c", c);
	}
	
	fseek(arq3,-cont,SEEK_CUR);										// volta para frente do *
	
	cont += 1;														//marca tamanho
	
	fwrite(&cont, sizeof(int), 1, arq3);							//escreve o tamanho
	

	makeWorstList(arq3,index3[pos].offset,&cabecalho,cont);

	fseek(arq3, 0, SEEK_SET);										// volta pro cabecalho
	fwrite(&cabecalho, sizeof(int), 1, arq3);				// escreve a pos offset
	printf("Cabeçalho %d\n",cabecalho);
	removeIndex(index3, tam, pos);
	fclose(arq3);
	return 1;
}



//essa função pode ser usada em todos os casos, para dar uma olhada no vetor de removidos

void listar_worst_removidos(){

	int topo;	
	int node;
	

	int i = 0;
	int size;
	int aux;

	FILE *fp = fopen("file3.bin","r");
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


//faltando inserir no arquivo de índice
int inserir_worst(INDICE *index3, int *tam, int regtam,  REGISTRO *novo){
	FILE *fp;
	char ast = '*';

	int node, next,topo,nsize;
	int offset;
	int diff;
	fp = fopen("file3.bin","r+");

	if(fp == NULL){
		printf("Arquivo inexistente");
		return -1;
	}

	//se o topo alterar, alterar o topo no arquivo
	//se o tamanho do (registro + 2) for maior que o do primeiro registro removido, deverá ser inserido no final do arquivo
	//se a diferença de tamanho é entre 2 e 10, insere mas haverá lixo
	//se a diferença de tamanho for maior/igual a 10, insere e o resto será adicionado na lista de registros removidos

	fread(&topo,sizeof(int),1,fp);
	node = topo;

	offset = node;

	fseek(fp,node + 1,SEEK_SET);//cursor no começo do arquivo, + 1 por conta do asterisco
	fread(&nsize,sizeof(int),1, fp);//nsize vai receber o tamanho do registro removido deste nó
	printf("Original : %d Novo : %d",nsize,regtam);

	diff = nsize - regtam;
	if(diff == 0  || diff > 1) {// Inserção no topo da lista
		fread(&next,sizeof(int),1, fp);
		fseek(fp,node,SEEK_SET); //volto para o inicio da lista
		
		insere_registro(fp,novo); //insiro o novo registro no arquivo
		topo = next; // topo recebe o próximo nó
		
		printf("NEW Topo :%d\n", topo);
		//coube perfeiramente
		if (diff == 0) { 
			fseek(fp,0,SEEK_SET); //volta para o começo do arquivo para salvar o novo topo
			fwrite(&topo,sizeof(int),1,fp);
			printf("Registrado com Sucesso de modo identico!!");
		}


		else if (diff < 10){
			
			fwrite(&ast, sizeof(char), 1, fp);
			fseek(fp,0,SEEK_SET); //volta para o começo do arquivo para salvar o novo topo
			fwrite(&topo,sizeof(int),1,fp);
			printf("Incluido, mas haverá fragmentação externa!!");
		}

		//caso necessite de tratamento de fragmentação interna na inserção
		else {
			printf("Tratamento de fragmentação!!\n");
			node += regtam; // node vai receber o byte offset do novo registro a ser inserido na lista
			printf("Nedsw = %ld!!\n",(int long)node);
			printf("Novo tamanho = %d!!\n",diff);
			//fseek(fp,1,SEEK_CUR);
			fwrite(&ast, sizeof(char), 1, fp);
			fwrite(&diff, sizeof(int), 1, fp); //o tamanho desse novo registro é a diferença entre o tamanho original e o novo
			
			makeWorstList(fp, node, &topo, diff); // vai adicionar esse registro na lista de removidos

			fseek(fp,0,SEEK_SET); //volta para o começo do arquivo para salvar o novo topo
			fwrite(&topo,sizeof(int),1,fp);
		}


		//insereIndice(index3, tam,  novo->cnpj, offset);
		//ordeneIndice(index3, *tam);

	}
	//insere no final do arquivo
	else{
		fseek(fp,0,SEEK_END);
		offset = ftell(fp);
		//insereIndice(index3, tam,  novo->cnpj, offset);
		//ordeneIndice(index3, *tam);
		insere_registro(fp,novo);

	}
	fclose(fp);
	printf("Registrado com Sucesso!!");
	return 0;
}


REGISTRO *myRecord(int *tam, int qual){
	
	FILE *fp;

	//printf("Qual %d", qual);

	if (qual == 0) fp = fopen("teste.txt","r"); //
	if (qual == 1) fp = fopen("teste2.txt","r");
	if (qual == 2) fp = fopen("teste3.txt","r");
	if (qual == 3) fp = fopen("teste4.txt","r");


	REGISTRO *myregister = (REGISTRO *)malloc(sizeof(REGISTRO));



	myregister->cnpj = readline(fp);
	myregister->nomesocial = readline(fp);

	
	myregister->nomefantasia = readline(fp);

	myregister->dataregistro = readline(fp);

	myregister->datacancelamento = readline(fp);

	if(strcmp(myregister->datacancelamento,"null") == 0)
		strcpy(myregister->datacancelamento,"00/00/00"); 

	myregister->motivocancelamento = readline(fp);

	myregister->nomeempresa = readline(fp);

	myregister->cnpjauditor = readline(fp);
	fclose(fp);
	

	*tam = 52 + strlen(myregister->motivocancelamento)+ 1 + strlen(myregister->nomesocial) + 1 + strlen(myregister->nomefantasia) + 1 + strlen(myregister->nomeempresa) + 1 + 1;
	return myregister;
}