#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

//Bibliotecas
#include <stdio.h> 
#include <stdbool.h> //Utilizado para verificações booleanas
#include <string.h>

//Módulos
#include "triagem.h"
#include "global.h"
#include "estagiario.h"

//Variáveis globais
double salMinimo = 1412.36;
FILE* arquivoCasos;
triagem atendimento;
Estagiario estag;



void realizarTriagem() {

	printf("\n----------- TRIAGEM DE CASO -------------\n");

	int codAtend = gerarCodAtendimento();


	if (arquivoCasos == NULL)
	{
		printf("Erro ao abrir CLIENTES.DAT\n");
		system("pause");
		exit(0);
	};

	atendimento.codAtendimento = codAtend;
	gerarDataAtual(atendimento.data, sizeof(atendimento.data));
	gerarHoraAtual(atendimento.horaAtendimento, sizeof(atendimento.horaAtendimento));

	int codEstag;
	char tipoPessoa;

	do
	{
		printf("Digite o código do estagiário: ");
		scanf("%d", &codEstag);
		limparBuffer();
		estag = verEstagiarioEspecifico(codEstag);

		if (estag.tipo != 'A') {
			printf("Somente estagiários atendentes podem realizar a triagem.\n\n");
		}

	} while (estag.tipo != 'A');

	atendimento.codEstagiario = codEstag;


	printf("\nHorário que o atendido chegou (hh:mm): ");
	fgets(atendimento.horaChegada, sizeof(atendimento.horaChegada), stdin);
	atendimento.horaChegada[strcspn(atendimento.horaChegada, "\n")] = '\0';

	printf("\nFonte de informacão do servico: ");
	fgets(atendimento.fonteInformacaoServico, sizeof(atendimento.fonteInformacaoServico), stdin);
	atendimento.fonteInformacaoServico[strcspn(atendimento.fonteInformacaoServico, "\n")] = '\0';

	do {
		printf("\nTipo de pessoa (F/J): ");
		tipoPessoa = getchar();
		limparBuffer();

		if (tipoPessoa != 'F' && tipoPessoa != 'J') printf("Tipo de pessoa inválido. Digite F para pessoa física ou J para pessoa jurídica.\n");

	} while (tipoPessoa != 'F' && tipoPessoa != 'J');

	atendimento.tipoPessoa = tipoPessoa;

	printf("\nNome do atendido: ");
	fgets(atendimento.nome, sizeof(atendimento.nome), stdin);
	atendimento.nome[strcspn(atendimento.nome, "\n")] = '\0';

	printf("\nGênero: ");
	fgets(atendimento.genero, sizeof(atendimento.genero), stdin);
	atendimento.genero[strcspn(atendimento.genero, "\n")] = '\0';

	printf("\nPertence a comunidade LGBTQIA+? (S/N): ");
	if (getchar() == 'S') atendimento.comLgbt = true;
	else atendimento.comLgbt = false;
	limparBuffer();

	printf("\nCor/Raça: ");
	fgets(atendimento.corRaca, sizeof(atendimento.corRaca), stdin);
	atendimento.corRaca[strcspn(atendimento.corRaca, "\n")] = '\0';

	printf("\nData de nascimento: ");
	fgets(atendimento.dataNascimento, sizeof(atendimento.dataNascimento), stdin);
	atendimento.dataNascimento[strcspn(atendimento.dataNascimento, "\n")] = '\0';

	printf("\nNacionalidade: ");
	fgets(atendimento.nacionalidade, sizeof(atendimento.nacionalidade), stdin);
	atendimento.nacionalidade[strcspn(atendimento.nacionalidade, "\n")] = '\0';

	printf("\nNaturalidade: ");
	fgets(atendimento.naturalidade, sizeof(atendimento.naturalidade), stdin);
	atendimento.naturalidade[strcspn(atendimento.naturalidade, "\n")] = '\0';

	printf("\nCPF: ");
	fgets(atendimento.cpf, sizeof(atendimento.cpf), stdin);
	atendimento.cpf[strcspn(atendimento.cpf, "\n")] = '\0';

	printf("\nRG: ");
	fgets(atendimento.rg, sizeof(atendimento.rg), stdin);
	atendimento.rg[strcspn(atendimento.rg, "\n")] = '\0';

	printf("\nEndereço: ");
	fgets(atendimento.endereco, sizeof(atendimento.endereco), stdin);
	atendimento.endereco[strcspn(atendimento.endereco, "\n")] = '\0';

	printf("\nCelular: ");
	fgets(atendimento.celular, sizeof(atendimento.celular), stdin);
	atendimento.celular[strcspn(atendimento.celular, "\n")] = '\0';

	printf("\nPossui WhatsApp? (S/N): ");
	if (getchar() == 'S') atendimento.whatsapp = true;
	else atendimento.whatsapp = false;
	limparBuffer();

	printf("\nTelefone alternativo: ");
	fgets(atendimento.telAlternativo, sizeof(atendimento.telAlternativo), stdin);
	atendimento.telAlternativo[strcspn(atendimento.telAlternativo, "\n")] = '\0';

	printf("\nE-mail: ");
	fgets(atendimento.email, sizeof(atendimento.email), stdin);
	atendimento.email[strcspn(atendimento.email, "\n")] = '\0';

	printf("\nEscolaridade: ");
	fgets(atendimento.escolaridade, sizeof(atendimento.escolaridade), stdin);
	atendimento.escolaridade[strcspn(atendimento.escolaridade, "\n")] = '\0';

	printf("\nO atendido está desempregado? (S/N) ");
	char resposta = getchar();
	limparBuffer();

	if (resposta == 'S') {
		strcpy(atendimento.situacaoProfissional, "Desempregado");
		strcpy(atendimento.profissao, "Desempregado");
	}
	else
	{
		strcpy(atendimento.situacaoProfissional, "Empregado");
		printf("\nProfissão: ");
		fgets(atendimento.profissao, sizeof(atendimento.profissao), stdin);
		atendimento.profissao[strcspn(atendimento.profissao, "\n")] = '\0';
	}


	printf("\nEstado civil: ");
	fgets(atendimento.estadoCivil, sizeof(atendimento.estadoCivil), stdin);
	atendimento.estadoCivil[strcspn(atendimento.estadoCivil, "\n")] = '\0';

	printf("\nPossui filhos? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.temFilhos = true;
		printf("\nQuantos filhos moram com você? ");
		fflush(stdin); scanf("%1f", &atendimento.qtdFilhosMorando);
	}
	else
	{
		atendimento.temFilhos = false;
		atendimento.qtdFilhosMorando = 0;
	}
	limparBuffer();

	printf("\nTotal de membros da entidadade familiar: ");
	fflush(stdin); scanf("%1f", &atendimento.totalMembrosFamilia);

	printf("\nPossui algum membro da família com deficiência? (S/N): ");
	if (getchar() == 'S') atendimento.membroFamiliaDeficiencia = true;
	else atendimento.membroFamiliaDeficiencia = false;
	limparBuffer();

	printf("\nPossui algum membro da família com Transtorno Global do Desenvolvimento (TGD)? (S/N): ");
	if (getchar() == 'S') atendimento.membroFamiliarTGD = true;
	else atendimento.membroFamiliarTGD = false;
	limparBuffer();

	printf("\nPossui algum membro da família idoso? (S/N): ");
	if (getchar() == 'S') atendimento.membroFamiliarIdoso = true;
	else atendimento.membroFamiliarIdoso = false;
	limparBuffer();

	printf("\nMembro familiar egresso prisional de até 4 meses (S/N): ");
	if (getchar() == 'S') atendimento.membroFamiliarEgressoPrisional = true;
	else atendimento.membroFamiliarEgressoPrisional = false;
	limparBuffer();

	printf("\nRecebe algum benefício assistencial do governo? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.recebeBeneficio = true;
		printf("\nQual o valor do benefício? ");
		fflush(stdin); scanf("%1f", &atendimento.valorBeneficio);
	}
	else
	{
		atendimento.recebeBeneficio = false;
		atendimento.valorBeneficio = 0;
	}
	limparBuffer();

	printf("\nValor da renda mensal do assistido: ");
	fflush(stdin); scanf("%1f", &atendimento.valorRenda);


	do
	{
		printf("\nValor total da renda familiar: ");
		scanf("%1f", &atendimento.totalRendaFamiliar);
		limparBuffer();
		if (atendimento.totalRendaFamiliar < 0 || atendimento.totalRendaFamiliar > 1000000) printf("Valor inválido. Digite um valor entre 0 e 1.000.000\n");
	} while (atendimento.totalRendaFamiliar < 0 || atendimento.totalRendaFamiliar > 1000000);


	printf("\nPossui gastos médicos? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.temGastosMedicos = true;
		printf("\nQual o valor dos gastos médicos? ");
		fflush(stdin); scanf("%1f", &atendimento.valorGastosMedicos);
	}
	else
	{
		atendimento.temGastosMedicos = false;
		atendimento.valorGastosMedicos = 0;
	}
	limparBuffer();

	printf("\nPossui investimentos? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.possuiInvestimento = true;
		printf("\nQual o valor dos investimentos? ");
		fflush(stdin); scanf("%1f", &atendimento.valorInvestimento);
	}
	else
	{
		atendimento.possuiInvestimento = false;
		atendimento.valorInvestimento = 0;
	}
	limparBuffer();

	printf("\nPossui casa própria? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.possuiCasaPropria = true;
		printf("\nQual o valor da casa própria? ");
		fflush(stdin); scanf("%1f", &atendimento.valorCasaPropria);
	}
	else
	{
		atendimento.possuiCasaPropria = false;
		atendimento.valorCasaPropria = 0;
	}
	limparBuffer();

	printf("\nPossui apartamento? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.possuiApartamento = true;
		printf("\nQual o valor do apartamento? ");
		fflush(stdin); scanf("%1f", &atendimento.valorApartamento);
	}
	else
	{
		atendimento.possuiApartamento = false;
		atendimento.valorApartamento = 0;
	}
	limparBuffer();

	printf("\nPossui terreno? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.possuiTerreno = true;
		printf("\nQual o valor do terreno? ");
		fflush(stdin); scanf("%1f", &atendimento.valorTerreno);
	}
	else
	{
		atendimento.possuiTerreno = false;
		atendimento.valorTerreno = 0;
	}
	limparBuffer();

	printf("\nPossui imóvel comercial? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.possuiImovelComercial = true;
		printf("\nQual o valor do imóvel comercial? ");
		fflush(stdin); scanf("%1f", &atendimento.valorImovelComercial);
	}
	else
	{
		atendimento.possuiImovelComercial = false;
		atendimento.valorImovelComercial = 0;
	}
	limparBuffer();

	printf("\nPossui veículo? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.possuiVeiculo = true;
		printf("\nQual o valor do veículo? ");
		fflush(stdin); scanf("%1f", &atendimento.valorVeiculo);
	}
	else
	{
		atendimento.possuiVeiculo = false;
		atendimento.valorVeiculo = 0;
	}
	limparBuffer();

	printf("\nA demanda envolve violência doméstica? (S/N): ");
	if (getchar() == 'S') atendimento.demandaViolenciaDomestica = true;
	else atendimento.demandaViolenciaDomestica = false;
	limparBuffer();

	printf("\nResumo do caso: ");
	fgets(atendimento.resumoCaso, sizeof(atendimento.resumoCaso), stdin);
	atendimento.resumoCaso[strcspn(atendimento.resumoCaso, "\n")] = '\0';

	printf("\nRamo do direito: ");
	fgets(atendimento.ramoDireito, sizeof(atendimento.ramoDireito), stdin);
	atendimento.ramoDireito[strcspn(atendimento.ramoDireito, "\n")] = '\0';
	verificarPerfilEnquadrado(&atendimento);

	arquivoCasos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jurídico\\data\\CLIENTES.DAT", "a+b");

	fwrite(&atendimento, sizeof(atendimento), 1, arquivoCasos);

	fclose(arquivoCasos);

	printf("\nCASO REGISTRADO NO SISTEMA COM SUCESSO!\n");
	gerarRelatorio(&atendimento);

	printf("\n------------------------------------------------------\n");

}

void verificarCasosEmAndamento()
{
	int count = 0;
	arquivoCasos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jurídico\\data\\CLIENTES.DAT", "r+b");

	if (arquivoCasos == NULL)
	{
		printf("Erro ao abrir CLIENTES.DAT\n");
		system("pause");
		exit(0);
	};

	printf("\n----------- LISTA DE CASOS NO SISTEMA -------------\n");

	while (!feof(arquivoCasos))
	{
		fread(&atendimento, sizeof(atendimento), 1, arquivoCasos);
		if (!feof(arquivoCasos))
		{
			count++;
			gerarRelatorio(&atendimento);
		}
		if (count == 0) printf("\nNenhum caso em andamento\n");


	}
	count = 0;

	fclose(arquivoCasos);

	printf("\n-------------------------------------------------------\n");


	system("pause");

}

triagem verificarCasoEspecifico(int codAtendimento)
{
	bool encontrado = false;
	arquivoCasos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jurídico\\data\\CLIENTES.DAT", "r+b");

	if (arquivoCasos == NULL)
	{
		printf("Erro ao abrir CLIENTES.DAT\n");
		exit(0);
	};

	while (!feof(arquivoCasos))

	{
		fread(&atendimento, sizeof(atendimento), 1, arquivoCasos);
		if (!feof(arquivoCasos))
		{
			if (atendimento.codAtendimento == codAtendimento)
			{
				encontrado = true;
				break;
			}
		}
	}

	if (!encontrado) {
		printf("Nenhum caso encontrado com o código de atendimento %d\n\n", codAtendimento);
		system("pause");
		exit(0);
	}

	fclose(arquivoCasos);

	return atendimento;
}


int gerarCodAtendimento()
{
	triagem ultimoAtendimento;

	arquivoCasos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jurídico\\data\\CLIENTES.DAT", "r+b");

	if (arquivoCasos == NULL)
	{
		printf("Erro ao abrir CLIENTES.DAT\n");
		system("pause");
		exit(0);
	};

	//Acessa a última linha do aquivo
	fseek(arquivoCasos, -1 * sizeof(triagem), SEEK_END);

	fread(&ultimoAtendimento, sizeof(triagem), 1, arquivoCasos);
	if (feof(arquivoCasos)) ultimoAtendimento.codAtendimento = 0;

	fclose(arquivoCasos);

	return ultimoAtendimento.codAtendimento + 1;
};



void gerarRelatorio(triagem* atendimento)
{
	printf("\nCod. Atendimento         : %d\n", atendimento->codAtendimento);
	printf("Cod. Estagiário Atendente  : %d\n", atendimento->codEstagiario);
	printf("Data                       : %s\n", atendimento->data);
	printf("Hora de Atendimento        : %s\n", atendimento->horaAtendimento);
	printf("Hora de Chegada            : %s\n", atendimento->horaChegada);
	printf("Fonte de Informação        : %s\n", atendimento->fonteInformacaoServico);
	printf("Pessoa Fisica/Juridica     : %c\n", atendimento->tipoPessoa);
	printf("Nome do(a) Atendido        : %s\n", atendimento->nome);
	printf("Gênero                     : %s\n", atendimento->genero);
	printf("Comunidade LGBTQIA+        : %s\n", atendimento->comLgbt ? "Sim" : "Não");
	printf("Cor/Raça                   : %s\n", atendimento->corRaca);
	printf("Data de Nascimento         : %s\n", atendimento->dataNascimento);
	printf("Nacionalidade              : %s\n", atendimento->nacionalidade);
	printf("Naturalidade               : %s\n", atendimento->naturalidade);
	printf("CPF                        : %s\n", atendimento->cpf);
	printf("RG                         : %s\n", atendimento->rg);
	printf("Endereço                   : %s\n", atendimento->endereco);
	printf("Celular                    : %s\n", atendimento->celular);
	printf("WhatsApp                   : %s\n", atendimento->whatsapp ? "Sim" : "Não");
	printf("Tel. Alternativo           : %s\n", atendimento->telAlternativo);
	printf("E-mail                     : %s\n", atendimento->email);
	printf("Escolaridade               : %s\n", atendimento->escolaridade);
	printf("Profissão                  : %s\n", atendimento->profissao);
	printf("Situação Profissional      : %s\n", atendimento->situacaoProfissional);
	printf("Estado Civil               : %s\n", atendimento->estadoCivil);
	printf("Possui Filhos              : %s\n", atendimento->temFilhos ? "Sim" : "Não");
	printf("Qtd. Filhos Morando        : %d\n", atendimento->qtdFilhosMorando);
	printf("Total Membros Família      : %d\n", atendimento->totalMembrosFamilia);
	printf("Membro com Deficiência     : %s\n", atendimento->membroFamiliaDeficiencia ? "Sim" : "Não");
	printf("Membro com TGD             : %s\n", atendimento->membroFamiliarTGD ? "Sim" : "Não");
	printf("Membro Idoso               : %s\n", atendimento->membroFamiliarIdoso ? "Sim" : "Não");
	printf("Membro Egresso Prisional   : %s\n", atendimento->membroFamiliarEgressoPrisional ? "Sim" : "Não");
	printf("Recebe Benefício           : %s\n", atendimento->recebeBeneficio ? "Sim" : "Não");
	if (atendimento->recebeBeneficio) printf("Valor do Benefício         : %.2f\n", atendimento->valorBeneficio);
	printf("Valor da Renda             : %.2f\n", atendimento->valorRenda);
	printf("Total Renda Familiar       : %.2f\n", atendimento->totalRendaFamiliar);
	printf("Possui Gastos Médicos      : %s\n", atendimento->temGastosMedicos ? "Sim" : "Não");
	if (atendimento->temGastosMedicos) printf("Valor Gastos Médicos       : %.2f\n", atendimento->valorGastosMedicos);
	printf("Possui Investimento        : %s\n", atendimento->possuiInvestimento ? "Sim" : "Não");
	if (atendimento->possuiInvestimento) printf("Valor Investimento         : %.2f\n", atendimento->valorInvestimento);
	printf("Possui Casa Própria        : %s\n", atendimento->possuiCasaPropria ? "Sim" : "Não");
	if (atendimento->possuiCasaPropria) printf("Valor Casa Própria         : %.2f\n", atendimento->valorCasaPropria);
	printf("Possui Apartamento         : %s\n", atendimento->possuiApartamento ? "Sim" : "Não");
	if (atendimento->possuiApartamento) 	printf("Valor Apartamento          : %.2f\n", atendimento->valorApartamento);
	printf("Possui Terreno             : %s\n", atendimento->possuiTerreno ? "Sim" : "Não");
	if (atendimento->possuiTerreno) 	printf("Valor Terreno              : %.2f\n", atendimento->valorTerreno);
	printf("Possui Imóvel Comercial    : %s\n", atendimento->possuiImovelComercial ? "Sim" : "Não");
	if (atendimento->possuiImovelComercial) 	printf("Valor Imóvel Comercial     : %.2f\n", atendimento->valorImovelComercial);
	printf("Possui Veículo             : %s\n", atendimento->possuiVeiculo ? "Sim" : "Não");
	if (atendimento->possuiVeiculo) 	printf("Valor Veículo              : %.2f\n", atendimento->valorVeiculo);
	printf("Demanda Violência Doméstica: %s\n", atendimento->demandaViolenciaDomestica ? "Sim" : "Não");
	printf("Resumo do Caso             : %s\n", atendimento->resumoCaso);
	printf("Ramo do Direito            : %s\n", atendimento->ramoDireito);
	printf("Perfil Enquadrado          : %s\n", atendimento->perfilEnquadrado ? "Sim" : "Não");
}

void verificarPerfilEnquadrado(triagem* atendimento)
{
	if (atendimento->totalRendaFamiliar <= 3 * salMinimo) {
		printf("Perfil enquadrado por ter renda familiar menor ou igual que tres salarios minimos\n");
		atendimento->perfilEnquadrado = true;
	}
	else if (atendimento->totalRendaFamiliar <= 4 * salMinimo) {
		printf("Renda familiar menor ou igual que 4 salarios minimos. Verificando outras condições\n");
		if (atendimento->totalMembrosFamilia > 5)
		{
			printf("Número de membros da familia maior que 5. Perfil enquadarado\n");
			atendimento->perfilEnquadrado = true;
		}
		else if (atendimento->temGastosMedicos)
		{
			printf("Tem gastos medicos. Perfil enquadarado\n");
			atendimento->perfilEnquadrado = true;
		}
		else if (atendimento->membroFamiliaDeficiencia || atendimento->membroFamiliarTGD)
		{
			printf("Membro da familia com deficiencia ou TGD. Perfil enquadarado\n");
			atendimento->perfilEnquadrado = true;
		}
		else if ((atendimento->membroFamiliarIdoso || atendimento->membroFamiliarEgressoPrisional) && atendimento->totalMembrosFamilia >= 4)
		{
			printf("Membro da familia idoso ou egresso prisional com mais de 4 membros. Perfil enquadarado\n");
			atendimento->perfilEnquadrado = true;
		}
		else {
			printf("Perfil NÃO enquadrado.\n");
			atendimento->perfilEnquadrado = false;
		}
	}

}