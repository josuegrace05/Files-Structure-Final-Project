
Galera, para esse projeto, eu proponho usar muito git e github. Então para isso, eu vou descrever aqui alguns comandos básicos que nós vamos usar.

Primeiro, se você está usando Windows, você pode baixar o terminal do git para Windows. Segue esse link https://github.com/git-for-windows/git/releases/tag/v2.13.0.windows.1

Para quem usa Linux, ele geralmente já tem o git instalado. Se não tiver, basta você fazer sudo apt install git no terminal.

Isso feito, aqui seguem os comandos básicos que nós vamos usar.

1. Dar as configurações básicas para se identificar:

	git config --global user.name "myUsername" --> configura seu username 
	git config --global user.email "myEmail"   --> configura seu email
	git config -l --> Para ver suas configurações

2. Initializar o controle de versão para um repositório
	
	git init

3. Salvar as modificações feitas no repositório
	
	git add [o arquivo] --> adiciona as modificações do arquivo
	git add *[.extensão] --> adiciona as modificações feitas em todos arquivos com extensão definida
	git . --> adiciona as modificações feitas em todos os arquivos do diretório

4. Commentar suas modificações

	git commit -m "seu comentaŕio" --> Dá um commit/comentário nas modificações feitas até aqui. Isso é como se você tirasse uma foto do estado atual do seu trablaho. Muito importante!

	git log --> Vizualiza todos os commit feitos.

	git commit --> Esse comando é quando você tem uma descrição muito longa. Ele abre um editor de texto para você escrever seu commit.

5. Ver o estado do seu repositório

	git status --> Útil para saber quais são as modificações do repositório. O git  informa para você se já  salvou e comentou suas modificações.

6. Clonar um repositório do github

	git clone [url] --> Quando você quer clonar um repositório existente do github no seu diretório. Para pegar a url, basta ir no repositório no github, clicar no botão clone or download, aí vai aparecer a url.

7. Atualizar seu diretório git com os dados que estão no repositório no github
	
	git pull origin master --> Você recupera os dados que estão no repositório github para seu diretório local.

8. Atualizar o repositório github com os dados do seu diretório local
	
	git push origin master --> Você envia todos os dados adicionados do seu diretório para o repositório no github

9. Criar e manipular branches
	
	git branch "nome da branch" --> Cria uma branch. Suponha que você quer fazer uma tarefa específica do projeto. Você não quer mexer com o projeto principal e você quer fazer suas modificações num rascunho por exemplo. Você cria uma outra branch onde você vai trabalhar. Isto é uma boa prática no desenvolviemnto de um projeto.

 	git branch --> Diz em qual branch você está.

 	git branch --list --> lista todas as branches.

 	git checkout "nome da branch" --> Ir para uma branch.

 10. Juntar as branches

 	git merge "nome da branche" --> Suponha que você acabou de fazer suas modificações no rascunho e quer colocar à limpo. Você volta na branch principal "master" fazendo : git checkout master. E em seguida faz : git merge "nome da branch".

 11. Consultar o manual de utilização de um comando git

 	git [comando] --help

 12. Usar o sistema de pull request

 	Imagine, como já comentamos antes, que você criou uma nova branch para você desenvolver uma parte exclusiva do projeto. Agora em vez de você mesmo, depois de ter terminado a tarefa, voltar para a branch principal/master e fazer o merge, você pode usar o sitema de pull request. O que é pull request ?

 	Basicamente é você perguntar para seu colega que está trabalhando no mesmo projeto se ele pode revisar o código que você adicionou; o que ele acha da sua solução por exemplo. Ele vai ver suas modificações, e vai falar por exemplo: "Ta bom, gostei". E ele vai fazer o merge da branch que você criou para a branch principal. Okay, agora como fazer uma pull request ?

 	--> Basta você ir no repositório do github e ir na branch que você criou. Lá vai ter um botão verde "compare & pull request". Clique nesse botão.
 	--> Ele vai abrir um pequeno editor de texto onde você vai poder digitar o texto que você vai andar para seu colega como um email que você manda para alguém. No início do seu texto você pode identificar o seu colega fazendo por exemplo "Oi @username do github do seu colega".
 	--> Fazendo isso, o seu colega vai receber um email e ele vai poder ver a branch que você criou e as modificações que você fez.
 	--> No github, o seu colega pode comentar linha por linha, cada modificações suas.
 	--> E por fim, no github o seu colega poderá ele mesmo fazer um merge da sua branch via um botão verde "merge pull request".   

 Então galera esses são alguns comandos básicos que noś vamos precisar para esse projeto. Qualquer dúvida, é só perguntar.

 @byJosuéGrace
