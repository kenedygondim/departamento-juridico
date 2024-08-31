#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

//Bibliotecas
#include <stdio.h> 
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

//Arquivos
#include "global.h"
#include "advogado.h"
#include "agenda.h"
#include "casosAtribuidos.h"
#include "triagem.h"
#include "estagiario.h"
#include "disponibilidade.h"
#include "controle.h"

void gerarMensagemBoasVindas();

int main()
{
	setlocale(LC_ALL, ""); //Seta a localização para a padrão do sistema	

	//Variáveis
	int opcao = 1;

	gerarMensagemBoasVindas();

	do
	{
		printf("\nQual ação deseja realizar?\n");
		printf("\n1 - Realizar triagem\n");
		printf("2 - Ver todas as triagens\n");
		printf("3 - Atribuir estagiário\n");
		printf("4 - Adicionar estagiário no sistema\n");
		printf("5 - Ver todos os estagiários\n");
		printf("6 - Adicionar disponibilidade dos advogados\n");
		printf("7 - Agendar atendimento\n");
		printf("8 - Ver todos os advogados\n");
		printf("9 - Adicionar advogado no sistema\n");
		printf("10 - Atualizar/Inserir Controle/Movimentação dos casos\n");
		printf("11 - Visualizar Controle/Movimentação dos casos\n");
		printf("12 - Listar todos os clientes\n");
		printf("13 - Visualizar fila\n");
		printf("14 - Processar fila\n");
		printf("15 - Sair\n");
		scanf("%i", &opcao);
		limparBuffer();

		switch (opcao)
		{
		case 1:
			realizarTriagem();
			break;
		case 2:
			mostrarCasosEmAndamento();
			break;
		case 3:
			atribuirEstagiario();
			break;
		case 4:
			adicionarEstagiario();
			break;
		case 5:
			mostrarTodosEstagiarios();
			break;
		case 6:
			adicionarDisponibilidade();
			break;
		case 7:
			agendarAtendimento();
			break;
		case 8:
			mostrarTodosAdvogados();
			break;
		case 9:
			adicionarAdvogado();
			break;
		case 10:
			atualizarOuInserirMovimentacao();
			break;
		case 11:
			verTodasMovimentacoes();
			break;
		case 12:
			mostrarCasosEmAndamento();
			break;
		case 13:
			visualizarTodasFilas();
			break;
		case 14:
			processarAtendimento();
			break;
		case 15:
			printf("Até breve!\n");
			exit(0);
		default:
			break;
		}

		limparBuffer();

	} while (opcao != 15);

	return 0;
}


//Funções auxiliares
void gerarMensagemBoasVindas() {
	printf("*********************************************\n");
	printf("*                                           *\n");
	printf("*      Bem-vindo ao Departamento Jurídico   *\n");
	printf("*               de São Paulo                *\n");
	printf("*                                           *\n");
	printf("*   Estamos aqui para ajudá-lo com suas     *\n");
	printf("*      questões legais e fornecer o         *\n");
	printf("*     melhor suporte jurídico possível.     *\n");
	printf("*                                           *\n");
	printf("*********************************************\n");
}