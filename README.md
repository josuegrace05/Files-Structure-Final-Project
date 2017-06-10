# Files-Structure-Final-Project
This project is intended to put into practice all the concepts of files structure

1.Organização de arquivos

1.1 Campos de tamanho de fixo
	
	->CNPJ(18)
	->dataRegistro(8)
	->dataCancelamento(8)
	->CNPJauditor(18)

1.2 Campos de tamanho variável
	
	->nomdeSocial
	->nomeFantasia
	->motivoCancelamento
	->nomeEmpresa

1.3 Organização de registros e campos

	->Total dos campos : 8
	->Organização híbrida de campos. Os campos de tamanho varíavel têm delimitadores entre eles.
	->Os registros são de tamnho varíavel com delimitadores entre registros.
Funcionalidades do programa

(1) Apresentar uma interface. (2) Gerar 3 arquivos de saida iguais a partir do arquivo de entrada dado.Permitir a leitura dos registros dos arquivos de saida. (3) Criar um indice primário i sobre o campo CNPJ para cada arquivo de saida i (i = 1 até 3) depois que os mesmos estiverem criados.Os arquivos de índice gerados são iguais. (4)Remover logicamente os registros dos arquivos de saída.

 -->Passos:

 1--> O usuário indica o valor para o campo CNPJ.
 2--> Para cada arquivo de saída i (i = 1 até 3):
 	 -->busca registro desesjado usando-se o índice primário correspondente. 
 	 -->remover logicamente o registro do arquivo de dados
 	 -->remover fisicamente a entrada correspondente do arquivo de índices.
 	 -->mostrar uma mensagem informando se teve sucesso ou não na operação.
(5) Inserir registros adicionais com reaproveitamento dinâmico do espaço de ergistros logicamente removidos.

 -->Estratégias	de alocação a serem usadas:

 1-->para o arquivo de saída 1: first-fit sem ordenação da lista de registros removidos, com tratamento de fragmentação interna e, sem realizar a junção de espaços vazios adjacentes.

 2-->para o arquivo de saída 2: best-fit com ordenação crescente da lista de registros removidos, com tratamento da fragmentação interna, e sem realizar a jnção de espaços vazios adjacentes.

 3-->para o arquivo de saída 3: worst-fit com oredeanção decrescente da lista de registros removidos, com tratamento da fragmentação interna, e sem realizar a junção de espaços vazios adjacentes.

 -->Passos:

 1--> O usuário indica o registro a ser removido ou inserido.
 2--> Para arquivo de saída i (i = 1 até 3):
 	--> inserir o registro desejado no arquivo de saída.
 	--> inserir a sua entrada correspondente no arquivo de índice.
 	--> informar se a operação teve sucesso ou não na inserção/remoção.
