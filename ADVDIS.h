#ifndef  ADVDIS_H
#define ADVDIS_H

typedef struct {
	int oab;
	char nome[40];
	char especialidade[20];
	char email[30];
	int diaSemana;
	char horaInicio[7];
	char horaFim[7];
	char formato;
} AdvDis;

void mostrarRelatorioAdvDis();

#endif 
