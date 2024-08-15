#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

// Bibliotecas
#include <stdio.h> //biblioteca padrão de entrada e saída
#include <string.h> //biblioteca para manipulação de strings

// Módulos
#include "casosAtribuidos.h"
#include "triagem.h"
#include "estagiario.h"
#include "global.h"

//Variáveis Globais
FILE* arquivoCasosAtribuidos;
CasosAtribuidos atribuicaoCaso;

void atribuirEstagiario() {
	printf("\n-----------ATRIBUIÇÃO DE CASO AO ESTAGIÁRIO-------------\n");

	//TODO: Realizar verificação para inserção de códigos de atendimento válidos
	printf("Digite o código de atendimento: ");
	fflush(stdin); scanf("%d", &atribuicaoCaso.codAtendimento);

	triagem caso = retornarCasoEspecifico(atribuicaoCaso.codAtendimento);

	if (caso.codAtendimento != 0) {
		if (!caso.perfilEnquadrado) {
			printf("Perfil de cliente não está enquadrado como assistido.\n");
			system("pause");
			return;
		}
	}
	///////////////////////////////////////////////////////////////////

	//TODO: Realizar verificação para inserção de códigos de estagiários válidos
	printf("\nDigite o código do estagiário: ");
	scanf("%d", &atribuicaoCaso.codEstagiario);
	limparBuffer();

	Estagiario estag = retornarEstagiarioEspecifico(atribuicaoCaso.codEstagiario);

	if (estag.codeEstag != 0) {
		if (estag.tipo != 'P') {
			printf("Somente estagiários plantonistas podem ser atribuídos aos casos.\n");
			system("pause");
			return;
		}
	}
	////////////////////////////////////////////////////////////////////

	printf("\nDigite a data da atribuição: ");
	fgets(atribuicaoCaso.dataAtribuicao, sizeof(atribuicaoCaso.dataAtribuicao), stdin);
	atribuicaoCaso.dataAtribuicao[strcspn(atribuicaoCaso.dataAtribuicao, "\n")] = '\0';
	printf("\nDigite a hora da atribuição: ");
	fgets(atribuicaoCaso.horaAtribuicao, sizeof(atribuicaoCaso.horaAtribuicao), stdin);
	atribuicaoCaso.horaAtribuicao[strcspn(atribuicaoCaso.horaAtribuicao, "\n")] = '\0';
	strcpy(atribuicaoCaso.cpf, caso.cpf);
	atribuicaoCaso.codAtendimento = caso.codAtendimento;

	// Abre o arquivo para escrita, verifica se foi aberto corretamente, escreve no arquivo e fecha
	arquivoCasosAtribuidos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jurídico\\data\\ATRIBUICAO.DAT", "a+b");
	if (arquivoCasosAtribuidos == NULL)
	{
		printf("Erro ao abrir ATRIBUICAO.DAT\n");
		system("pause");
		exit(0);
	};
	fwrite(&atribuicaoCaso, sizeof(CasosAtribuidos), 1, arquivoCasosAtribuidos);
	fclose(arquivoCasosAtribuidos);

	printf("\nCASO ATRIBUÍDO AO ESTAGIÁRIO COM SUCESSO!\n");

	//Imprime o relatório do caso atribuído
	gerarRelatorioCasosAtribuidos(&atribuicaoCaso);

	printf("\n--------------------------------------------------------\n");
}

// Relatório de casos atribuídos
void gerarRelatorioCasosAtribuidos(CasosAtribuidos* atribuicaoCaso) {
	printf("\nCódigo de atendimento:  %d\n", atribuicaoCaso->codAtendimento);
	printf("Código do estagiário:    %d\n", atribuicaoCaso->codEstagiario);
	printf("Data da atribuição:      %s\n", atribuicaoCaso->dataAtribuicao);
	printf("Hora da atribuição:      %s\n", atribuicaoCaso->horaAtribuicao);
}