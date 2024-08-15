#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

//Bilbiotecas
#include <stdio.h> //biblioteca padr�o de entrada e sa�da
#include <string.h> //biblioteca para manipula��o de strings
#include <stdbool.h> //biblioteca para usar tipo de dados booleano
#include <stdlib.h> //biblioteca para usar fun��es de aloca��o de mem�ria din�mica

//M�dulos
#include "global.h"
#include "disponibilidade.h"
#include "advogado.h"


//Vari�veis globais
FILE* arquivoDisponibilidade;
Disponibilidade disponibilidade;
Disponibilidade* disponibilidades;
Advogado adv;



void adicionarDisponibilidade() {
	//Vari�veis tempor�rias
	int tempOAB;
	int tempDiaSemana;
	char tempFormato;

	printf("\n----------- INSER��O DE DISPONIBILIDADE NO SISTEMA -------------\n");

	// Enquanto n�o encontrar um advogado com a OAB informada, pede para inserir novamente
	do {
		printf("Qual o n�mero da OAB do advogado: ");
		scanf("%i", &tempOAB);
		limparBuffer();
		adv = retornarAdvogadoEspecifico(tempOAB);
	} while (adv.oab == -1); //  o c�digo -1 � quando n�o encontra o advogado
	// Atribui o n�mero da OAB � disponibilidade
	disponibilidade.oab = tempOAB;

	// Valida��o do dia da semana, enquanto n�o for entre 1 e 5, pede para inserir novamente
	do {
		printf("\nQual o dia da semana: ");
		scanf("%d", &tempDiaSemana);
		limparBuffer();
	} while (tempDiaSemana < 1 || tempDiaSemana > 5);
	// Atribui o dia da semana � disponibilidade
	disponibilidade.diaSemana = tempDiaSemana;

	printf("\nQual o hor�rio de in�cio: ");
	fgets(disponibilidade.horaInicio, sizeof(disponibilidade.horaInicio), stdin);
	disponibilidade.horaInicio[strcspn(disponibilidade.horaInicio, "\n")] = '\0';
	printf("\nQual o hor�rio de t�rmino: ");
	fgets(disponibilidade.horaFim, sizeof(disponibilidade.horaFim), stdin);
	disponibilidade.horaFim[strcspn(disponibilidade.horaFim, "\n")] = '\0';
	// Valida��o do formato, enquanto n�o for R ou P, pede para inserir novamente
	do {
		printf("\nQual o formato da disponibilidade (R - Remoto / P - Presencial): ");
		tempFormato = getchar();
		limparBuffer();

	} while (tempFormato != 'R' && tempFormato != 'P');
	// Atribui o formato � disponibilidade
	disponibilidade.formato = tempFormato;

	// Abre, verifica se o arquivo foi aberto, escreve e fecha o arquivo
	arquivoDisponibilidade = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\DISPONIBILIDADE.DAT", "a+b");
	if (arquivoDisponibilidade == NULL)
	{
		printf("Erro ao abrir DISPONIBILIDADE.DAT\n");
		system("pause");
		exit(0);
	}
	fwrite(&disponibilidade, sizeof(Disponibilidade), 1, arquivoDisponibilidade);
	fclose(arquivoDisponibilidade);

	printf("\nREGISTRO DE DISPONIBILIDADE ADICIONADO NO SISTEMA!\n");
	//Imprime o relat�rio da disponibilidade adicionada
	gerarRelatorioDisponibilidade(&disponibilidade);
	printf("\n--------------------------------------------------------\n");

}


//Mostra o relat�rio de todas as disponibilidades mesclado com as informa��es do advogado
void mostrarRelatorioAdvDis() {
	//Vari�veis tempor�rias
	int diaSemana;

	//chama a fun��o que armazena todas as disponibilidades em um array de Disponibilidade e retorna a quantidade de disponibilidades
	int count = obterTodasDisponibilidades();

	// Obter o dia da semana (hoje)
	diaSemana = retornarDiaSemana();

	//percorre o array de disponibilidades e verifica se a disponibilidade � do dia da semana informado + 1
	//Exemplo: se hoje � segunda-feira, vai ser retornado as disponibilidades de ter�a-feira
	for (int i = 0; i < count; i++) {
		if (disponibilidades[i].diaSemana == diaSemana + 1) {
			adv = retornarAdvogadoEspecifico(disponibilidades[i].oab);
			gerarRelatorioAdvDis(&disponibilidades[i], adv);
			printf("\n          ����������������������         ");
		}
	}
}


//Retorna a disponibilidade espec�fica do advogado com a OAB e do dia da semana informados.
Disponibilidade obterDisponibilidadeEspecifica(int oab, int diaSemana)
{
	//chama a fun��o que armazena todas as disponibilidades em um array de Disponibilidade e retorna a quantidade de disponibilidades
	int count = obterTodasDisponibilidades();

	//percorre o array de disponibilidades e verifica se a disponibilidade � do advogado com a OAB e do dia da semana informados
	for (int i = 0; i < count; i++)
	{
		if (disponibilidades[i].oab == oab && disponibilidades[i].diaSemana == diaSemana)
		{
			return disponibilidades[i];
		}
	}

	//Se n�o encontrar a disponibilidade, exibe a mensagem de erro
	printf("Nenhuma disponibilidade encontrada para o advogado com OAB: %d e dia da semana: %d\n\n", oab, diaSemana);

	//Retorna uma disponibilidade inv�lida para valida��o em outras fun��es
	Disponibilidade disp_invalida;
	disp_invalida.oab = -1;
	return disp_invalida;
}

//Armazena todas as disponibilidades em um array de Disponibilidade
int obterTodasDisponibilidades() {
	int count = 0;

	// Abre o arquivo, verifica se foi aberto
	arquivoDisponibilidade = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\DISPONIBILIDADE.DAT", "rb");

	if (arquivoDisponibilidade == NULL)
	{
		printf("Erro ao abrir DISPONIBILIDADE.DAT\n");
		system("pause");
		exit(0);
	};

	// Vai at� o final do arquivo
	fseek(arquivoDisponibilidade, 0, SEEK_END);
	// Obt�m a posi��o atual do cursor (tamanho do arquivo em bytes)
	long tamanhoArquivo = ftell(arquivoDisponibilidade);
	// Retorna o cursor para o in�cio do arquivo
	rewind(arquivoDisponibilidade);

	//Aloca��o de mem�ria para o array de disponibilidades
	disponibilidades = (Disponibilidade*)malloc(tamanhoArquivo);

	//Verifica se a aloca��o de mem�ria foi bem sucedida
	if (disponibilidades == NULL) {
		printf("Erro interno. (FALHA NA ALOCA��O DE MEM�RIA)\n");
		system("pause");
		exit(0);
	}

	//L� as disponibilidades do arquivo e armazena no array de disponibilidades
	while (!feof(arquivoDisponibilidade)) {
		fread(&disponibilidade, sizeof(disponibilidade), 1, arquivoDisponibilidade);
		if (!feof(arquivoDisponibilidade)) {
			disponibilidades[count] = disponibilidade;
			count++;
		}
	}

	//Fecha o arquivo
	fclose(arquivoDisponibilidade);

	//Retorna a quantidade de disponibilidades 
	return count;
}

//Uma mescla de informa��es do advogado e da disponibilidade, conforme solicitado no trabalho
void gerarRelatorioAdvDis(Disponibilidade* disponibilidade, Advogado adv) {
	printf("\nOAB:                           %i", adv.oab);
	printf("\nAdvogado e disponibilidade:    %s (%s)", adv.nome, adv.especialidade);
	printf("\nEmail:                         %s", adv.email);
	switch (disponibilidade->diaSemana)
	{
	case 1:
		printf("\nDia da semana:                 Segunda-feira");
		break;
	case 2:
		printf("\nDia da semana:                 Ter�a-feira");
		break;
	case 3:
		printf("\nDia da semana:                 Quarta-feira");
		break;
	case 4:
		printf("\nDia da semana:                 Quinta-feira");
		break;
	case 5:
		printf("\nDia da semana:                 Sexta-feira");
		break;
	default:
		break;
	}
	printf("\nHor�rio de in�cio:             %s", disponibilidade->horaInicio);
	printf("\nHor�rio de t�rmino:            %s", disponibilidade->horaFim);
	printf("\nFormato:                       %s\n", disponibilidade->formato == 'R' ? "Remoto" : "Presencial");
}


//Relat�rio de disponibilidade 
void gerarRelatorioDisponibilidade(Disponibilidade* disponibilidade) {
	printf("\nN�mero da OAB: %i", disponibilidade->oab);

	switch (disponibilidade->diaSemana)
	{
	case 1:
		printf("\nDia da semana: Segunda-feira");
		break;
	case 2:
		printf("\nDia da semana: Ter�a-feira");
		break;
	case 3:
		printf("\nDia da semana: Quarta-feira");
		break;
	case 4:
		printf("\nDia da semana: Quinta-feira");
		break;
	case 5:
		printf("\nDia da semana: Sexta-feira");
		break;
	default:
		break;
	}
	printf("\nHor�rio de in�cio: %s", disponibilidade->horaInicio);
	printf("\nHor�rio de t�rmino: %s", disponibilidade->horaFim);
	printf("\nFormato: %s", disponibilidade->formato == 'R' ? "Remoto" : "Presencial");
}