
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

2. Funcionalidades do programa

	(1) Apresentar uma interface.
	(2) Gerar 3 arquivos de saida iguais a partir do arquivo de entrada dado.Permitir a leitura dos registros dos arquivos de saida.
	(3) Criar um indice primário i sobre o campo CNPJ para cada arquivo de saida i (i = 1 até 3) depois que os mesmos estiverem criados.Os arquivos de índice gerados são iguais.
	(4)Remover logicamente os registros dos arquivos de saída.

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

	*(6) Permitir a vizualização de estatísticas sobre os arquivos de ínidces. Deve se mostrar uma tabela que mostra, para cada índice primário, a quantidade de entradas que ele possui. Permitir também a exibição dos registros dos 3 índices simultaneamente, possibilitando a vizualizalçao das semelhanças e das diferenças existentes entre eles. Caso  a  visualização  dos  índices seja textual, os dados devem ser mostrados de forma organizada na saída padrão para permitir a distinção dos campos e registros, sendo que deve-se permitir a visualização dos  registros,  um  por  vez. O  grupo  também  pode  optar  por  fazer  uma  visualização gráfica  dos  índices. Por  exemplo,  a  visualização  gráfica  pode  ser  feita  por  meio  de tabelas, uma tabela para cada índice.

	(7) Permitir a vizaulização de estatísticas sobre as listas de reigstros rmeovidos. Deve-se exibir uma tabela que mostra, para cada arquivo de dados, a quantidade e elementos  presentes em sua lista de registros removidos. Adicionalmente, a funcioanlidade também deve permitir a vizaulição gráfica de cada lista de registros removidos de cada arquivo de dados, conetendo informações sobre o byte offset e o tamanho do registro removido , bem como o byte offset do próximo registro.

3. Restrições:

	(1) Os arquivos de dados são gravados em disco em modo binário.
	(2) Os nomes dos campos não podem ser alterados nem retirados. Nenhum campo pode ser adicionado. Exxplicar na documentaçãoexterna a escolha do tamanho de cada campo, no caso dos campos de tamanho fixo.
	(3) Tratar os erros e as exceções exibindo-os na tela.
	(4) Os dados devem ser lidos campo a campo. Pode-se usar a serialização(copiar os dados/campos na memória).
	(5) Os arquivos de índices devem ser mantidos em disco. Porém, devem ser carregados na memória RAM e serem usados nela durante a execução do programa.
	(6) Colocar dentro do código fonte os nomes e números USP dos paraticipantes.
	(7) Comentar o código tanto em nível de rotina quanto em nível de varíaveis e blocos funcionais.

4. A documentação externa

	(1) Deve conter a descrição dos principais conceitos usados no trabalho prático, as decisões de projeto e as suas justificativas.
	(2) Deve conter uma capa contendo o nome da instituĩção, o nome do curso, da disciplina, do professor responsável, do trabalho prático, dos participantes e os respectivos números USP assim como a data de entrega do trabalho prático.
	(3) Deve conter um índice listando os nomes das seções que compõem o trabalho prático e as suas respectivas páginas de início.
	(4) Diferentes seções referentes a cada decisão de projeto, seus detalhes e suas justificativas.
	(5) Cópias de telas de interface que explicam o funcionamento do programa.
	(6) Baterias de testes gerando informações que permitam acompanhar a execução do programa.
	(7) Referências bibliográficas se necessário. 

*: Precisamos nos reunir para definirmos esses detalhes.



