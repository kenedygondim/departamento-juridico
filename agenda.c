#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe


//Arquivos
#include "agenda.h"
#include "global.h"
#include "advogado.h"
#include "estagiario.h"
#include "disponibilidade.h"


//bilbiotecas
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Variáveis globais
FILE* arquivoAgenda;
Agenda agenda;

void agendarAtendimento() {

	printf("\n----------- AGENDAMENTO DE ATENDIMENTO -------------\n");

	int tempOab;
	Advogado adv;
	int diaSemana = retornarDiaSemana();

	printf("\nATENÇÃO: Só é possível agendar atendimentos para o dia seguinte.\n");
	printf("Advogados disponíveis para amanhã: \n");

	mostrarRelatorioAdvDis();

	do
	{
		printf("\nInsira o número da OAB do advogado que deseja atendimento: ");
		scanf("%i", &tempOab);
		limparBuffer();

		adv = verAdvogadoEspecifico(tempOab);

	} while (adv.oab == -1);

	agenda.oab = tempOab;

	int codEstag;
	Estagiario estag;

	do {
		printf("\nInsira o código do estagiário: ");
		scanf("%i", &codEstag);
		limparBuffer();
		estag = verEstagiarioEspecifico(codEstag);
		if (estag.tipo != 'P')
			printf("\nSomente estagiários plantonistas agendar reuniões.\n");
	} while (estag.tipo != 'P');

	agenda.codEstagiario = codEstag;

	Disponibilidade disp = obterDisponibilidadeEspecifica(agenda.oab, diaSemana + 1);

	if (disp.oab == -1) {
		printf("\nAdvogado não possui disponibilidade para o dia seguinte.\n");
		system("pause");
		return;
	}

	gerarDataAtualMaisUm(agenda.dtAgendada, sizeof(agenda.dtAgendada));
	strcpy(agenda.hrAgendada, disp.horaInicio);

	gerarDataAtual(agenda.dtInscricao, sizeof(agenda.dtInscricao));
	gerarHoraAtual(agenda.hrInscricao, sizeof(agenda.hrInscricao));

	strcpy(agenda.areaDireito, adv.especialidade);

	printf("\nQual tipo de orientação deseja?\n");
	fgets(agenda.tipoOrientacao, sizeof(agenda.tipoOrientacao), stdin);
	agenda.tipoOrientacao[strcspn(agenda.tipoOrientacao, "\n")] = '\0';

	char tempPF;

	do
	{
		printf("\nPrazo fatal? (S/N): ");
		tempPF = getchar();
		limparBuffer();
	} while (tempPF != 'S' && tempPF != 'N');

	if (tempPF == 'S') {
		agenda.prazoFatal = true;
		printf("\nInsira a data do prazo fatal: ");
		fgets(agenda.dtPrazoFatal, sizeof(agenda.dtPrazoFatal), stdin);
		agenda.dtPrazoFatal[strcspn(agenda.dtPrazoFatal, "\n")] = '\0';
	}
	else
		agenda.prazoFatal = false;

	printf("\nObservações: ");
	fgets(agenda.observacoes, sizeof(agenda.observacoes), stdin);
	agenda.observacoes[strcspn(agenda.observacoes, "\n")] = '\0';

	printf("\nNúmero do processo: ");
	fgets(agenda.numProcesso, sizeof(agenda.numProcesso), stdin);
	agenda.numProcesso[strcspn(agenda.numProcesso, "\n")] = '\0';

	arquivoAgenda = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jurídico\\data\\AGENDA.DAT", "a+b");
	fwrite(&agenda, sizeof(Agenda), 1, arquivoAgenda);
	fclose(arquivoAgenda);

	printf("\nATENDIMENTO AGENDADO COM SUCESSO!\n");
	gerarRelatorioAgenda(&agenda);
}

void gerarRelatorioAgenda(Agenda* agenda) {
	printf("\nNúmero da OAB: %i", agenda->oab);
	printf("\nCódigo do estagiário: %i", agenda->codEstagiario);
	printf("\nData de inscrição: %s", agenda->dtInscricao);
	printf("\nHora de inscrição: %s", agenda->hrInscricao);
	printf("\nData agendada: %s", agenda->dtAgendada);
	printf("\nHora agendada: %s", agenda->hrAgendada);
	printf("\nÁrea do direito: %s", agenda->areaDireito);
	printf("\nTipo de orientação: %s", agenda->tipoOrientacao);
	printf("\nPrazo fatal: %s", agenda->prazoFatal ? "Sim" : "Não");
	if (agenda->prazoFatal) printf("\nData do prazo fatal: %s", agenda->dtPrazoFatal);
	printf("\nObservações: %s", agenda->observacoes);
	printf("\nNúmero do processo: %s", agenda->numProcesso);
	printf("\n--------------------------------------------------------\n");
}