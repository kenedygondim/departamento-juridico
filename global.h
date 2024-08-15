#ifndef GLOBAL_H
#define GLOBAL_H

void limparBuffer(void);
void gerarData(char* buffer, size_t size, int acresDias);
void gerarHoraAtual(char* buffer, size_t size);
int retornarDiaSemana();

#endif