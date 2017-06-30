#include "utils.h"

struct indice{																	//lista adaptada para ser usada como vetor e fila para o trab de grafos
	
	char *cnpj;
	int  offset;
	
};

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
	int aux = 1, convert = 0, number = 0;
	
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
			
			aux = strlen(motivocancelamento)+1;
			fwrite(motivocancelamento , sizeof(char), aux, arq1);
			fwrite(&separador , sizeof(char), 1, arq1);
			fwrite(motivocancelamento , sizeof(char), aux, arq2);
			fwrite(&separador , sizeof(char), 1, arq2);
			fwrite(motivocancelamento , sizeof(char), aux, arq3);
			fwrite(&separador , sizeof(char), 1, arq3);
			
			aux = strlen(nomeempresa)+1;
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
	
	arq = fopen("file3.bin", "r");  
	if(arq==NULL){												//verifica se o arquivo existe
		printf("Arquivo Inexistente");
		return -1;
	}

	while(fgetc(arq)!=EOF){
											//Enquanto o arquivo não chegou ao seu final
		fseek(arq,-1,SEEK_CUR);										//cursor = cursor - 1 para compensar o fgetc()
		
																	//um registro inteiro é printado na tela
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
	//realizar a busca binária para saber qual a posição a ser removida
	free(index[pos].cnpj);

	for(i = pos; i < (*n)-1; i++){
		index[i] = index[i+1];
	}
	(*n)--;

	index = (INDICE*) realloc(index, sizeof(INDICE) * (*n) );
}

int criar_indices(INDICE *index1, INDICE *index2, INDICE *index3){
	
	FILE *arq;
	int cont = 0, contoffset = 0;
	char c, *cnpj;
	
	
	arq = fopen("file1.bin", "r");  
	
	if(arq!=NULL){														//verifica se o arquivo existe
		
		
		
		while(fgetc(arq)!=EOF){
			
			fseek(arq,-1,SEEK_CUR);
			
			index1 = (INDICE*) realloc( index1, sizeof(INDICE) * (cont+1) );
			index2 = (INDICE*) realloc( index2, sizeof(INDICE) * (cont+1) );
			index3 = (INDICE*) realloc( index3, sizeof(INDICE) * (cont+1) );
			cnpj = (char*) malloc ( sizeof(char) * 19); 
			fread(cnpj, sizeof(char), 18, arq);
			cnpj[18] = '\0';
			index1[cont].cnpj = cnpj;           
			index1[cont].offset = contoffset; 
			index2[cont].cnpj = cnpj;           
			index2[cont].offset = contoffset; 
			index3[cont].cnpj = cnpj;           
			index3[cont].offset = contoffset;           
			cont++;	
			
			contoffset += 18;
			
			c ='a';
			
			while(c != '#'){
				c = fgetc(arq);
				contoffset++;
			}
			
		}		
		
		ordeneIndice(index1, cont);
		ordeneIndice(index2, cont);
		ordeneIndice(index3, cont);

	
	}else{
		printf("falha ao arir o arquivo");
	}
	
	return cont;

}

