#ifndef ADVOGADO_H
#define ADVOGADO_H

//struct
typedef struct {
	int oab;
	char nome[40];
	char especialidade[20];
	char cpf[13];
	char email[30];
	char numeroTelefone[15];
	int anoIngresso;

} Advogado;

void adicionarAdvogado();
void verTodosAdvogados();
int obterTodosAdvogados();
void gerarRelatorioAdv(Advogado *advogado);
Advogado verAdvogadoEspecifico(int oab);
void ordenaAdvOab(Advogado* advogados, int tamanho_vetor);

#endif