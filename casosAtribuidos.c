#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe


// Bibliotecas
#include <stdio.h>
#include <string.h>

// Arquivos
#include "casosAtribuidos.h"
#include "triagem.h"
#include "estagiario.h"
#include "global.h"


//Vari�veis Globais
FILE* arquivoCasosAtribuidos;
CasosAtribuidos atribuicaoCaso;

//Fun��es
void atribuirEstagiario() {
	printf("\n-----------ATRIBUI��O DE CASO AO ESTAGI�RIO-------------\n");

	printf("Digite o c�digo de atendimento: ");
	fflush(stdin); scanf("%d", &atribuicaoCaso.codAtendimento);

	triagem caso = verificarCasoEspecifico(atribuicaoCaso.codAtendimento);

	if (caso.codAtendimento != 0) {
		if (!caso.perfilEnquadrado) {
			printf("Perfil de cliente n�o est� enquadrado como assistido.\n");
			system("pause");
			return;
		}
	}

	printf("\nDigite o c�digo do estagi�rio: ");
	scanf("%d", &atribuicaoCaso.codEstagiario);
	limparBuffer();

	Estagiario estag = verEstagiarioEspecifico(atribuicaoCaso.codEstagiario);

	if (estag.codeEstag != 0) {
		if (estag.tipo != 'P') {
			printf("Somente estagi�rios plantonistas podem ser atribu�dos aos casos.\n");
			system("pause");
			return;
		}
	}

	printf("\nDigite a data da atribui��o: ");
	fgets(atribuicaoCaso.dataAtribuicao, sizeof(atribuicaoCaso.dataAtribuicao), stdin);
	atribuicaoCaso.dataAtribuicao[strcspn(atribuicaoCaso.dataAtribuicao, "\n")] = '\0';

	printf("\nDigite a hora da atribui��o: ");
	fgets(atribuicaoCaso.horaAtribuicao, sizeof(atribuicaoCaso.horaAtribuicao), stdin);
	atribuicaoCaso.horaAtribuicao[strcspn(atribuicaoCaso.horaAtribuicao, "\n")] = '\0';

	strcpy(atribuicaoCaso.cpf, caso.cpf);
	atribuicaoCaso.codAtendimento = caso.codAtendimento;


	arquivoCasosAtribuidos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\ATRIBUICAO.DAT", "a+b");

	if (arquivoCasosAtribuidos == NULL)
	{
		printf("Erro ao abrir ATRIBUICAO.DAT\n");
		system("pause");
		exit(0);
	};
	
	fwrite(&atribuicaoCaso, sizeof(CasosAtribuidos), 1, arquivoCasosAtribuidos);

	fclose(arquivoCasosAtribuidos);

	printf("\nCASO ATRIBU�DO AO ESTAGI�RIO COM SUCESSO!\n");

	gerarRelatorioCasosAtribuidos(&atribuicaoCaso);

	printf("\n--------------------------------------------------------\n");
}

void gerarRelatorioCasosAtribuidos(CasosAtribuidos *atribuicaoCaso) {
	printf("\nC�digo de atendimento:  %d\n", atribuicaoCaso->codAtendimento);
	printf("C�digo do estagi�rio:    %d\n", atribuicaoCaso->codEstagiario);
	printf("Data da atribui��o:      %s\n", atribuicaoCaso->dataAtribuicao);
	printf("Hora da atribui��o:      %s\n", atribuicaoCaso->horaAtribuicao);
}