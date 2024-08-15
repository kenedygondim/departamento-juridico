#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

//Bibliotecas 
#include "stdio.h" //Biblioteca padr�o de entrada e sa�da
#include "string.h" //Biblioteca para manipula��o de strings
#include "stdlib.h" //inclui fun��es para aloca��o de mem�ria din�mica, etc.

//M�dulos
#include "estagiario.h"
#include "global.h"
#include <stdbool.h>

//Vari�veis globais
Estagiario estagiario; //Vai armazenar o estagi�rio
Estagiario* estagiarios; //Vai armazenar o array de estagi�rios
FILE* arquivo; //Ponteiro para o arquivo



void adicionarEstagiario() {
	//Vari�veis tempor�rias
	char tempTipoEstagiario;

	//Vai setar o c�digo do estagi�rio diretamente.
	//Diferente da triagem, estou passando a refer�ncia do estagi�rio.
	//Melhor abordagem que a usada no m�dulo de triagem, mas mesmo efeito.
	gerarCodEstagiario(&estagiario);

	printf("\n-----------INSER��O DE ESTAGI�RIO NO SISTEMA -------------\n");

	//Pede para inserir os dados do estagi�rio
	printf("\nInsira o nome do estagi�rio: ");
	fgets(estagiario.nome, sizeof(estagiario.nome), stdin);
	estagiario.nome[strcspn(estagiario.nome, "\n")] = '\0';
	printf("\nInsira o n�mero de telefone do estagi�rio: ");
	fgets(estagiario.numeroTelefone, sizeof(estagiario.numeroTelefone), stdin);
	estagiario.numeroTelefone[strcspn(estagiario.numeroTelefone, "\n")] = '\0';
	printf("\nInsira o email do estagi�rio: ");
	fgets(estagiario.email, sizeof(estagiario.email), stdin);
	estagiario.email[strcspn(estagiario.email, "\n")] = '\0';

	// Valida��o do tipo de estagi�rio, enquanto n�o for A, P ou V, pede para inserir novamente
	do {
		printf("\nInsira o tipo de estagi�rio: ");
		tempTipoEstagiario = getchar();
		limparBuffer();
	} while (tempTipoEstagiario != 'A' && tempTipoEstagiario != 'P' && tempTipoEstagiario != 'V');
	// Atribui o tipo de estagi�rio validado ao estagi�rio
	estagiario.tipo = tempTipoEstagiario;

	//Abre, verifica se o arquivo foi aberto, escreve e fecha o arquivo
	fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\ESTAGIARIOS.DAT", "a+b");
	if (arquivo == NULL) {
		printf("Erro ao abrir ESTAGIARIOS.DAT\n");
		system("pause");
		exit(0);
	}
	//Escreve o estagi�rio no arquivo
	fwrite(&estagiario, sizeof(Estagiario), 1, arquivo);
	//Fecha o arquivo
	fclose(arquivo);

	printf("\nESTAGI�RIO ADICIONADO NO SISTEMA COM SUCESSO!\n");
	//Imprime o relat�rio do estagi�rio adicionado
	gerarRelatorioEstag(&estagiario);

	printf("\n--------------------------------------------------------\n");
}

//Retorna o �ltimo c�digo de estagi�rio cadastrado.
//Mesma l�gica do c�digo de triagem/atendimento.
int retornarUltimoCodEstag() {
	//Declara a vari�vel que vai armazenar o �ltimo estagi�rio do arquivo
	Estagiario ultimoEstagiario;
	//Abre o arquivo
	arquivo = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\ESTAGIARIOS.DAT", "a+b");
	//Se n�o conseguir abrir, exibe a mensagem de erro e encerra o programa
	if (arquivo == NULL) {
		printf("N�o foi poss�vel abrir ESTAGIARIOS.DAT");
		system("pause");
		exit(0);
	}
	//Vai para o final do arquivo
	fseek(arquivo, -1 * sizeof(Estagiario), SEEK_END);
	//L� o �ltimo estagi�rio e armazena na vari�vel ultimoEstagiario
	fread(&ultimoEstagiario, sizeof(Estagiario), 1, arquivo);
	//Se o arquivo estiver vazio, seta o c�digo do estagi�rio como 0
	if (feof(arquivo)) ultimoEstagiario.codeEstag = 0;
	//Fecha o arquivo
	fclose(arquivo);
	//Retorna o c�digo do �ltimo estagi�rio (ou zero) 
	return ultimoEstagiario.codeEstag;
}

//Basicamente seta o c�digo do estagi�rio como o �ltimo c�digo de estagi�rio + 1
void gerarCodEstagiario(Estagiario* estagiario) {
	//chama a fun��o que retorna o �ltimo c�digo de estagi�rio
	int ultimoCod = retornarUltimoCodEstag();
	//Seta o c�digo do estagi�rio como o �ltimo c�digo de estagi�rio + 1
	estagiario->codeEstag = ultimoCod + 1;
}

//Armazena todos os estagi�rios cadastrados que est�o no arquivo ESTAGIARIOS.DAT em 
//um array de Estagiario
int obterTodosOsEstagiarios()
{
	//Chama a fun��o que retorna o �ltimo c�digo de estagi�rio para descobrir quantos registros existem
	int ultimoCod = retornarUltimoCodEstag();

	int count = 0;

	//Abre o arquivo
	arquivo = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\ESTAGIARIOS.DAT", "r+b");
	//Se n�o conseguir abrir, exibe a mensagem de erro e encerra o programa
	if (arquivo == NULL)
	{
		printf("Erro ao abrir ESTAGIARIOS.DAT\n");
		system("pause");
		exit(0);
	};

	//Faz a aloca��o de mem�ria para o array de estagi�rios
	estagiarios = (Estagiario*)malloc(ultimoCod * sizeof(Estagiario));

	//Se n�o conseguir alocar a mem�ria, exibe a mensagem de erro e encerra o programa
	if (estagiarios == NULL) {
		printf("Erro interno. (FALHA NA ALOCA��O DE MEM�RIA)\n");
		system("pause");
		exit(0);
	}

	//Enquanto n�o chegar no final do arquivo, l� os registros e armazena no array de estagi�rios
	while (!feof(arquivo)) {
		fread(&estagiario, sizeof(estagiario), 1, arquivo);
		if (!feof(arquivo)) {
			estagiarios[count] = estagiario;
			count++;
		}
	}

	//Fecha o arquivo
	fclose(arquivo);

	//retorna a quantidade de estagi�rios cadastrados para ser usada em outras fun��es
	return count;
}

//Utilizada para mostrar todos os estagi�rios cadastrados no sistema no console
void mostrarTodosEstagiarios() {
	//Chama a fun��o que armazena todos os estagi�rios cadastrados no array de estagi�rios e retorna a quantidade de estagi�rios
	int count = obterTodosOsEstagiarios();

	printf("\n-----------LISTA DE ESTAGI�RIO NO SISTEMA -------------\n");

	if (count == 0) {
		printf("Nenhum estagi�rio cadastrado no DJ.\n\n");
	}
	else {
		//Se houver estagi�rios cadastrados, imprime o relat�rio de cada um por meio de um for b�sico
		for (int i = 0; i < count; i++) {
			gerarRelatorioEstag(&estagiarios[i]);
			if (i < count - 1) {
				printf("\n          ����������������������         ");
			}
		};
	}

	printf("\n--------------------------------------------------------\n");

	//Desaloca a mem�ria.
		//Se n�o fizer isso ap�s a execu��o da fun��o, o programa vai consumir mem�ria desnecessariamente.
	free(estagiarios);
}

//Retorna um estagi�rio espec�fico com base no c�digo do estagi�rio
Estagiario retornarEstagiarioEspecifico(int codEstag) {
	//Chama a fun��o que armazena todos os estagi�rios cadastrados no array de estagi�rios e retorna a quantidade de estagi�rios
	int tamanho_vetor = obterTodosOsEstagiarios();

	//Declara as vari�veis de busca bin�ria
	int inicio = 0, fim = tamanho_vetor - 1, meio;

	//Vari�vel de controle
	bool encontrado = false;

	//Realiza a busca bin�ria
	while (inicio <= fim)
	{
		meio = (inicio + fim) / 2;
		if (estagiarios[meio].codeEstag == codEstag) {
			encontrado = true;
			//Encontrou, retornou.
			return estagiarios[meio];
		}
		if (estagiarios[meio].codeEstag > codEstag)
			fim = meio - 1;
		else
			inicio = meio + 1;
	}

	//Se n�o encontrar o estagi�rio, exibe a mensagem.
	if (!encontrado) {
		printf("Nenhum estagi�rio encontrado com o c�digo: %d\n\n", codEstag);
		system("pause");
	}

	//Desaloca a mem�ria.
	//Se n�o fizer isso ap�s a execu��o da fun��o, o programa vai consumir mem�ria desnecessariamente.
	free(estagiarios);

	//Retorna um estagi�rio inv�lido para verifica��o em outras partes do c�digo
	//Talvez n�o seja a melhor abordagem, mas � funcional.
	Estagiario estag_invalido;
	estag_invalido.codeEstag = -1;
	return estag_invalido;
}

//Gera o relat�rio do estagi�rio
void gerarRelatorioEstag(Estagiario* estagiario) {
	printf("\nC�digo:         %i\n", estagiario->codeEstag);
	printf("Nome:           %s\n", estagiario->nome);
	printf("N�mero:         %s\n", estagiario->numeroTelefone);
	printf("Email:          %s\n", estagiario->email);

	switch (estagiario->tipo)
	{
	case 'A':
		printf("Tipo:           Atendente\n");
		break;
	case 'P':
		printf("Tipo:           Plantonista\n");
		break;
	case 'V':
		printf("Tipo:           Vareiro\n");
		break;
	default:
		break;
	}
}