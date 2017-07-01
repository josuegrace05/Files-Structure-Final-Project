#include "utils.h"



char *readline(FILE *arq_entrada){                                          //função para ler ate a um parametro

    int cont = 0;
    char *string = NULL, c;

    do{
        c = fgetc(arq_entrada);
        string = (char*) realloc (string, sizeof(char) * (cont+1) );     //le o caractere e o salva enquanto este n for                    
        string[cont] = c;           
        cont++; 
            
    }while(c != '\n' && c != EOF && c != '$' && c != ';' && c != '#');

    string[cont - 1] = '\0';                                                 //adiciona um \0 no final da linha para indicar uma string

    return string;                                                           //retorna a string
}

int chooseOrganization(){
    
    int opt;
        printf("=====================================================\n");               // apresenta o menu de escolha de arquivo de saida
        printf("=                      MENU PRINCIPAL               =\n");
        printf("=       1. Criar os arquivos a partir do csv        =\n");
        printf("=       2. Apresentar os registros                  =\n");
        printf("=       3. Criar arquivo de índice                  =\n");
        printf("=       4. Remover registro                         =\n");
        printf("=       5. Inserir registro                         =\n");
        printf("=       6. Estatisticas do índice                   =\n");
        printf("=       7. Estatisticas dos removidos               =\n");
        printf("=       8. Finalizar programa                       =\n");
        printf("=====================================================\n\n");

        printf("Digite uma opcao: ");
        scanf("%d", &opt);                                                  // le a opção desejada
        scanf("%*c");
        
        printf("\n");

        return opt;
}

int toUtf8(char *filename){ //Função para converter o arquivo em utf8

    char *str = (char *)malloc(sizeof(char)*10);
    char *cmd = (char *)malloc(sizeof(char)*42);
    int n = strlen(filename);

    cmd[41] = '\0';
    str[9] = '\0';
    strcpy(str,"temp.csv ");
    strcpy(cmd,"iconv -c -f iso-8859-1 -t utf-8 -o ");
    strcat(cmd,str);

    cmd = (char *)realloc(cmd,(42 + n)*sizeof(char));
    cmd[41+n] = '\0';
    strcat(cmd,filename);
    free(str);

    if(system(cmd) == -1){

        free(cmd);
        return 0;
    }

    free(cmd);
    return 1;
}

//função que recebe o ponteiro do arquivo csv, faz a leitura e grava  no arquivo.bin
int ler_arquivo_numfixreg(){
	
	FILE *arq1, *arq2, *arq3;
	FILE *arq_entrada;													// gera as variaveis necessarias
	char *entrada;
	char *cnpj, *dataregistro, *datacancelamento, *cnpjauditor, *nomesocial, *nomefantasia, *motivocancelamento, *nomeempresa;
	char separador = '$', separador2 = '#';
	int aux = -1, convert = 0, number = 0;
	
	printf("\nDigite o nome do arquivo que deseja ler:\n");
	entrada = readline(stdin);											// pede o nome do arquivo de onde irá ler (.csv)
	
	convert = toUtf8(entrada);

	if(convert == 1)
		arq_entrada = fopen("temp.csv", "r"); //convert o arquivo em um formato utf8
	else
		arq_entrada = fopen(entrada, "r"); //Se não conseguir converter, usa o arquivo original
		
		

	arq1 = fopen("file1.bin", "ab+");									// abre o arquivo de leitura e o de escrita
	arq2 = fopen("file2.bin", "ab+");
	arq3 = fopen("file3.bin", "ab+");
	
	if(arq1 != NULL && arq2 != NULL && arq3 != NULL && arq_entrada != NULL){
		
		fwrite(&aux, sizeof(int), 1, arq1);
		fwrite(&aux, sizeof(int), 1, arq2);								// escreve cabecalho
		fwrite(&aux, sizeof(int), 1, arq3);
		
		while(fgetc(arq_entrada) != EOF){								// enquanto existirem registros
			
			fseek(arq_entrada, -1, SEEK_CUR);							// retorna o cursor uma posição, para compensar o fgetc do while
			
			cnpj = readline(arq_entrada);
			nomesocial = readline(arq_entrada);							//  le cada campo do arquivo csv
			nomefantasia = readline(arq_entrada);
			dataregistro = readline(arq_entrada);
			datacancelamento = readline(arq_entrada);

			if(strcmp(datacancelamento,"null") == 0){

				datacancelamento = (char *)realloc(datacancelamento, sizeof(char) * 9); //Se for formata como 00/00/00
                datacancelamento[8] = '\0';
                strcpy(datacancelamento,"00/00/00");
			}

			motivocancelamento = readline(arq_entrada);
			nomeempresa = readline(arq_entrada);
			cnpjauditor = readline(arq_entrada);

			if(strcmp(cnpjauditor,"null\n") == 0){ //Verifica se o campo cnpj auditor está null.

                cnpjauditor = (char *)realloc(cnpjauditor, sizeof(char) * 19); //Se for formata como 00.000.000/0000-00
                cnpjauditor[18] = '\0';
                strcpy(cnpjauditor,"00.000.000/0000-00");
            }													
	
			fwrite(cnpj, sizeof(char), 18, arq1);
			fwrite(cnpj, sizeof(char), 18, arq2);
			fwrite(cnpj, sizeof(char), 18, arq3);	
			fwrite(dataregistro, sizeof(char), 8, arq1);					// então coloca todos os dados de forma organizada no arquivo
			fwrite(dataregistro, sizeof(char), 8, arq2);
			fwrite(dataregistro, sizeof(char), 8, arq3);
			fwrite(datacancelamento, sizeof(char), 8, arq1);				// para facilitar o uso do arquivo, os campos de tamanho fixo foram colocados todos juntos
			fwrite(datacancelamento, sizeof(char), 8, arq2);
			fwrite(datacancelamento, sizeof(char), 8, arq3);
			fwrite(cnpjauditor, sizeof(char), 18, arq1);	
			fwrite(cnpjauditor, sizeof(char), 18, arq2);	
			fwrite(cnpjauditor, sizeof(char), 18, arq3);						
			
			
			aux = strlen(nomesocial);
			fwrite(nomesocial , sizeof(char), aux, arq1);
			fwrite(&separador , sizeof(char), 1, arq1);							// inserção do delimitador no final dos campos de tamanho variável
			fwrite(nomesocial , sizeof(char), aux, arq2);
			fwrite(&separador , sizeof(char), 1, arq2);
			fwrite(nomesocial , sizeof(char), aux, arq3);
			fwrite(&separador , sizeof(char), 1, arq3);
			
			
			aux = strlen(nomefantasia);
			fwrite(nomefantasia , sizeof(char), aux, arq1);					
			fwrite(&separador , sizeof(char), 1, arq1);
			fwrite(nomefantasia , sizeof(char), aux, arq2);					
			fwrite(&separador , sizeof(char), 1, arq2);
			fwrite(nomefantasia , sizeof(char), aux, arq3);					
			fwrite(&separador , sizeof(char), 1, arq3);
			
			aux = strlen(motivocancelamento);
			fwrite(motivocancelamento , sizeof(char), aux, arq1);
			fwrite(&separador , sizeof(char), 1, arq1);
			fwrite(motivocancelamento , sizeof(char), aux, arq2);
			fwrite(&separador , sizeof(char), 1, arq2);
			fwrite(motivocancelamento , sizeof(char), aux, arq3);
			fwrite(&separador , sizeof(char), 1, arq3);
			
			aux = strlen(nomeempresa);
			fwrite(nomeempresa , sizeof(char), aux, arq1);
			fwrite(&separador , sizeof(char), 1, arq1);
			fwrite(nomeempresa , sizeof(char), aux, arq2);
			fwrite(&separador , sizeof(char), 1, arq2);
			fwrite(nomeempresa , sizeof(char), aux, arq3);
			fwrite(&separador , sizeof(char), 1, arq3);
			
			fwrite(&separador2 , sizeof(char), 1, arq1);						// escreve separador de registro
			fwrite(&separador2 , sizeof(char), 1, arq2);
			fwrite(&separador2 , sizeof(char), 1, arq3);

			//fgetc(arq);													// Foi verificado que no final de cada registro existe um /n, esse fgetc() pega este caracter
			
			number++;

			free(cnpj);													// libera as strings usadas
			free(dataregistro);
			free(datacancelamento);
			free(cnpjauditor);
			free(nomesocial);
			free(nomefantasia);
			free(motivocancelamento);
			free(nomeempresa);
		
		}
		
		printf("\n%d registro(s) foram adicionado(s)\n", number);

		if(convert)
			remove("temp.csv");

		fclose(arq1);													// após adicionar todos os registros fecha os arquivos
		fclose(arq2);
		fclose(arq3);
		fclose(arq_entrada);
			
	}else{
		printf("\nfalha ao abrir o arquivo\n");                           // caso algum dos dois arquivos seham nulos
	}
	
	return 0;
}



// recebe um arquivo válido com o cursor já apontado para o proximo registro a ser impresso
void print_registro(FILE *arq){
	

	char *cnpj, *dataregistro, *datacancelamento, *cnpjauditor; // campos fixos
	char *nomesocial, *nomefantasia, *motivocancelamento, *nomeempresa; //campos variáveis
	
	cnpj = (char *)malloc(sizeof(char)*19);   					// É feita a alocação de uma unidade a mais do que o tamanho do campo, para a inserção do '\0' no final da string
	fread(cnpj, sizeof(char), 18, arq);
	cnpj[18] = '\0';											// inserção do '/0' no final do arquivo

	dataregistro = (char *)malloc(sizeof(char)*9);
	fread(dataregistro, sizeof(char), 8, arq);
	dataregistro[8] = '\0';
	
	datacancelamento = (char *)malloc(sizeof(char)*9);
	fread(datacancelamento, sizeof(char), 8, arq);
	datacancelamento[8] = '\0';

	cnpjauditor = (char *)malloc(sizeof(char)*19);
	fread(cnpjauditor, sizeof(char), 18, arq);
	cnpjauditor[18] = '\0';

	// campos variáveis
	nomesocial = readline(arq);											// le até o separador de campos
	nomefantasia = readline(arq);
	motivocancelamento = readline(arq);
	nomeempresa = readline(arq);
	
	readline(arq);														// le até o separador de registro

	//Printa na tela o registro
	printf("\nCnpj: %s\n",cnpj);
	printf("Nome Social : %s\n", nomesocial);
	printf("Nome Fantasia : %s\n", nomefantasia);
	printf("Data De Registro: %s\n",dataregistro);
	printf("Data De Cancelamento: %s\n",datacancelamento);
	printf("MotivoCancelamento : %s\n", motivocancelamento);
	printf("Nome Empresa : %s\n", nomeempresa );
	printf("Cnpj Auditor: %s\n",cnpjauditor);
	
	free(dataregistro);
	free(datacancelamento);
	free(cnpjauditor);
	free(nomesocial);
	free(nomefantasia);
	free(motivocancelamento);
	free(nomeempresa);
	free(cnpj);
}

//Função recebe um ponteiro de arquivo e printa todos os registros presentes nele
int listar_registros_numfixreg(){

	FILE *arq;
	int contador =  3, number = 0;
	char enter;
	
	arq = fopen("file1.bin", "r");  
	if(arq==NULL){												//verifica se o arquivo existe
		printf("Arquivo Inexistente");
		return -1;
	}

	fseek(arq,4,SEEK_CUR);
	
	while(fgetc(arq)!=EOF){
																		//Enquanto o arquivo não chegou ao seu final
		fseek(arq,-1,SEEK_CUR);											//cursor = cursor - 1 para compensar o fgetc()
		
		if( fgetc(arq) == '*'){
			
			printf("REMOVIDO\n");
			
			while( fgetc(arq) != '#' );
			
		}else{
				
			fseek(arq,-1,SEEK_CUR);														//um registro inteiro é printado na tela
			if(contador-- > 0) {
				printf("\nRegistro %d\n", number++);
				print_registro(arq);	
			}
			else{

				printf("\nDigite enter para continuar ou 'q' para quitar\n");
				scanf("%c", &enter);
				if(enter == 'q')
					break;
				contador = 3;

			}	
		}									
	
	}
	fclose(arq);										
	return 0;
}

void swap(INDICE *vector, int i, int j) {
	INDICE aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

int partition(INDICE *vector, int left, int right) {
	int i, j;

	i = left;
	for (j = i+1; j <= right; j++) {
		if (strcmp(vector[j].cnpj, vector[left].cnpj) < 0) {
			++i;
			swap(vector, i, j);
		}
	}
	swap(vector, i, left);

	return i;
}

void quicksort(INDICE *vector, int left, int right) {
	int r;

	if (left < right) {
		r = partition(vector, left, right);
		quicksort(vector, left, r-1);
		quicksort(vector, r+1, right);
	}
}


void ordeneIndice(INDICE *indiceArq, int n){

	quicksort(indiceArq, 0, n-1);

}

int buscaBinaria(INDICE *indexArq, int start, int end, char *key){

	int middle = (start + end)/2;

	if(start > end)
		return -1;

	if(strcmp(indexArq[middle].cnpj, key) == 0)
		return middle;

	else if(strcmp(indexArq[middle].cnpj, key) < 0)
		return buscaBinaria(indexArq, middle +1 , end, key);

	else 
		return buscaBinaria(indexArq, start, middle -1, key);
}

void removeIndex(INDICE *index, int *n, int pos){
	int i;
	
	free(index[pos].cnpj);

	for(i = pos; i < (*n)-1; i++){
		index[i] = index[i+1];
	}
	(*n)--;

	index = (INDICE*) realloc(index, sizeof(INDICE) * (*n) );
}

int criar_indices(INDICE **index1, INDICE **index2, INDICE **index3){
	
	FILE *arq;
	int cont = 0, contoffset = 4;
	char c, *cnpj;
	
	
	if(*index1 != NULL || *index2 != NULL || *index3 != NULL ){
		printf("Arquivo de indice já existente\n");
		return 0;
	}
	
	arq = fopen("file1.bin", "r");  
	
	if(arq!=NULL){														//verifica se o arquivo existe
		
		fseek(arq,4,SEEK_CUR);
		
		while(fgetc(arq)!=EOF){
			
			fseek(arq,-1,SEEK_CUR);
			
			*index1 = (INDICE*) realloc( *index1, sizeof(INDICE) * (cont+1) );
			*index2 = (INDICE*) realloc( *index2, sizeof(INDICE) * (cont+1) );
			*index3 = (INDICE*) realloc( *index3, sizeof(INDICE) * (cont+1) );
			cnpj = (char*) malloc ( sizeof(char) * 19); 
			fread(cnpj, sizeof(char), 18, arq);
			cnpj[18] = '\0';
			(*index1)[cont].cnpj = cnpj;           
			(*index1)[cont].offset = contoffset; 
			(*index2)[cont].cnpj = cnpj;           
			(*index2)[cont].offset = contoffset; 
			(*index3)[cont].cnpj = cnpj;           
			(*index3)[cont].offset = contoffset;           
			cont++;	
			
			contoffset += 18;
			
			c ='a';
			
			while(c != '#'){
				c = fgetc(arq);
				contoffset++;
			}
			
		}		
		
		ordeneIndice(*index1, cont);
		ordeneIndice(*index2, cont);
		ordeneIndice(*index3, cont);
		
		fclose(arq);
	
	}else{
		printf("falha ao arir o arquivo");
	}
	
	
	return cont;

}

int print_indice(INDICE *index1, int tam){
	
	int i;
	
	for(i=0; i < tam; i++){
			printf("%s %d\n", index1[i].cnpj, index1[i].offset); 
	}
	
	return 0;
}

void listar_removidos(){

	int topo;	
	int node;

	int i = 0;
	int size;
	int aux;

	FILE *fp = fopen("file1.bin","r");
	if(fp==NULL) {
		printf("Problemaa");
		return;
	}
	fread(&topo,sizeof(int),1,fp); //lendo o cabecalho
	node = topo;

	printf("Topo:%d\n",topo);
	while(node!=-1){
		fseek(fp,node + 1,SEEK_SET);//cursor no começo do arquivo vai até onde o node aponta --- o +1 serve para pular o asterisco
		fread(&size,sizeof(int),1, fp);//nsize vai receber o tamanho do registro removido deste nó
		fread(&aux,sizeof(int),1, fp);
		printf("%d - Size: %d  Offset :%d  Next :%d\n",i++,size,node,aux);
		node = aux;

	}
}

int remove_registro(char * cnpj, INDICE *index1, int *tam ){
	
	int pos, cont = 0, cabecalho;
	FILE *arq1;
	char c = '*';
	
	pos = buscaBinaria(index1, 0, *tam, cnpj);
	
	arq1 = fopen("file1.bin", "r+");	
	
	if(arq1 != NULL){
		fread(&cabecalho, sizeof(int), 1, arq1);
								
		printf("%d\n", index1[pos].offset);
		fseek(arq1, index1[pos].offset , SEEK_SET);						// vai ate offset
		
		fwrite(&c, sizeof(char), 1, arq1);								// escreve *
		
		while(c != '#'){												// le até #
			cont++;
			c = fgetc(arq1);
			printf("%c", c);
		}
		
		fseek(arq1,-cont,SEEK_CUR);										// volta para frente do *
		
		cont += 1;														//marca tamanho
		
		printf("tamanho %d\n", cont);
		
		fwrite(&cont, sizeof(int), 1, arq1);							//escreve o tamanho
		
		fwrite(&cabecalho, sizeof(int), 1, arq1);						// escreve cabecalho
		
		fseek(arq1, 0, SEEK_SET);										// volta pro cabecalho
		
		
		fwrite(&(index1[pos].offset), sizeof(int), 1, arq1);				// escreve a pos offset

		removeIndex(index1, tam, pos);
	
		fclose(arq1);
		
	}else{
		printf("falha ao arir o arquivo");
	}
	
	return 0;
}

REGISTRO *cria_registro( int *tam ){
	
	REGISTRO *myregister = (REGISTRO *)malloc(sizeof(REGISTRO));

	printf("Digite o cnpj:\n");
	//scanf("%m[^\n]s",&(myregister->cnpj));
	//scanf("%*c");
	myregister->cnpj = readline(stdin);

	printf("Digite o nome social:\n");
	//scanf("%m[^\n]s",&(myregister->nomesocial));
	//scanf("%*c");
	myregister->nomesocial = readline(stdin);

	printf("Digite o nome fantasia:\n");
	//scanf("%m[^\n]s",&(myregister->nomefantasia));
	//scanf("%*c");
	myregister->nomefantasia = readline(stdin);
	
	printf("Digite a data de registro:\n");
	//scanf("%m[^\n]s",&(myregister->dataregistro));
	//scanf("%*c");
	myregister->dataregistro = readline(stdin);
	
	
	printf("Digite a data de cancelamento:\n");
	//scanf("%m[^\n]s",&(myregister->datacancelamento));
	//scanf("%*c");
	myregister->datacancelamento = readline(stdin);

	if(strcmp(myregister->datacancelamento,"null") == 0)
		strcpy(myregister->datacancelamento,"00/00/00"); 
		
	printf("Digite o motivo do cancelamento:\n");
	//scanf("%m[^\n]s",&(myregister->motivocancelamento));
	//scanf("%*c");
	myregister->motivocancelamento = readline(stdin);
	
	printf("Digite o nome da empresa:\n");
	//scanf("%m[^\n]s",&(myregister->nomeempresa));
	//scanf("%*c");
	myregister->nomeempresa = readline(stdin);

	printf("Digite o cnpj auditor:\n");
	//scanf("%m[^\n]s",&(myregister->cnpjauditor));
	//scanf("%*c");
	myregister->cnpjauditor = readline(stdin);
	
	*tam = 52 + strlen(myregister->motivocancelamento)+ 1 + strlen(myregister->nomesocial) + 1 + strlen(myregister->nomefantasia) + 1 + strlen(myregister->nomeempresa) + 1 + 1;

	return myregister;
}

int insere_registro(FILE *arq, REGISTRO *novo){
	
	char separador = '$', separador2 = '#';
	int size;
	
	fwrite(novo->cnpj, sizeof(char), 18, arq);	
	fwrite(novo->dataregistro, sizeof(char), 8, arq);					// então coloca todos os dados de forma organizada no arquivo
	fwrite(novo->datacancelamento, sizeof(char), 8, arq);				// para facilitar o uso do arquivo, os campos de tamanho fixo foram colocados todos juntos
	fwrite(novo->cnpjauditor, sizeof(char), 18, arq);	

	size = strlen(novo->nomesocial);
	fwrite(novo->nomesocial , sizeof(char), size, arq);
	fwrite(&separador , sizeof(char), 1, arq);							// inserção do delimitador no final dos campos de tamanho variável
	
	
	size = strlen(novo->nomefantasia);
	fwrite(novo->nomefantasia , sizeof(char), size, arq);					
	fwrite(&separador , sizeof(char), 1, arq);
	
	size = strlen(novo->motivocancelamento);
	fwrite(novo->motivocancelamento , sizeof(char), size, arq);
	fwrite(&separador , sizeof(char), 1, arq);
	
	size = strlen(novo->nomeempresa);
	fwrite(novo->nomeempresa , sizeof(char), size, arq);
	fwrite(&separador , sizeof(char), 1, arq);
	
	fwrite(&separador2 , sizeof(char), 1, arq);						// escreve separador de registro

	
	return 0;
}

int insereIndice(INDICE *indexArq, int *n, char * cnpj, int offset){

	indexArq = (INDICE *)realloc(indexArq, (sizeof(INDICE)*((*n)+1)));
	
	if(indexArq != NULL){

		indexArq[*n].cnpj = cnpj;
		indexArq[*n].offset = offset;
		(*n)++;

		return 1;	
	}
	
	return 0;
}

int inserir_first(INDICE *index1, int *tam, int regtam,  REGISTRO *novo){
	
	FILE *arq1;
	int offset, node, size, aux, aux2 = -2, anterior = -1;
	char separador2 = '#';
	
	arq1 = fopen("file1.bin", "r+");
	
	if(arq1 != NULL){
																		// pega o valor do cabecalho
		fread(&node, sizeof(int), 1, arq1);								// anda nos removidos
		
		anterior = node;
		
		while(node != -1){
			
			aux2 ++;
			
			fseek(arq1,node + 1,SEEK_SET);								//cursor no começo do arquivo vai até onde o node aponta --- o +1 serve para pular o asterisco
			fread(&size,sizeof(int),1, arq1);							//nsize vai receber o tamanho do registro removido deste nó
			fread(&offset,sizeof(int),1, arq1);
			
			
			
			if( size == regtam){
				
				printf("entrou caso igual\n");
			
				fseek(arq1,-9,SEEK_CUR);								//volta para antes do *
				insere_registro(arq1, novo);
				
				if(aux2 != -1){
					insereIndice(index1, tam,  novo->cnpj, anterior);
					ordeneIndice(index1, *tam);
					fseek(arq1, anterior+5, SEEK_SET);						// vai até o anterior e pula o * e o tamanho do reg
					fwrite(&offset , sizeof(int), 1, arq1);					// escreve novo next
				}else{
					insereIndice(index1, tam,  novo->cnpj, anterior);
					ordeneIndice(index1, *tam);
					fseek(arq1, 0, SEEK_SET);
					fwrite(&aux2 , sizeof(int), 1, arq1);
				}
				
				
				fclose(arq1);
				return 0;
				
			}
			else if(size - regtam > 10){	
				
				printf("entrou caso maior q 10\n");							
				
				fseek(arq1,-8,SEEK_CUR);								// volta para frente do *
				
				aux = size - regtam;
				fwrite(&aux , sizeof(int), 1, arq1);
				
				fseek(arq1, 4,SEEK_CUR);								// vai até depois do indicador do prox
				fseek(arq1, aux-10, SEEK_CUR);							// vai até o tamanho novo menos o tamanho ja percorrido menos o local onde vamos colocar o #
				
				fwrite(&separador2 , sizeof(char), 1, arq1);
							
				insere_registro(arq1, novo);
				
				insereIndice(index1, tam,  novo->cnpj, anterior + aux);
				ordeneIndice(index1, *tam);
				
				fclose(arq1);
				return 1;
						
			}else if(size - regtam < 10 && size - regtam >= 2){			
			
				printf("entrou caso entre 2 e 10\n");
			
				fseek(arq1,-8,SEEK_CUR);								// volta para frente do *
				
				aux = size - regtam;
				
				fseek(arq1, aux-2 ,SEEK_CUR);							// avança até antes do #							
				
				fwrite(&separador2 , sizeof(char), 1, arq1);			// escreve #
						
				insere_registro(arq1, novo);
				
				if(aux2 != -1){
					insereIndice(index1, tam,  novo->cnpj, anterior + aux);
					ordeneIndice(index1, *tam);
					fseek(arq1, anterior+5, SEEK_SET);						// vai até o anterior e pula o * e o tamanho do reg
					fwrite(&offset , sizeof(int), 1, arq1);					// escreve novo next
				}else{
					insereIndice(index1, tam,  novo->cnpj, anterior + aux);
					ordeneIndice(index1, *tam);
					fseek(arq1, 0, SEEK_SET);
					fwrite(&aux2 , sizeof(int), 1, arq1);
				}
				
				fclose(arq1);
				return 1;
			}
			
			
			//printf("Size: %d  Offset :%d  Next :%d\n",size,node,offset);
			anterior = offset;
			node = offset;
			
		}
	
		fseek(arq1, 0, SEEK_END);
		aux = ftell(arq1);
		insere_registro(arq1, novo);
		insereIndice(index1, tam,  novo->cnpj, aux);
		ordeneIndice(index1, *tam);
		fclose(arq1);
		
		return 1;
	
	}else{
		printf("falha ao arir o arquivo");
	}
	
	
	return 0;
}


