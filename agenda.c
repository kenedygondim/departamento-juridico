#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

// Bilbiotecas
#include <stdio.h> //biblioteca padr�o de entrada e sa�da
#include <string.h> //biblioteca para manipula��o de strings
#include <stdbool.h> //biblioteca para usar tipo de dados booleano

// M�dulos
#include "agenda.h"
#include "global.h"
#include "advogado.h"
#include "estagiario.h"
#include "disponibilidade.h"

//Vari�veis globais
FILE* arquivoAgenda;
Agenda agenda;

void agendarAtendimento() {
	//Vari�veis tempor�rias
	int tempOab;
	Advogado adv;
	int diaSemana = retornarDiaSemana();
	int codEstag;
	Estagiario estag;
	char tempPF;

	printf("\n----------- AGENDAMENTO DE ATENDIMENTO -------------\n");
	printf("\nATEN��O: S� � poss�vel agendar atendimentos para o dia seguinte.\n");
	printf("Advogados dispon�veis para amanh�: \n");

	//Mostra relat�rio de advogados dispon�veis para o dia seguinte
	mostrarRelatorioAdvDis();

	// Enquanto n�o encontrar um advogado com a OAB informada, pede para inserir novamente
	do
	{
		printf("\nInsira o n�mero da OAB do advogado que deseja atendimento: ");
		scanf("%i", &tempOab);
		limparBuffer();
		adv = retornarAdvogadoEspecifico(tempOab);
	} while (adv.oab == -1);
	// Atribui o n�mero da OAB � agenda
	agenda.oab = tempOab;

	// Enquanto n�o encontrar um estagi�rio plantonista com o c�digo informado, pede para inserir novamente
	do {
		printf("\nInsira o c�digo do estagi�rio: ");
		scanf("%i", &codEstag);
		limparBuffer();
		estag = retornarEstagiarioEspecifico(codEstag);
		if (estag.tipo != 'P')
			printf("\nSomente estagi�rios plantonistas agendar reuni�es.\n");
	} while (estag.tipo != 'P');
	// Atribui o c�digo do estagi�rio � agenda
	agenda.codEstagiario = codEstag;

	// Verifica se realmente o advogado possui disponibilidade para o dia seguinte
	Disponibilidade disp = obterDisponibilidadeEspecifica(agenda.oab, diaSemana + 1);
	if (disp.oab == -1) {
		printf("\nAdvogado n�o possui disponibilidade para o dia seguinte.\n");
		system("pause");
		return;
	}

	// Atribui a data e hora agendada � agenda
	gerarData(agenda.dtAgendada, sizeof(agenda.dtAgendada), 1);
	strcpy(agenda.hrAgendada, disp.horaInicio);

	// Atribui a data e hora de inscri��o � agenda
	gerarData(agenda.dtInscricao, sizeof(agenda.dtInscricao), 0);
	gerarHoraAtual(agenda.hrInscricao, sizeof(agenda.hrInscricao));

	// Atribui a �rea do direito � agenda, de acordo com a especialidade do advogado
	strcpy(agenda.areaDireito, adv.especialidade);

	printf("\nQual tipo de orienta��o deseja?\n");
	fgets(agenda.tipoOrientacao, sizeof(agenda.tipoOrientacao), stdin);
	agenda.tipoOrientacao[strcspn(agenda.tipoOrientacao, "\n")] = '\0';

	// Se o prazo for fatal, pede para inserir a data do prazo fatal
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

	// Abre, verifica se o arquivo foi aberto, escreve e fecha o arquivo
	arquivoAgenda = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\AGENDA.DAT", "a+b");
	if (arquivoAgenda == NULL)
	{
		printf("Erro ao abrir AGENDA.DAT\n");
		system("pause");
		exit(0);
	}
	fwrite(&agenda, sizeof(Agenda), 1, arquivoAgenda);
	fclose(arquivoAgenda);

	printf("\nATENDIMENTO AGENDADO COM SUCESSO!\n");
	//Imprime o relat�rio do atendimento agendado
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