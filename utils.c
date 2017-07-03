#include "utils.h"
#define cifrao '$'
#define hashtag '#'
#define asterisco '*'

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
    char *cmd = (char *)malloc(sizeof(char)*45);
    int n = strlen(filename);

    cmd[41] = '\0';
    str[9] = '\0';
    strcpy(str,"temp.csv ");
    strcpy(cmd,"iconv -c -f iso-8859-1 -t utf-8 -o ");
    strcat(cmd,str);

    cmd = (char *)realloc(cmd,(45 + n)*sizeof(char));
    cmd[44+n] = '\0';
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
	char separador = cifrao, separador2 = hashtag;
	int aux = -1, convert = 0, number = 0;
	
	printf("\nDigite o nome do arquivo que deseja ler:\n");   // pede o nome do arquivo de onde irá ler (.csv)
	entrada = readline(stdin);											
	convert = toUtf8(entrada);								//convert o arquivo no formato utf8

	if(convert == 1)
		arq_entrada = fopen("temp.csv", "r"); //Usa o arquivo temporário convertido
	else
		arq_entrada = fopen(entrada, "r"); //Se não conseguir converter, usa o arquivo original
		
		

	arq1 = fopen("file1.bin", "ab+");									// abre o arquivo de leitura e o de escrita
	arq2 = fopen("file2.bin", "ab+");
	arq3 = fopen("file3.bin", "ab+");
	
	if(arq1 != NULL && arq2 != NULL && arq3 != NULL && arq_entrada != NULL){
		
		// escreve o registro de cabeçalho se o arquivo estiver fazio
		fseek(arq1, 0, SEEK_END); 
		if(ftell(arq1) == 0)
			fwrite(&aux, sizeof(int), 1, arq1);

		fseek(arq2, 0, SEEK_END);
		if(ftell(arq2) == 0)
			fwrite(&aux, sizeof(int), 1, arq2);								
		
		fseek(arq3, 0, SEEK_END);
		if(ftell(arq3) == 0)
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

		if(convert) //apaga o arquivo temporário se foi criado
			remove("temp.csv");

		fclose(arq1);													// após adicionar todos os registros fecha os arquivos
		fclose(arq2);
		fclose(arq3);
		fclose(arq_entrada);
			
	}else{
		printf("\nfalha ao abrir um arquivo\n");                           // caso algum dos 4 arquivos sejam nulo
		return 0;
	}
	
	return 1;
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
	int contador =  1, number = 0;
	char enter;
	
	arq = fopen("file1.bin", "r");  
	
	if(arq == NULL){												//verifica se o arquivo existe
		printf("Arquivo Inexistente");
		return 0;
	}

	fseek(arq, 4, SEEK_CUR);//pula o registro de cabeçalho
	
	while(fgetc(arq) != EOF){
																		//Enquanto o arquivo não chegou ao seu final
		fseek(arq,-1,SEEK_CUR);											//cursor = cursor - 1 para compensar o fgetc()
		
		if(fgetc(arq) == asterisco){
			
			printf("\nREMOVIDO\n");
			
			while(fgetc(arq) != hashtag);//lê o registro removido
			
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
				contador = 1;
			}	
		}									
	
	}

	fclose(arq);										
	return 1;
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

void insertionSort(INDICE *vector, int n){

	int i,j;
    INDICE key;
    printf("AQUI: %d\n", n);

    for (j = 1; j < n; j++) {
	    key = vector[j];
	    i = j-1;			
        while (i >= 0 && (strcmp(key.cnpj, vector[i].cnpj) < 0)) {	
    		vector[i+1] = vector[i];
    		i--;				
    	}
    	vector[i+1] = key;
    }
    	
}
//Função para ordenar o índice
void ordeneIndice(INDICE *indiceArq, int n){

	//quicksort(indiceArq, 0, n-1);
	insertionSort(indiceArq, n);

}
//Função para buscar registro no índice
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
//Função para remover no índice
void removeIndex(INDICE **index, int *n, int pos){
	int i;
	
	for(i = pos; i < (*n)-1; i++){
		*(index)[i] = *(index)[i+1];
	}
	(*n)--;
	*index = (INDICE*) realloc(*index, sizeof(INDICE) * (*n));
}
//Função para carregar o índice do arquivo para memória
int carregaIndices(INDICE **index1, INDICE **index2, INDICE **index3){

	int cont = 0, offset;
	char *cnpj;
	FILE *arq1, *arq2, *arq3;

	arq1 = fopen("index1.bin", "r+");

	printf("\nCarregando o arquivo de índice 1...\n");

	while(fgetc(arq1) != EOF){

		fseek(arq1, -1, SEEK_CUR);

		cnpj = (char*) malloc(sizeof(char) * 19);
		cnpj[18] = '\0';

		fread(cnpj,sizeof(char),18, arq1);
		
		fread(&offset,sizeof(int),1, arq1);

		*index1 = (INDICE*) realloc(*index1, sizeof(INDICE) * (cont+1) );

		(*index1)[cont].cnpj = cnpj;           
		(*index1)[cont].offset = offset;

		cont++;

	}

	fclose(arq1);
	cont = 0;

	arq2 = fopen("index2.bin", "r+");

	printf("\nCarregando o arquivo de índice 2...\n");

	while(fgetc(arq2) != EOF){

		fseek(arq2, -1, SEEK_CUR);

		cnpj = (char*) malloc(sizeof(char) * 19);
		cnpj[18] = '\0'; 

		fread(cnpj, sizeof(char), 18, arq2);
		
		fread(&offset,sizeof(int),1, arq2);

		*index2 = (INDICE*) realloc( *index2, sizeof(INDICE) * (cont+1) );

		(*index2)[cont].cnpj = cnpj;           
		(*index2)[cont].offset = offset;

		cont++;

	}

	fclose(arq2);
	cont = 0;

	arq3 = fopen("index3.bin", "r+");
	
	printf("\nCarregando o arquivo de índice 3...\n");

	while(fgetc(arq3) != EOF){

		fseek(arq3, -1, SEEK_CUR);

		cnpj = (char*) malloc(sizeof(char) * 19);
		cnpj[18] = '\0';

		fread(cnpj, sizeof(char), 18, arq3);
		fread(&offset,sizeof(int),1, arq3);

		*index3 = (INDICE*) realloc( *index3, sizeof(INDICE) * (cont+1) );

		(*index3)[cont].cnpj = cnpj;           
		(*index3)[cont].offset = offset;

		cont++;

	}

	fclose(arq3);

	printf("Arquivos de índice carregados com succeso...\n");

	return cont;

}

//Função para gerar índice
int criar_indices(INDICE **index1, INDICE **index2, INDICE **index3, int *cont){
	
	FILE *arq, *arq1;
	int contoffset = 4;
	char c, *cnpj1, *cnpj2, *cnpj3;

	arq1 = fopen("index1.bin", "r");

	if(arq1 != NULL && *index1 == NULL && *index2 == NULL && *index3 == NULL ){
	
		printf("Os arquivos de índice já existem.\nCarregando....\n");
		*cont = carregaIndices(index1, index2, index3);
		fclose(arq1);
		return 1;

	}
	
	if(*index1 != NULL || *index2 != NULL || *index3 != NULL ){
		printf("Arquivo de indice já gerado\n");
		return 0;
	}
	
	arq = fopen("file1.bin", "r");  
	
	*cont = 0;

	if(arq != NULL){														//verifica se o arquivo existe
		
		fseek(arq,4,SEEK_CUR);
		
		while(fgetc(arq)!=EOF){
			
			fseek(arq,-1,SEEK_CUR);
			
			*index1 = (INDICE*) realloc( *index1, sizeof(INDICE) * (*cont+1) );
			*index2 = (INDICE*) realloc( *index2, sizeof(INDICE) * (*cont+1) );
			*index3 = (INDICE*) realloc( *index3, sizeof(INDICE) * (*cont+1) );
			
			cnpj1 = (char*) malloc (sizeof(char) * 19);
			cnpj1[18] = '\0';
			
			cnpj2 = (char*) malloc (sizeof(char) * 19);
			cnpj2[18] = '\0';
			
			cnpj3 = (char*) malloc (sizeof(char) * 19);
			cnpj3[18] = '\0';
			
			fread(cnpj1, sizeof(char), 18, arq);
			
			strcpy(cnpj2, cnpj1);
			strcpy(cnpj3, cnpj1);
			
			(*index1)[*cont].cnpj = cnpj1;           
			(*index1)[*cont].offset = contoffset; 
			(*index2)[*cont].cnpj = cnpj2;           
			(*index2)[*cont].offset = contoffset; 
			(*index3)[*cont].cnpj = cnpj3;           
			(*index3)[*cont].offset = contoffset;           
			(*cont)++;	
			
			contoffset += 18;
			
			c ='a';
			
			while(c != '#'){
				c = fgetc(arq);
				contoffset++;
			}
			
		}		
		
		ordeneIndice(*index1, *cont);
		ordeneIndice(*index2, *cont);
		ordeneIndice(*index3, *cont);
		

		fclose(arq);
	
	}else{
		printf("\nFalha ao abrir o arquivo, arquivo de dados inexistente ou vazio.\n");
		return 0;
	}

	return 1;

}
//Função para printar o arquivo de índice
int print_indice(INDICE *index1, int tam){

	int i;
	
	for(i = 0; i < tam; i++)
		printf("%s %d\n", index1[i].cnpj, index1[i].offset); 
	
	return 1;
}
//Função para listar todos os registros removidos
void listar_removidos(){

	int topo;	
	int node;

	int i = 0;
	int size;
	int aux;

	FILE *fp = fopen("file1.bin","r");
	if(fp == NULL) {
		printf("\nFalha ao abrir o arquivo. Arquivo de dados inexistente ou vazio\n");
		return;
	}

	fread(&topo,sizeof(int),1,fp); //lendo o registro de cabecalho
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
//Função para remover um registro com first fit
int remove_registro(char *cnpj, INDICE **index1, int *tam){
	
	int pos, cont = 0, cabecalho;
	FILE *arq1;
	char c = asterisco;
	printf("TAM :%d \n", *tam);
	if((*tam) <= 0){
		printf("\nErro. Arquivo de dados inexistente ou vazio.\n");
		return 0;
	}
	
	pos = buscaBinaria(*index1, 0, *tam, cnpj);
	printf("Aqui\n");
	
	arq1 = fopen("file1.bin", "r+");	
	
	if (pos == -1){
		printf("CNPJ não encontrado");
		return 0;
	}

	if(arq1 != NULL){

		fread(&cabecalho, sizeof(int), 1, arq1);//leu  o registro de cabeçalho
								
		fseek(arq1, (*index1)[pos].offset , SEEK_SET);						// vai ate offset
		
		fwrite(&c, sizeof(char), 1, arq1);								// escreve *
		
		while(c != hashtag){												// le até #
			cont++;
			c = fgetc(arq1);
		}

		printf("AQUI 4\n");
		fseek(arq1,-cont,SEEK_CUR);										// volta para frente do *
		
		cont += 1;														//marca tamanho
		
		fwrite(&cont, sizeof(int), 1, arq1);							//escreve o tamanho
		
		fwrite(&cabecalho, sizeof(int), 1, arq1);						// escreve o que estava no cabeçalho
		
		fseek(arq1, 0, SEEK_SET);										// volta pro cabecalho
				
		fwrite(&((*index1)[pos].offset), sizeof(int), 1, arq1);				// escreve a pos offset
		printf("AQUI 3\n");
		removeIndex(index1, tam, pos); //remove do arquivo de índice
		printf("AQUI 2\n");
	
		fclose(arq1);
		
	}else{
		printf("falha ao arir o arquivo");
		return 0;
	}
	
	return 1;
}
//Função para criar um novo registro manualmente
REGISTRO *cria_registro(int *tam ){
	
	REGISTRO *myregister = (REGISTRO *)malloc(sizeof(REGISTRO));

	printf("Digite o cnpj:\n");
	myregister->cnpj = readline(stdin);
	myregister->cnpj = (char *)realloc(myregister->cnpj, sizeof(char) * 19);
	myregister->cnpj[18] = '\0';

	printf("Digite o nome social:\n");
	myregister->nomesocial = readline(stdin);

	printf("Digite o nome fantasia:\n");
	myregister->nomefantasia = readline(stdin);
	
	printf("Digite a data de registro:\n");
	myregister->dataregistro = readline(stdin);
	myregister->dataregistro = (char *)realloc(myregister->dataregistro, sizeof(char) * 19);
	myregister->dataregistro[18] = '\0';
	
	
	printf("Digite a data de cancelamento:\n");
	myregister->datacancelamento = readline(stdin);
	myregister->datacancelamento = (char *)realloc(myregister->datacancelamento, sizeof(char) * 19);
	myregister->datacancelamento[18] = '\0';

	if(strcmp(myregister->datacancelamento,"null") == 0)
		strcpy(myregister->datacancelamento,"00/00/00"); 
		
	printf("Digite o motivo do cancelamento:\n");
	myregister->motivocancelamento = readline(stdin);
	
	printf("Digite o nome da empresa:\n");
	myregister->nomeempresa = readline(stdin);

	printf("Digite o cnpj auditor:\n");
	myregister->cnpjauditor = readline(stdin);
	myregister->cnpjauditor = (char *)realloc(myregister->cnpjauditor, sizeof(char) * 19);
	myregister->cnpjauditor[18] = '\0';
	
	*tam = 52 + strlen(myregister->motivocancelamento)+ 1 + strlen(myregister->nomesocial) + 1 + strlen(myregister->nomefantasia) + 1 + strlen(myregister->nomeempresa) + 1 + 1;

	return myregister;
}

//Função para inserir um registro  novo com first fit
int insere_registro(FILE *arq, REGISTRO *novo){
	
	char separador = cifrao, separador2 = hashtag;
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
//Função para inserir no índice
int insereIndice(INDICE **indexArq, int *n, char * cnpj, int offset){

	printf("AQUI 2: %d\n", *n);

	*indexArq = (INDICE *)realloc(*indexArq, sizeof(INDICE)*((*n)+1));
	
	if(*indexArq != NULL){

		(*indexArq[*n]).cnpj = cnpj;
		(*indexArq[*n]).offset = offset;
		(*n)++;

		return 1;	
	}
	
	return 0;
}
//Função para insrir registro com first-fit
int inserir_first(INDICE **index1, int *tam, int regtam,  REGISTRO *novo){
	
	FILE *arq1;
	int offset, node, size, aux, aux2 = -1, anterior;
	char separador2 = hashtag;
	
	arq1 = fopen("file1.bin", "r+");
	
	if(arq1 != NULL){
																		// pega o valor do cabeçalho
		fread(&node, sizeof(int), 1, arq1);								// anda nos removidos
		
		anterior = node;
		
		while(node != -1){
			
			fseek(arq1, node + 1, SEEK_SET);								//cursor no começo do arquivo vai até onde o node aponta --- o +1 serve para pular o asterisco
			fread(&size,sizeof(int),1, arq1);							//nsize vai receber o tamanho do registro removido deste nó
			fread(&offset,sizeof(int),1, arq1);
			
			if(size == regtam){
				
				printf("O registro cabe certinho, não haverá fragmentação\n");
			
				fseek(arq1,-9,SEEK_CUR);//volta para antes do *
				printf("inserindo no arquivo de dados....\n");
				insere_registro(arq1, novo);//insere o registro
				
				printf("inserindo no índice....\n");
				insereIndice(index1, tam,  novo->cnpj, anterior);//insere no índice

				printf("ordenando o índice....\n");
				ordeneIndice(*index1, *tam);//ordene o índice

				printf("rearrajando os ponteiros da lista....\n");
				if(offset != -1){//caso o próximo não for o último da lista, coloca ele no topo da lista
					fseek(arq1, 0, SEEK_SET);						// vai até o anterior e pula o * e o tamanho do reg
					fwrite(&offset , sizeof(int), 1, arq1);					// escreve novo next
				
				}else{//caso o próximo for o último na lista, atualiza o cabeçalho com -1
					fseek(arq1, 0, SEEK_SET);
					fwrite(&aux2 , sizeof(int), 1, arq1);
				}
				
				fclose(arq1);
				return 1;
				
			}
			else if(size - regtam > 10){	
				
				printf("O registro cabe mas, haverá fragmentação\n");							
				
				fseek(arq1,-8,SEEK_CUR);								// volta para frente do *
				
				aux = size - regtam;
				fwrite(&aux , sizeof(int), 1, arq1);
				
				printf("tratando a fragmentação interna...\n");
				fseek(arq1, 4,SEEK_CUR);								// vai até depois do indicador do prox
				fseek(arq1, aux-10, SEEK_CUR);							// vai até o tamanho novo menos o tamanho ja percorrido menos o local onde vamos colocar o #
				fwrite(&separador2 , sizeof(char), 1, arq1);			//escreve o delimitador de registro
				
				printf("inserindo no arquivo de dados....\n");
				insere_registro(arq1, novo);

				printf("inserindo no índice....\n");
				insereIndice(index1, tam,  novo->cnpj, anterior + aux);

				printf("ordenando o índice....\n");
				ordeneIndice(*index1, *tam);
				
				printf("tratando a fragmentação externa...\n");
				
				if(aux < 52){//caso tenha sobrado um tamanho menor do que o tamanho mínimo de um registro, trata como fragmentação externa
					
					printf("há fragmentação externa...\n");
					if(offset != -1){
						fseek(arq1, 0, SEEK_SET);						// vai até o anterior e pula o * e o tamanho do reg
						fwrite(&offset , sizeof(int), 1, arq1);					// escreve novo next
					}else{
						fseek(arq1, 0, SEEK_SET);
						fwrite(&aux2 , sizeof(int), 1, arq1);
					}
				}
				
				fclose(arq1);
				return 1;
						
			}else if(size - regtam <= 10 && size - regtam >= 2){			
			
				printf("O registro cabe mas, haverá fragmentação externa\n");
				
				printf("tratando a fragmentação interna...\n");
				fseek(arq1,-8,SEEK_CUR);								// volta para frente do *
				aux = size - regtam;
				fseek(arq1, aux-2 ,SEEK_CUR);							// avança até antes do #							
				fwrite(&separador2 , sizeof(char), 1, arq1);			// escreve #
				
				printf("inserindo no arquivo de dados....\n");
				insere_registro(arq1, novo);
				
				printf("inserindo no índice....\n");
				insereIndice(index1, tam,  novo->cnpj, anterior + aux);
				
				printf("ordenando o índice....\n");
				ordeneIndice(*index1, *tam);
				
				printf("rearrajando os ponteiros da lista....\n");
				if(offset != -1){
					fseek(arq1, 0, SEEK_SET);						// vai até o anterior e pula o * e o tamanho do reg
					fwrite(&offset , sizeof(int), 1, arq1);					// escreve novo next
				}else{
					fseek(arq1, 0, SEEK_SET);
					fwrite(&aux2 , sizeof(int), 1, arq1);
				}
				
				fclose(arq1);
				return 1;
			}
			
			anterior = offset;
			node = offset;
			
		}

		printf("Não coube em nenhum dos registros removidos. Inserindo no final do arquivo de dados....\n");
		fseek(arq1, 0, SEEK_END);
		aux = ftell(arq1);
		insere_registro(arq1, novo);

		printf("inserindo no índice....\n");
		insereIndice(index1, tam,  novo->cnpj, aux);

		printf("ordenando o índice....\n");
		ordeneIndice(*index1, *tam);
		fclose(arq1);
		return 1;
		
	}else{
		printf("\nFalha ao arir o arquivo. Arquivo de dados inexistente.\n");
		return 0;
	}

}
//Função para listar estatísticas
int estatistica(INDICE *index1, int tam1, INDICE *index2, int tam2, INDICE *index3, int tam3){

	int i, tam;
	char c;
	
	printf("tamanho índíce 1: %d\n", tam1);
	printf("tamanho índice 2: %d\n", tam2);
	printf("tamanho índice 3: %d\n", tam3);
	
	tam = tam1;
	
	if(tam < tam2){
		tam = tam2;
	}
	if(tam < tam3){
		tam = tam3;
	}

	if(tam <= 0 ){
		printf("\nIndíce inexistente\n");
		return 0;
	}
	
	printf("\n\nPara apresentar os registros pressione enter. Para sair pressione q. \n\n");
	
	printf("Registros: \t\t indice1 \t\t indice 2 \t\t indice 3\n\n");
	
	for(i = 0; i < tam; i++){
		
	 
		printf("%d \t->", i); 
		if(tam1 >i){
			printf("\t cnpj:%s \t off-set:%d \t |",  index1[i].cnpj, index1[i].offset);
		}else{
			printf("\t cnpj:------------------ \t ------------- \t |");
		}
		if(tam2 >i){
			printf("\t cnpj:%s \t off-set:%d \t |",  index2[i].cnpj, index2[i].offset);
		}else{
			printf("\t cnpj:------------------ \t ------------- \t |");
		}
		if(tam3 >i){
			printf("\t cnpj:%s \t off-set:%d \t \n",  index3[i].cnpj, index3[i].offset);
		}else{
			printf("\t cnpj:------------------ \t ------------- \t |");
		}
		
		scanf("%c", &c);
		
		if(c == 'q'){
			return 0;
		}
	
	}
											
	return 1;
}
//Função para gravar o índice no disco
int gravaIndice(INDICE *index1, int tam1, INDICE *index2, int tam2, INDICE *index3, int tam3){
	
	int tam = tam1;
	int i;
	FILE *arq1, *arq2, *arq3;

	if(tam < tam2){
		tam = tam2;
	}
	if(tam < tam3){
		tam = tam3;
	}

	if(tam > 0 ){

		arq1 = fopen("index1.bin","w");
		arq2 = fopen("index2.bin","w");
		arq3 = fopen("index3.bin","w");

		for(i = 0; i < tam; i++){
			
			fwrite(index1[i].cnpj,sizeof(char), 18, arq1);
			fwrite(&(index1[i].offset),sizeof(int), 1, arq1);

			fwrite(index2[i].cnpj,sizeof(char), 18, arq2);
			fwrite(&(index2[i].offset),sizeof(int), 1, arq2);

			fwrite(index3[i].cnpj,sizeof(char), 18, arq3);
			fwrite(&(index3[i].offset),sizeof(int), 1, arq3);
		}

		fclose(arq1);
		fclose(arq2);	
		fclose(arq3);

		return 1;	
	}

	return 0;

}

