#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe


//bibliotecas
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//arquivos
#include "estagiario.h"
#include "global.h"
#include <stdbool.h>

//Vari�veis globais
Estagiario estagiario;
Estagiario* estagiarios;
FILE* arquivo;
char teste;


void adicionarEstagiario() {
	limparBuffer();

	gerarCodEstagiario(&estagiario);

	printf("\n-----------INSER��O DE ESTAGI�RIO NO SISTEMA -------------\n");

	printf("\nInsira o nome do estagi�rio: ");
	fgets(estagiario.nome, sizeof(estagiario.nome), stdin);
	estagiario.nome[strcspn(estagiario.nome, "\n")] = '\0';

	printf("\nInsira o n�mero de telefone do estagi�rio: ");
	fgets(estagiario.numeroTelefone, sizeof(estagiario.numeroTelefone), stdin);
	estagiario.numeroTelefone[strcspn(estagiario.numeroTelefone, "\n")] = '\0';

	printf("\nInsira o email do estagi�rio: ");
	fgets(estagiario.email, sizeof(estagiario.email), stdin);
	estagiario.email[strcspn(estagiario.email, "\n")] = '\0';

	do {
		printf("\nInsira o tipo de estagi�rio: ");
		teste = getchar();
		limparBuffer();
	} while (teste != 'A' && teste != 'P' && teste != 'V');

	estagiario.tipo = teste;

	fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\ESTAGIARIOS.DAT", "a+b");
	fwrite(&estagiario, sizeof(Estagiario), 1, arquivo);
	fclose(arquivo);

	printf("\nESTAGI�RIO ADICIONADO NO SISTEMA COM SUCESSO!\n");

	gerarRelatorioEstag(&estagiario);

	printf("\n--------------------------------------------------------\n");
}

int retornaUltimoCodEstag() {
	Estagiario ultimoEstagiario;
	arquivo = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\ESTAGIARIOS.DAT", "a+b");
	if (arquivo == NULL) {
		printf("N�o foi poss�vel abrir ESTAGIARIOS.DAT");
		system("pause");
		exit(0);
	}
	fseek(arquivo, -1 * sizeof(Estagiario), SEEK_END);
	fread(&ultimoEstagiario, sizeof(Estagiario), 1, arquivo);
	if (feof(arquivo)) ultimoEstagiario.codeEstag = 0;
	fclose(arquivo);
	return ultimoEstagiario.codeEstag;
}

void gerarCodEstagiario(Estagiario* estagiario) {

	int ultimoCod = retornaUltimoCodEstag();
	estagiario->codeEstag = ultimoCod + 1;
}

int obterTodosOsEstagiarios()
{
	int ultimoCod = retornaUltimoCodEstag();
	int count = 0;
	arquivo = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\ESTAGIARIOS.DAT", "r+b");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir ESTAGIARIOS.DAT\n");
		system("pause");
		exit(0);
	};
	estagiarios = (Estagiario*)malloc(ultimoCod * sizeof(Estagiario));
	if (estagiarios == NULL) {
		printf("Erro interno. (FALHA NA ALOCA��O DE MEM�RIA)\n");
		system("pause");
		exit(0);
	}
	while (!feof(arquivo)) {
		fread(&estagiario, sizeof(estagiario), 1, arquivo);
		if (!feof(arquivo)) {
			estagiarios[count] = estagiario;
			count++;
		}
	}
	fclose(arquivo);

	return count;
}

void verTodosEstagiarios() {

	int count = obterTodosOsEstagiarios();

	printf("\n-----------LISTA DE ESTAGI�RIO NO SISTEMA -------------\n");

	if (count == 0) {
		printf("Nenhum estagi�rio cadastrado no DJ.\n\n");
	}
	else {
		for (int i = 0; i < count; i++) {
			gerarRelatorioEstag(&estagiarios[i]);
			if (i < count - 1) {
				printf("\n          ����������������������         ");
			}
		};
	}

	printf("\n--------------------------------------------------------\n");

	free(estagiarios); //desaloca a mem�ria
}

Estagiario verEstagiarioEspecifico(int codEstag) {

	int tamanho_vetor = obterTodosOsEstagiarios();
	int inicio = 0, fim = tamanho_vetor - 1, meio;
	bool encontrado = false;

	//busca bin�ria
	while (inicio <= fim)
	{
		meio = (inicio + fim) / 2;
		if (estagiarios[meio].codeEstag == codEstag) {
			encontrado = true;
			return estagiarios[meio];
		}
		if (estagiarios[meio].codeEstag > codEstag)
			fim = meio - 1;
		else
			inicio = meio + 1;
	}

	if (!encontrado) {
		printf("Nenhum estagi�rio encontrado com o c�digo: %d\n\n", codEstag);
		system("pause");
	}

	free(estagiarios);

	Estagiario estag_invalido;

	estag_invalido.codeEstag = -1;

	return estag_invalido;
}

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