#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

//Bibliotecas
#include <stdio.h> 
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

//Arquivos
#include "advogado.h"
#include "agenda.h"
#include "casosAtribuidos.h"
#include "triagem.h"
#include "global.h"
#include "estagiario.h"
#include "disponibilidade.h"

void gerarMensagemBoasVindas();

int main()
{
	setlocale(LC_ALL, ""); //Seta a localização para a padrão do sistema	


	//Variáveis
	int opcao = 1;

	gerarMensagemBoasVindas();


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
	printf("15 - Sair\n");
	scanf("%i", &opcao);
	limparBuffer();

	do
	{
		switch (opcao) //cuidado com o case 10, pois a variavel opcao é char (1 caractere), logo vai cair na opção triagem
		{
		case 1:
			realizarTriagem();
			break;
		case 2:
			verificarCasosEmAndamento();
			break;
		case 3:
			atribuirEstagiario();
			break;
		case 4:
			adicionarEstagiario();
			break;
		case 5:
			verTodosEstagiarios();
			break;
		case 6:
			adicionarDisponibilidade();
			break;
		case 7:
			agendarAtendimento();
			break;
		case 8:
			verTodosAdvogados();
			break;
		case 9:
			adicionarAdvogado();
			break;
		case 15:
			printf("Até breve!\n");
			exit(0);
		default:
			break;
		}

		limparBuffer();

		printf("Qual ação deseja realizar?\n");
		printf("1 - Realizar triagem\n");
		printf("2 - Ver triagens realizadas\n");
		printf("3 - Atribuir estagiário\n");
		printf("4 - Adicionar estagiário no sistema\n");
		printf("5 - Ver todos os estagiários\n");
		printf("6 - Adicionar disponibilidade dos advogados\n");
		printf("7 - Agendar atendimento\n");
		printf("8 - Ver todos os advogados\n");
		printf("9 - Adicionar advogado no sistema\n");
		printf("15 - Sair\n");
		scanf("%i", &opcao);
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

