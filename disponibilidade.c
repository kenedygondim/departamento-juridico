#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe


//Arquivos

//bilbiotecas
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "global.h"
#include "disponibilidade.h"
#include "advogado.h"


//Variáveis globais
FILE* arquivoDisponibilidade;
Disponibilidade disponibilidade;
Disponibilidade* disponibilidades;
Advogado adv;
int diaSemana;

//2 - Segunda-feira    //1 - Segunda-feira
//3 - Terça-feira      //2 - Terça-feira
//4 - Quarta-feira     //3 - Quarta-feira
//5 - Quinta-feira     ...
//6 - Sexta-feira        


void adicionarDisponibilidade() {
	printf("\n----------- INSERÇÃO DE DISPONIBILIDADE NO SISTEMA -------------\n");

	int tempOAB;
	Advogado adv;

	do {
		printf("Qual o número da OAB do advogado: ");
		scanf("%i", &tempOAB);
		limparBuffer();

		adv = verAdvogadoEspecifico(tempOAB);
	} while (adv.oab == -1);

	disponibilidade.oab = tempOAB;

	int tempDiaSemana;

	do {
		printf("\nQual o dia da semana: ");
		scanf("%d", &tempDiaSemana);
		limparBuffer();
	} while (tempDiaSemana < 2 || tempDiaSemana > 6);

	disponibilidade.diaSemana = tempDiaSemana;

	printf("\nQual o horário de início: ");
	fgets(disponibilidade.horaInicio, sizeof(disponibilidade.horaInicio), stdin);
	disponibilidade.horaInicio[strcspn(disponibilidade.horaInicio, "\n")] = '\0';


	printf("\nQual o horário de término: ");
	fgets(disponibilidade.horaFim, sizeof(disponibilidade.horaFim), stdin);
	disponibilidade.horaFim[strcspn(disponibilidade.horaFim, "\n")] = '\0';


	char tempFormato;

	do {
		printf("\nQual o formato da disponibilidade (R - Remoto / P - Presencial): ");
		tempFormato = getchar();
		limparBuffer();

	} while (tempFormato != 'R' && tempFormato != 'P');

	disponibilidade.formato = tempFormato;

	arquivoDisponibilidade = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jurídico\\data\\DISPONIBILIDADE.DAT", "a+b");

	if (arquivoDisponibilidade == NULL)
	{
		printf("Erro ao abrir DISPONIBILIDADE.DAT\n");
		system("pause");
		exit(0);
	}

	fwrite(&disponibilidade, sizeof(Disponibilidade), 1, arquivoDisponibilidade);
	fclose(arquivoDisponibilidade);

	printf("\nREGISTRO DE DISPONIBILIDADE ADICIONADO NO SISTEMA!\n");
	gerarRelatorioDisponibilidade(&disponibilidade);
	printf("\n--------------------------------------------------------\n");

}

void gerarRelatorioDisponibilidade(Disponibilidade* disponibilidade) {
	printf("\nNúmero da OAB: %i", disponibilidade->oab);

	switch (disponibilidade->diaSemana)
	{
	case 1:
		printf("\nDia da semana: Segunda-feira");
		break;
	case 2:
		printf("\nDia da semana: Terça-feira");
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
	printf("\nHorário de início: %s", disponibilidade->horaInicio);
	printf("\nHorário de término: %s", disponibilidade->horaFim);
	printf("\nFormato: %s", disponibilidade->formato == 'R' ? "Remoto" : "Presencial");
}

void mostrarRelatorioAdvDis() {
	int count = obterTodasDisponibilidades();
	diaSemana = retornarDiaSemana();

	for (int i = 0; i < count; i++) {
		if (disponibilidades[i].diaSemana == diaSemana + 1) {
			adv = verAdvogadoEspecifico(disponibilidades[i].oab);
			gerarRelatorioAdvDis(&disponibilidades[i], adv);
			printf("\n          ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨         ");
		}
	}
}

Disponibilidade obterDisponibilidadeEspecifica(int oab, int diaSemana)
{
	int count = obterTodasDisponibilidades();

	for (int i = 0; i < count; i++)
	{
		if (disponibilidades[i].oab == oab && disponibilidades[i].diaSemana == diaSemana)
		{
			return disponibilidades[i];
		}
	}

	printf("Nenhuma disponibilidade encontrada para o advogado com OAB: %d e dia da semana: %d\n\n", oab, diaSemana);

	Disponibilidade disp_invalida;
	disp_invalida.oab = -1;
	return disp_invalida;
}

int obterTodasDisponibilidades() {
	int count = 0;

	arquivoDisponibilidade = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jurídico\\data\\DISPONIBILIDADE.DAT", "rb");

	if (arquivoDisponibilidade == NULL)
	{
		printf("Erro ao abrir DISPONIBILIDADE.DAT\n");
		system("pause");
		exit(0);
	};

	fseek(arquivoDisponibilidade, 0, SEEK_END);
	// Obtém a posição atual do ponteiro (tamanho do arquivo em bytes)
	long tamanhoArquivo = ftell(arquivoDisponibilidade);
	rewind(arquivoDisponibilidade);
	disponibilidades = (Disponibilidade*)malloc(tamanhoArquivo);

	if (disponibilidades == NULL) {
		printf("Erro interno. (FALHA NA ALOCAÇÃO DE MEMÓRIA)\n");
		system("pause");
		exit(0);
	}

	while (!feof(arquivoDisponibilidade)) {
		fread(&disponibilidade, sizeof(disponibilidade), 1, arquivoDisponibilidade);
		if (!feof(arquivoDisponibilidade)) {
			disponibilidades[count] = disponibilidade;
			count++;
		}
	}

	fclose(arquivoDisponibilidade);

	return count;
}


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
		printf("\nDia da semana:                 Terça-feira");
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
	printf("\nHorário de início:             %s", disponibilidade->horaInicio);
	printf("\nHorário de término:            %s", disponibilidade->horaFim);
	printf("\nFormato:                       %s\n", disponibilidade->formato == 'R' ? "Remoto" : "Presencial");
}