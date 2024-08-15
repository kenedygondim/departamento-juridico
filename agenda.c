#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

// Bilbiotecas
#include <stdio.h> //biblioteca padrão de entrada e saída
#include <string.h> //biblioteca para manipulação de strings
#include <stdbool.h> //biblioteca para usar tipo de dados booleano

// Módulos
#include "agenda.h"
#include "global.h"
#include "advogado.h"
#include "estagiario.h"
#include "disponibilidade.h"

//Variáveis globais
FILE* arquivoAgenda;
Agenda agenda;

void agendarAtendimento() {
	//Variáveis temporárias
	int tempOab;
	Advogado adv;
	int diaSemana = retornarDiaSemana();
	int codEstag;
	Estagiario estag;
	char tempPF;

	printf("\n----------- AGENDAMENTO DE ATENDIMENTO -------------\n");
	printf("\nATENÇÃO: Só é possível agendar atendimentos para o dia seguinte.\n");
	printf("Advogados disponíveis para amanhã: \n");

	//Mostra relatório de advogados disponíveis para o dia seguinte
	mostrarRelatorioAdvDis();

	// Enquanto não encontrar um advogado com a OAB informada, pede para inserir novamente
	do
	{
		printf("\nInsira o número da OAB do advogado que deseja atendimento: ");
		scanf("%i", &tempOab);
		limparBuffer();
		adv = retornarAdvogadoEspecifico(tempOab);
	} while (adv.oab == -1);
	// Atribui o número da OAB à agenda
	agenda.oab = tempOab;

	// Enquanto não encontrar um estagiário plantonista com o código informado, pede para inserir novamente
	do {
		printf("\nInsira o código do estagiário: ");
		scanf("%i", &codEstag);
		limparBuffer();
		estag = retornarEstagiarioEspecifico(codEstag);
		if (estag.tipo != 'P')
			printf("\nSomente estagiários plantonistas agendar reuniões.\n");
	} while (estag.tipo != 'P');
	// Atribui o código do estagiário à agenda
	agenda.codEstagiario = codEstag;

	// Verifica se realmente o advogado possui disponibilidade para o dia seguinte
	Disponibilidade disp = obterDisponibilidadeEspecifica(agenda.oab, diaSemana + 1);
	if (disp.oab == -1) {
		printf("\nAdvogado não possui disponibilidade para o dia seguinte.\n");
		system("pause");
		return;
	}

	// Atribui a data e hora agendada à agenda
	gerarData(agenda.dtAgendada, sizeof(agenda.dtAgendada), 1);
	strcpy(agenda.hrAgendada, disp.horaInicio);

	// Atribui a data e hora de inscrição à agenda
	gerarData(agenda.dtInscricao, sizeof(agenda.dtInscricao), 0);
	gerarHoraAtual(agenda.hrInscricao, sizeof(agenda.hrInscricao));

	// Atribui a área do direito à agenda, de acordo com a especialidade do advogado
	strcpy(agenda.areaDireito, adv.especialidade);

	printf("\nQual tipo de orientação deseja?\n");
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

	printf("\nObservações: ");
	fgets(agenda.observacoes, sizeof(agenda.observacoes), stdin);
	agenda.observacoes[strcspn(agenda.observacoes, "\n")] = '\0';
	printf("\nNúmero do processo: ");
	fgets(agenda.numProcesso, sizeof(agenda.numProcesso), stdin);
	agenda.numProcesso[strcspn(agenda.numProcesso, "\n")] = '\0';

	// Abre, verifica se o arquivo foi aberto, escreve e fecha o arquivo
	arquivoAgenda = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jurídico\\data\\AGENDA.DAT", "a+b");
	if (arquivoAgenda == NULL)
	{
		printf("Erro ao abrir AGENDA.DAT\n");
		system("pause");
		exit(0);
	}
	fwrite(&agenda, sizeof(Agenda), 1, arquivoAgenda);
	fclose(arquivoAgenda);

	printf("\nATENDIMENTO AGENDADO COM SUCESSO!\n");
	//Imprime o relatório do atendimento agendado
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