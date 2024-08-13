#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

#include "global.h"
#include <stdio.h>
#include <time.h> // Utilizado para gerar data e hora atuais no programa



void limparBuffer(void) {
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

//https://www.youtube.com/watch?v=W-X2_v4Oyx8

void gerarDataAtual(char* buffer, size_t size) {

	time_t t;
	struct tm* tm_info;
	time(&t);
	tm_info = localtime(&t);
	mktime(tm_info);
	strftime(buffer, size, "%d/%m/%Y", tm_info);
}

void gerarHoraAtual(char* buffer, size_t size) {

	time_t t;
	struct tm* tm_info;
	time(&t);
	tm_info = localtime(&t);
	strftime(buffer, size, "%H:%M", tm_info);
}

int retornarDiaSemana() {
	time_t t;
	struct tm* tm_info;
	time(&t);
	tm_info = localtime(&t);

	return tm_info->tm_wday;
}

void gerarDataAtualMaisUm(char* buffer, size_t size) {

	time_t t;
	struct tm* tm_info;
	time(&t);
	tm_info = localtime(&t);
	tm_info->tm_mday += 1;
	mktime(tm_info);
	strftime(buffer, size, "%d/%m/%Y", tm_info);
}


