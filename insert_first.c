int inserir_first(INDICE *index1, int *tam, int regtam,  REGISTRO *novo){
	
	FILE *arq1;
	int offset, node, size, aux, aux2 = -1, anterior;
	char separador2 = '#';
	
	arq1 = fopen("file1.bin", "r+");
	
	if(arq1 != NULL){
																		// pega o valor do cabecalho
		fread(&node, sizeof(int), 1, arq1);								// anda nos removidos
		
		anterior = node;
		
		while(node != -1){
			
			fseek(arq1,node + 1,SEEK_SET);								//cursor no começo do arquivo vai até onde o node aponta --- o +1 serve para pular o asterisco
			fread(&size,sizeof(int),1, arq1);							//nsize vai receber o tamanho do registro removido deste nó
			fread(&offset,sizeof(int),1, arq1);
			
			if(size == regtam){
				
				printf("entrou caso igual\n");
			
				fseek(arq1,-9,SEEK_CUR);
				printf("1\n");								//volta para antes do *
				insere_registro(arq1, novo);
				printf("2\n");
				//insereIndice(index1, tam,  novo->cnpj, anterior);
				printf("3\n");
				//ordeneIndice(index1, *tam);
				printf("4\n");				
				if(offset != -1){//caso o próximo não for o último da lista, coloca ele como cabeçalho
					fseek(arq1, 0, SEEK_SET);						// vai até o anterior e pula o * e o tamanho do reg
					fwrite(&offset , sizeof(int), 1, arq1);					// escreve novo next
				
				}else{//caso o próximo for o último na lista, atualiza o cabeçalho com -1
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
				
				//precisa tratar o caso da frag ext aqui
				//insereIndice(index1, tam,  novo->cnpj, anterior + aux);
				//ordeneIndice(index1, *tam);
				
				fclose(arq1);
				return 1;
						
			}else if(size - regtam <= 10 && size - regtam >= 2){			
			
				printf("entrou caso entre 2 e 10\n");
			
				fseek(arq1,-8,SEEK_CUR);								// volta para frente do *
				
				aux = size - regtam;
				
				fseek(arq1, aux-2 ,SEEK_CUR);							// avança até antes do #							
				
				fwrite(&separador2 , sizeof(char), 1, arq1);			// escreve #
						
				insere_registro(arq1, novo);
				//insereIndice(index1, tam,  novo->cnpj, anterior + aux);
				//ordeneIndice(index1, *tam);
				
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
			
			
			//printf("Size: %d  Offset :%d  Next :%d\n",size,node,offset);
			anterior = offset;
			node = offset;
			
		}
	
		fseek(arq1, 0, SEEK_END);
		aux = ftell(arq1);
		insere_registro(arq1, novo);
		//insereIndice(index1, tam,  novo->cnpj, aux);
		//ordeneIndice(index1, *tam);
		fclose(arq1);
		
		return 1;
	
	}else{
		printf("falha ao arir o arquivo");
	}
	
	
	return 0;
}