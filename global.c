#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de fun��es consideradas inseguras pelo compilador

//Bibliotecas 
#include <stdio.h> //� usada para opera��es de entrada e sa�da em C, como leitura e escrita de dados
#include <time.h> //� usada para manipula��o de data e hora em C

//M�dulos
#include "global.h"

//Fun��o para limpar buffer do teclado
//Funcionamento b�sico:
/*"Enquanto o buffer possuir caracteres diferentes de \n (enter do teclado) e n�o chegar ao final do arquivo (EOF)
a vari�vel c vai consumir os caracteres do buffer por meio do getchar(), ent�o o buffer ser� limpo."*/
void limparBuffer(void) {
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

//Link do v�deo que explica a fun��o limparBuffer: https://www.youtube.com/watch?v=Jv8eK0b1FHQ


//Fun��o para gerar data atual, ou somar dias � data atual
//Par�metros da fun��o:
//buffer: propriedade que vai armazenar a data. Exemplo: agenda.dtInscricao
//size: tamanho do buffer (sizeof da propriedade) Exemplo: sizeof(agenda.dtInscricao)
//acresDias: quantidade de dias que deseja acrescentar na data atual. Exemplo: 1. Pode ser �til para gerar a data de amanh�.
//Em caso de gerar a data sem acrescentar dias, basta passar 0 como par�metro.
//Exemplo final: gerarData(agenda.dtInscricao, sizeof(agenda.dtInscricao), 1);
//A fun��o abaixo gera a data e armazena na propriedade desejada, sem necessidade de mais c�digo.
void gerarData(char* buffer, size_t size, int acresDias) {

	time_t t;
	struct tm* tm_info;
	time(&t);
	tm_info = localtime(&t);
	tm_info->tm_mday += acresDias;
	mktime(tm_info);
	strftime(buffer, size, "%d/%m/%Y", tm_info);
}

//Par�metros da fun��o:
//buffer: propriedade que vai armazenar a hora. Exemplo: agenda.dtInscricao
//size: tamanho do buffer (sizeof da propriedade) Exemplo: sizeof(agenda.dtInscricao)
//Exemplo final: gerarHoraAtual(agenda.horaInscricao, sizeof(agenda.horaInscricao));
//A fun��o abaixo gera a hora e armazena na propriedade desejada, sem necessidade de mais c�digo.
void gerarHoraAtual(char* buffer, size_t size) {

	time_t t;
	struct tm* tm_info;
	time(&t);
	tm_info = localtime(&t);
	strftime(buffer, size, "%H:%M", tm_info);
}

//Fun��o para retornar o dia da semana
//Retorna um inteiro que representa o dia da semana, sendo:
//0 - Domingo, 1 - Segunda-feira, 2 - Ter�a-feira, 3 - Quarta-feira, 4 - Quinta-feira, 5 - Sexta-feira, 6 - S�bado
int retornarDiaSemana() {
	time_t t;
	struct tm* tm_info;
	time(&t);
	tm_info = localtime(&t);
	return tm_info->tm_wday;
}