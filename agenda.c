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

//Vari�veis globais
FILE* arquivoAgenda;
Agenda agenda;

void agendarAtendimento() {

	printf("\n----------- AGENDAMENTO DE ATENDIMENTO -------------\n");

	int tempOab;
	Advogado adv;
	int diaSemana = retornarDiaSemana();

	printf("\nATEN��O: S� � poss�vel agendar atendimentos para o dia seguinte.\n");
	printf("Advogados dispon�veis para amanh�: \n");

	mostrarRelatorioAdvDis();

	do
	{
		printf("\nInsira o n�mero da OAB do advogado que deseja atendimento: ");
		scanf("%i", &tempOab);
		limparBuffer();

		adv = verAdvogadoEspecifico(tempOab);

	} while (adv.oab == -1);

	agenda.oab = tempOab;

	int codEstag;
	Estagiario estag;

	do {
		printf("\nInsira o c�digo do estagi�rio: ");
		scanf("%i", &codEstag);
		limparBuffer();
		estag = verEstagiarioEspecifico(codEstag);
		if (estag.tipo != 'P')
			printf("\nSomente estagi�rios plantonistas agendar reuni�es.\n");
	} while (estag.tipo != 'P');

	agenda.codEstagiario = codEstag;

	Disponibilidade disp = obterDisponibilidadeEspecifica(agenda.oab, diaSemana + 1);

	if (disp.oab == -1) {
		printf("\nAdvogado n�o possui disponibilidade para o dia seguinte.\n");
		system("pause");
		return;
	}

	gerarDataAtualMaisUm(agenda.dtAgendada, sizeof(agenda.dtAgendada));
	strcpy(agenda.hrAgendada, disp.horaInicio);

	gerarDataAtual(agenda.dtInscricao, sizeof(agenda.dtInscricao));
	gerarHoraAtual(agenda.hrInscricao, sizeof(agenda.hrInscricao));

	strcpy(agenda.areaDireito, adv.especialidade);

	printf("\nQual tipo de orienta��o deseja?\n");
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

	printf("\nObserva��es: ");
	fgets(agenda.observacoes, sizeof(agenda.observacoes), stdin);
	agenda.observacoes[strcspn(agenda.observacoes, "\n")] = '\0';

	printf("\nN�mero do processo: ");
	fgets(agenda.numProcesso, sizeof(agenda.numProcesso), stdin);
	agenda.numProcesso[strcspn(agenda.numProcesso, "\n")] = '\0';

	arquivoAgenda = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\AGENDA.DAT", "a+b");
	fwrite(&agenda, sizeof(Agenda), 1, arquivoAgenda);
	fclose(arquivoAgenda);

	printf("\nATENDIMENTO AGENDADO COM SUCESSO!\n");
	gerarRelatorioAgenda(&agenda);
}

void gerarRelatorioAgenda(Agenda* agenda) {
	printf("\nN�mero da OAB: %i", agenda->oab);
	printf("\nC�digo do estagi�rio: %i", agenda->codEstagiario);
	printf("\nData de inscri��o: %s", agenda->dtInscricao);
	printf("\nHora de inscri��o: %s", agenda->hrInscricao);
	printf("\nData agendada: %s", agenda->dtAgendada);
	printf("\nHora agendada: %s", agenda->hrAgendada);
	printf("\n�rea do direito: %s", agenda->areaDireito);
	printf("\nTipo de orienta��o: %s", agenda->tipoOrientacao);
	printf("\nPrazo fatal: %s", agenda->prazoFatal ? "Sim" : "N�o");
	if (agenda->prazoFatal) printf("\nData do prazo fatal: %s", agenda->dtPrazoFatal);
	printf("\nObserva��es: %s", agenda->observacoes);
	printf("\nN�mero do processo: %s", agenda->numProcesso);
	printf("\n--------------------------------------------------------\n");
}