#ifndef AGENDA_H
#define AGENDA_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {
	int oab;
	int codEstagiario;
	char dtAgendada[11];
	char hrAgendada[6];
	char dtInscricao[11]; //automatico
	char hrInscricao[6]; //automatico
	char areaDireito[20];
	char tipoOrientacao[30];
	bool prazoFatal;
	char dtPrazoFatal[11];
	char observacoes[500];
	char numProcesso[100];
	char foiAtendido[20];
} Agenda;


void agendarAtendimento();
void verAgendamentos();
void gerarRelatorioAgenda(Agenda* agenda);

#endif 