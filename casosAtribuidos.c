#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe


// Bibliotecas
#include <stdio.h>
#include <string.h>

// Arquivos
#include "casosAtribuidos.h"
#include "triagem.h"
#include "estagiario.h"
#include "global.h"


//Variáveis Globais
FILE* arquivoCasosAtribuidos;
CasosAtribuidos atribuicaoCaso;

//Funções
void atribuirEstagiario() {
	printf("\n-----------ATRIBUIÇÃO DE CASO AO ESTAGIÁRIO-------------\n");

	printf("Digite o código de atendimento: ");
	fflush(stdin); scanf("%d", &atribuicaoCaso.codAtendimento);

	triagem caso = verificarCasoEspecifico(atribuicaoCaso.codAtendimento);

	if (caso.codAtendimento != 0) {
		if (!caso.perfilEnquadrado) {
			printf("Perfil de cliente não está enquadrado como assistido.\n");
			system("pause");
			return;
		}
	}

	printf("\nDigite o código do estagiário: ");
	scanf("%d", &atribuicaoCaso.codEstagiario);
	limparBuffer();

	Estagiario estag = verEstagiarioEspecifico(atribuicaoCaso.codEstagiario);

	if (estag.codeEstag != 0) {
		if (estag.tipo != 'P') {
			printf("Somente estagiários plantonistas podem ser atribuídos aos casos.\n");
			system("pause");
			return;
		}
	}

	printf("\nDigite a data da atribuição: ");
	fgets(atribuicaoCaso.dataAtribuicao, sizeof(atribuicaoCaso.dataAtribuicao), stdin);
	atribuicaoCaso.dataAtribuicao[strcspn(atribuicaoCaso.dataAtribuicao, "\n")] = '\0';

	printf("\nDigite a hora da atribuição: ");
	fgets(atribuicaoCaso.horaAtribuicao, sizeof(atribuicaoCaso.horaAtribuicao), stdin);
	atribuicaoCaso.horaAtribuicao[strcspn(atribuicaoCaso.horaAtribuicao, "\n")] = '\0';

	strcpy(atribuicaoCaso.cpf, caso.cpf);
	atribuicaoCaso.codAtendimento = caso.codAtendimento;


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

	gerarRelatorioCasosAtribuidos(&atribuicaoCaso);

	printf("\n--------------------------------------------------------\n");
}

void gerarRelatorioCasosAtribuidos(CasosAtribuidos *atribuicaoCaso) {
	printf("\nCódigo de atendimento:  %d\n", atribuicaoCaso->codAtendimento);
	printf("Código do estagiário:    %d\n", atribuicaoCaso->codEstagiario);
	printf("Data da atribuição:      %s\n", atribuicaoCaso->dataAtribuicao);
	printf("Hora da atribuição:      %s\n", atribuicaoCaso->horaAtribuicao);
}