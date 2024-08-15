#define _CRT_SECURE_NO_WARNINGS //desabilita alertas de unsafe

//Bibliotecas
#include <stdio.h> // Biblioteca padr�o de entrada e sa�da
#include <stdbool.h> //Utilizado para verifica��es booleanas
#include <string.h>  //inclui fun��es para copiar (strcpy), concatenar (strcat), comparar (strcmp)

//M�dulos
#include "triagem.h" 
#include "global.h" 
#include "estagiario.h"

//Vari�veis globais
double salMinimo = 1412.36; // Vari�vel que ser� utilizada no c�lculo da renda familiar
FILE* arquivoCasos; // Ponteiro para o arquivo CLIENTES.DAT, ser� utilizado para resgatar, gravar e atualizar os dados dos atendimentos
triagem atendimento; // Vari�vel que armazenar� os dados do atendimento
Estagiario estag; // Servir� para verificar se o estagi�rio � valido e se � atendente ou n�o.


void realizarTriagem() {
	//Vari�veis tempor�rias (Usadas para verifica��es de entrada do usu�rio)
	int tempCodEstag;
	char tempTipoPessoa;

	
	printf("\n----------- TRIAGEM DE CASO -------------\n");
	
	//Atribui um c�digo do atendimento v�lido
	atendimento.codAtendimento = retornarCodAtendimento();

	//Gera a data e hora do atendimento 
	gerarData(atendimento.data, sizeof(atendimento.data), 0);
	gerarHoraAtual(atendimento.horaAtendimento, sizeof(atendimento.horaAtendimento));

	//Enquanto o estagi�rio n�o for um atendente, o c�digo do estagi�rio � solicitado novamente
	do
	{
		printf("Digite o c�digo do estagi�rio: ");
		scanf("%d", &tempCodEstag);
		limparBuffer();
		estag = retornarEstagiarioEspecifico(tempCodEstag);
		if (estag.tipo != 'A')
			printf("Somente estagi�rios atendentes podem realizar a triagem.\n\n");
	} while (estag.tipo != 'A');
	//Atribui o c�digo do estagi�rio ao atendimento
	atendimento.codEstagiario = tempCodEstag;

	printf("\nHor�rio que o atendido chegou (hh:mm): ");
	fgets(atendimento.horaChegada, sizeof(atendimento.horaChegada), stdin);
	atendimento.horaChegada[strcspn(atendimento.horaChegada, "\n")] = '\0';
	printf("\nFonte de informac�o do servico: ");
	fgets(atendimento.fonteInformacaoServico, sizeof(atendimento.fonteInformacaoServico), stdin);
	atendimento.fonteInformacaoServico[strcspn(atendimento.fonteInformacaoServico, "\n")] = '\0';

	//Verifica se o tipo de pessoa � v�lido (F�sica ou Jur�dica)
	//Adicionar campo de CNPJ caso seja pessoa jur�dica posteriormente
	do {
		printf("\nTipo de pessoa (F/J): ");
		tempTipoPessoa = getchar(); // O comportamento do getchar � de consumir o caracterer. Se n�o for capturado por uma vari�vel, o valor ser� perdido.
		limparBuffer();
		if (tempTipoPessoa != 'F' && tempTipoPessoa != 'J') printf("Tipo de pessoa inv�lido. Digite F para pessoa f�sica ou J para pessoa jur�dica.\n");
	} while (tempTipoPessoa != 'F' && tempTipoPessoa != 'J');
	//Atribui o tipo de pessoa ao atendimento
	atendimento.tipoPessoa = tempTipoPessoa;

	printf("\nNome do atendido: ");
	fgets(atendimento.nome, sizeof(atendimento.nome), stdin);
	atendimento.nome[strcspn(atendimento.nome, "\n")] = '\0';
	printf("\nG�nero: ");
	fgets(atendimento.genero, sizeof(atendimento.genero), stdin);
	atendimento.genero[strcspn(atendimento.genero, "\n")] = '\0';

	//Adicionar verifica��o (S� se quiser) qualquer coisa diferente de 'S' vai ser setado com false:
	//Se adicionar verifica��o, criar variavel temporaria para consumir o getchar
	printf("\nPertence a comunidade LGBTQIA+? (S/N): ");
	if (getchar() == 'S') atendimento.comLgbt = true;
	else atendimento.comLgbt = false;
	limparBuffer();

	printf("\nCor/Ra�a: ");
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


	do {
		printf("\nCPF: ");
		fgets(atendimento.cpf, sizeof(atendimento.cpf), stdin);
		atendimento.cpf[strcspn(atendimento.cpf, "\n")] = '\0';

		if (strlen(atendimento.cpf) != 11) printf("\nO CPF deve ter 11 d�gitos.");

	} while (strlen(atendimento.cpf) != 11);

	do {
		printf("\nRG: ");
		fgets(atendimento.rg, sizeof(atendimento.rg), stdin);
		atendimento.rg[strcspn(atendimento.rg, "\n")] = '\0';

		if (strlen(atendimento.rg) != 9) printf("\nO RG deve ter 8 d�gitos.");

	} while (strlen(atendimento.rg) != 9);

	printf("\nEndere�o: ");
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

	//Se o atendido for desempregado, a profiss�o � setada como desempregado
	//Alterar se achar conveniente
	printf("\nO atendido est� desempregado? (S/N) ");
	if (getchar() == 'S') {
		strcpy(atendimento.situacaoProfissional, "Desempregado");
		strcpy(atendimento.profissao, "Desempregado");
	}
	else
	{
		strcpy(atendimento.situacaoProfissional, "Empregado");
		printf("\nProfiss�o: ");
		fgets(atendimento.profissao, sizeof(atendimento.profissao), stdin);
		atendimento.profissao[strcspn(atendimento.profissao, "\n")] = '\0';
	}
	limparBuffer();

	printf("\nEstado civil: ");
	fgets(atendimento.estadoCivil, sizeof(atendimento.estadoCivil), stdin);
	atendimento.estadoCivil[strcspn(atendimento.estadoCivil, "\n")] = '\0';

	//Se o atendido possuir filhos, a quantidade de filhos morando com ele � solicitada.
	printf("\nPossui filhos? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.temFilhos = true;
		do {
			printf("\nQuantos filhos moram com voc�? ");
			scanf("%i", &atendimento.qtdFilhosMorando);
			limparBuffer();
		} while (atendimento.qtdFilhosMorando < 0 || atendimento.qtdFilhosMorando > 30);
	}
	else
	{
		atendimento.temFilhos = false;
		atendimento.qtdFilhosMorando = 0;
	}



	

	do {
		printf("\nTotal de membros da entidadade familiar: ");
		scanf("%i", &atendimento.totalMembrosFamilia);

		printf("\n\n %i \n\n", atendimento.totalMembrosFamilia);

		limparBuffer();
	} while (atendimento.totalMembrosFamilia < 1 || atendimento.totalMembrosFamilia > 30);


	////Adicionar verifica��o (S� se quiser) qualquer coisa diferente de 'S' vai ser setado com false:
	//Se adicionar verifica��o, criar variavel temporaria para consumir o getchar
	printf("\nPossui algum membro da fam�lia com defici�ncia? (S/N): ");
	if (getchar() == 'S') atendimento.membroFamiliaDeficiencia = true;
	else atendimento.membroFamiliaDeficiencia = false;
	limparBuffer();
	printf("\nPossui algum membro da fam�lia com Transtorno Global do Desenvolvimento (TGD)? (S/N): ");
	if (getchar() == 'S') atendimento.membroFamiliarTGD = true;
	else atendimento.membroFamiliarTGD = false;
	limparBuffer();
	printf("\nPossui algum membro da fam�lia idoso? (S/N): ");
	if (getchar() == 'S') atendimento.membroFamiliarIdoso = true;
	else atendimento.membroFamiliarIdoso = false;
	limparBuffer();
	printf("\nMembro familiar egresso prisional de at� 4 meses (S/N): ");
	if (getchar() == 'S') atendimento.membroFamiliarEgressoPrisional = true;
	else atendimento.membroFamiliarEgressoPrisional = false;
	limparBuffer();

	


	printf("\nRecebe algum benef�cio assistencial do governo? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.recebeBeneficio = true;
		do
		{
			printf("\nQual o valor do benef�cio? ");
			scanf("%d", &atendimento.valorBeneficio);
			limparBuffer();

		} while (atendimento.valorBeneficio < 50 && atendimento.valorBeneficio > 5000);
		
	}
	else
	{
		atendimento.recebeBeneficio = false;
		atendimento.valorBeneficio = 0;
		limparBuffer();
	}
	

	do {
		printf("\nValor da renda mensal do assistido: ");
		scanf("%d", &atendimento.valorRenda);
		limparBuffer();
	} while (atendimento.valorRenda < 0 || atendimento.valorRenda > 1000000);

	do
	{
		printf("\nValor total da renda familiar: ");
		scanf("%d", &atendimento.totalRendaFamiliar);
		limparBuffer();
		if (atendimento.totalRendaFamiliar < 0 || atendimento.totalRendaFamiliar > 1000000) printf("Valor inv�lido. Digite um valor entre 0 e 1.000.000\n");
	} while (atendimento.totalRendaFamiliar < 0 || atendimento.totalRendaFamiliar > 1000000);


	printf("\nPossui gastos m�dicos? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.temGastosMedicos = true;
		printf("\nQual o valor dos gastos m�dicos? ");
		scanf("%d", &atendimento.valorGastosMedicos);
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
		scanf("%d", &atendimento.valorInvestimento);
	}
	else
	{
		atendimento.possuiInvestimento = false;
		atendimento.valorInvestimento = 0;
	}
	limparBuffer();

	printf("\nPossui casa pr�pria? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.possuiCasaPropria = true;
		printf("\nQual o valor da casa pr�pria? ");
		scanf("%d", &atendimento.valorCasaPropria);
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
		scanf("%d", &atendimento.valorApartamento);
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
		scanf("%d", &atendimento.valorTerreno);
	}
	else
	{
		atendimento.possuiTerreno = false;
		atendimento.valorTerreno = 0;
	}
	limparBuffer();

	printf("\nPossui im�vel comercial? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.possuiImovelComercial = true;
		printf("\nQual o valor do im�vel comercial? ");
		scanf("%d", &atendimento.valorImovelComercial);
	}
	else
	{
		atendimento.possuiImovelComercial = false;
		atendimento.valorImovelComercial = 0;
	}
	limparBuffer();

	printf("\nPossui ve�culo? (S/N): ");
	if (getchar() == 'S')
	{
		atendimento.possuiVeiculo = true;
		printf("\nQual o valor do ve�culo? ");
		scanf("%d", &atendimento.valorVeiculo);
	}
	else
	{
		atendimento.possuiVeiculo = false;
		atendimento.valorVeiculo = 0;
	}
	limparBuffer();

	printf("\nA demanda envolve viol�ncia dom�stica? (S/N): ");
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

	//Abre o arquivo CLIENTES.DAT
	arquivoCasos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\CLIENTES.DAT", "a+b");

	if (arquivoCasos == NULL)
	{
		printf("Erro ao abrir CLIENTES.DAT\n");
		system("pause");
		exit(0);
	};

	//Grava o atendimento no arquivo CLIENTES.DAT
	fwrite(&atendimento, sizeof(atendimento), 1, arquivoCasos);

	//Fecha o arquivo CLIENTES.DAT
	fclose(arquivoCasos);

	printf("\nCASO REGISTRADO NO SISTEMA COM SUCESSO!\n");

	//Exibe o relat�rio do atendimento
	gerarRelatorio(&atendimento);

	printf("\n------------------------------------------------------\n");

}

//Fun��o que simplemente exibe todos os casos em andamento no console
void mostrarCasosEmAndamento()
{
	int count = 0;

	//Abre o arquivo CLIENTES.DAT
	arquivoCasos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\CLIENTES.DAT", "r+b");

	// Se por algum motivo o arquivo n�o puder ser aberto, arquivoCasos ser� NULL
	if (arquivoCasos == NULL)
	{
		printf("Erro ao abrir CLIENTES.DAT\n");
		system("pause");
		exit(0);
	};

	printf("\n----------- LISTA DE CASOS NO SISTEMA -------------\n");

	//Enquanto n�o chegar ao final do arquivo (feof - end of file)...
	while (!feof(arquivoCasos))
	{
		//...l� o pr�ximo atendimento
		fread(&atendimento, sizeof(atendimento), 1, arquivoCasos);
		if (!feof(arquivoCasos))
		{
			//Soma o n�mero de atendimentos
			count++;
			//Exibe o relat�rio do atendimento no console
			gerarRelatorio(&atendimento);
		}
		if (count == 0) printf("\nNenhum caso em andamento\n");
	}

	count = 0;

	fclose(arquivoCasos);

	printf("\n-------------------------------------------------------\n");

	system("pause");
}

//Fun��o para retornar um caso espec�fico. Pode ser utilizado para buscar uma atribui��o de um estagi�rio, por exemplo.
//Recebe o c�digo do atendimento como par�metro
triagem retornarCasoEspecifico(int codAtendimento)
{
	bool encontrado = false;

	//Abre o arquivo CLIENTES.DAT
	arquivoCasos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\CLIENTES.DAT", "r+b");

	// Se por algum motivo o arquivo n�o puder ser aberto, arquivoCasos ser� NULL
	if (arquivoCasos == NULL)
	{
		printf("Erro ao abrir CLIENTES.DAT\n");
		system("pause");
		exit(0);
	};

	//Enquanto n�o chegar ao final do arquivo (feof - end of file)...
	while (!feof(arquivoCasos))

	{
		//...l� o pr�ximo atendimento
		fread(&atendimento, sizeof(atendimento), 1, arquivoCasos);

		if (!feof(arquivoCasos))
		{
			//Se o c�digo do atendimento for igual ao c�digo passado como par�metro
			//o loop � interrompido
			//o atendimento fica salvo na vari�vel global atendimento
			if (atendimento.codAtendimento == codAtendimento)
			{
				encontrado = true;
				break;
			}
		}
	}


	//Se o atendimento n�o for encontrado, exibe mensagem de erro e encerra o programa
	if (!encontrado) {
		printf("Nenhum caso encontrado com o c�digo de atendimento %d\n\n", codAtendimento);
		system("pause");
		exit(0);
	}

	fclose(arquivoCasos);

	return atendimento;
}

//Fun��o utilizada para gerar o c�digo do atendimento e retorn�-lo
int retornarCodAtendimento()
{
	triagem ultimoAtendimento; //Vari�vel que armazenar� o �ltimo atendimento registrado

	//Abre o arquivo CLIENTES.DAT
	arquivoCasos = fopen("C:\\Users\\kened\\OneDrive\\Documentos\\C#\\Departamento Jur�dico\\data\\CLIENTES.DAT", "r+b");

	// Se por algum motivo o arquivo n�o puder ser aberto, arquivoCasos ser� sempre NULL
	// Causas mais comuns : arquivo n�o existe, caminho do arquivo incorreto, arquivo aberto em outro local
	if (arquivoCasos == NULL)
	{
		printf("Erro ao abrir CLIENTES.DAT\n");
		system("pause");
		// O programa ser� encerrado completamente. **Pode ser utilizada outra abordagem.
		exit(0);
	};

	//Passando pelo IF anterior, o arquivo foi aberto com sucesso.
	//fseek � usada para mover o cursor de leitura/escrita para uma posi��o espec�fica em um arquivo, permitindo saltar para diferentes partes do arquivo.
	fseek(arquivoCasos, -1 * sizeof(triagem), SEEK_END);
	//com os parametros acima, o cursor foi movido para a �ltima linha do arquivo CLIENTES.DAT

	//fread � usada para ler um bloco de dados de um arquivo
	//com o cursos movido para a �ltima linha do arquivo, a fun��o fread l� o �ltimo atendimento registrado
	fread(&ultimoAtendimento, sizeof(triagem), 1, arquivoCasos);
	if (feof(arquivoCasos)) ultimoAtendimento.codAtendimento = 0;
	//Se n�o houver atendimentos registrados, o c�digo do atendimento ser� 0 provisoriamente

	//Fecha o arquivo CLIENTES.DAT
	fclose(arquivoCasos);

	//Retorna o c�digo do �ltimo atendimento registrado (ou zero) + 1
	return ultimoAtendimento.codAtendimento + 1;
};


//Fun��o para gerar relat�rio do atendimento
//Recebe o ponteiro do atendimento como par�metro
void gerarRelatorio(triagem* atendimento)
{
	printf("\nCod. Atendimento         : %d\n", atendimento->codAtendimento);
	printf("Cod. Estagi�rio Atendente  : %d\n", atendimento->codEstagiario);
	printf("Data                       : %s\n", atendimento->data);
	printf("Hora de Atendimento        : %s\n", atendimento->horaAtendimento);
	printf("Hora de Chegada            : %s\n", atendimento->horaChegada);
	printf("Fonte de Informa��o        : %s\n", atendimento->fonteInformacaoServico);
	printf("Pessoa Fisica/Juridica     : %c\n", atendimento->tipoPessoa);
	printf("Nome do(a) Atendido        : %s\n", atendimento->nome);
	printf("G�nero                     : %s\n", atendimento->genero);
	printf("Comunidade LGBTQIA+        : %s\n", atendimento->comLgbt ? "Sim" : "N�o");
	printf("Cor/Ra�a                   : %s\n", atendimento->corRaca);
	printf("Data de Nascimento         : %s\n", atendimento->dataNascimento);
	printf("Nacionalidade              : %s\n", atendimento->nacionalidade);
	printf("Naturalidade               : %s\n", atendimento->naturalidade);
	printf("CPF                        : %s\n", atendimento->cpf);
	printf("RG                         : %s\n", atendimento->rg);
	printf("Endere�o                   : %s\n", atendimento->endereco);
	printf("Celular                    : %s\n", atendimento->celular);
	printf("WhatsApp                   : %s\n", atendimento->whatsapp ? "Sim" : "N�o");
	printf("Tel. Alternativo           : %s\n", atendimento->telAlternativo);
	printf("E-mail                     : %s\n", atendimento->email);
	printf("Escolaridade               : %s\n", atendimento->escolaridade);
	printf("Profiss�o                  : %s\n", atendimento->profissao);
	printf("Situa��o Profissional      : %s\n", atendimento->situacaoProfissional);
	printf("Estado Civil               : %s\n", atendimento->estadoCivil);
	printf("Possui Filhos              : %s\n", atendimento->temFilhos ? "Sim" : "N�o");
	if (atendimento->temFilhos) printf("Qtd. Filhos Morando        : %d\n", atendimento->qtdFilhosMorando);
	printf("Total Membros Fam�lia      : %d\n", atendimento->totalMembrosFamilia);
	printf("Membro com Defici�ncia     : %s\n", atendimento->membroFamiliaDeficiencia ? "Sim" : "N�o");
	printf("Membro com TGD             : %s\n", atendimento->membroFamiliarTGD ? "Sim" : "N�o");
	printf("Membro Idoso               : %s\n", atendimento->membroFamiliarIdoso ? "Sim" : "N�o");
	printf("Membro Egresso Prisional   : %s\n", atendimento->membroFamiliarEgressoPrisional ? "Sim" : "N�o");
	printf("Recebe Benef�cio           : %s\n", atendimento->recebeBeneficio ? "Sim" : "N�o");
	if (atendimento->recebeBeneficio) printf("Valor do Benef�cio         : %d\n", atendimento->valorBeneficio);
	printf("Valor da Renda             : %d\n", atendimento->valorRenda);
	printf("Total Renda Familiar       : %d\n", atendimento->totalRendaFamiliar);
	printf("Possui Gastos M�dicos      : %s\n", atendimento->temGastosMedicos ? "Sim" : "N�o");
	if (atendimento->temGastosMedicos) printf("Valor Gastos M�dicos       : %d\n", atendimento->valorGastosMedicos);
	printf("Possui Investimento        : %s\n", atendimento->possuiInvestimento ? "Sim" : "N�o");
	if (atendimento->possuiInvestimento) printf("Valor Investimento         : %d\n", atendimento->valorInvestimento);
	printf("Possui Casa Pr�pria        : %s\n", atendimento->possuiCasaPropria ? "Sim" : "N�o");
	if (atendimento->possuiCasaPropria) printf("Valor Casa Pr�pria         : %d\n", atendimento->valorCasaPropria);
	printf("Possui Apartamento         : %s\n", atendimento->possuiApartamento ? "Sim" : "N�o");
	if (atendimento->possuiApartamento) 	printf("Valor Apartamento          : %d\n", atendimento->valorApartamento);
	printf("Possui Terreno             : %s\n", atendimento->possuiTerreno ? "Sim" : "N�o");
	if (atendimento->possuiTerreno) 	printf("Valor Terreno              : %d\n", atendimento->valorTerreno);
	printf("Possui Im�vel Comercial    : %s\n", atendimento->possuiImovelComercial ? "Sim" : "N�o");
	if (atendimento->possuiImovelComercial) 	printf("Valor Im�vel Comercial     : %d\n", atendimento->valorImovelComercial);
	printf("Possui Ve�culo             : %s\n", atendimento->possuiVeiculo ? "Sim" : "N�o");
	if (atendimento->possuiVeiculo) 	printf("Valor Ve�culo              : %d\n", atendimento->valorVeiculo);
	printf("Demanda Viol�ncia Dom�stica: %s\n", atendimento->demandaViolenciaDomestica ? "Sim" : "N�o");
	printf("Resumo do Caso             : %s\n", atendimento->resumoCaso);
	printf("Ramo do Direito            : %s\n", atendimento->ramoDireito);
	printf("Perfil Enquadrado          : %s\n", atendimento->perfilEnquadrado ? "Sim" : "N�o");
}

//Fun��o para verificar se o perfil do atendido se enquadra nos crit�rios de atendimento
//Recebe o ponteiro do atendimento como par�metro
void verificarPerfilEnquadrado(triagem* atendimento)
{
	//Se a renda familiar for menor ou igual a 3 sal�rios m�nimos, o perfil � enquadrado
	if (atendimento->totalRendaFamiliar <= 3 * salMinimo) {
		printf("Perfil enquadrado por ter renda familiar menor ou igual que tres salarios minimos\n");
		atendimento->perfilEnquadrado = true;
	}
	//Se a renda familiar for menor ou igual a 4 sal�rios m�nimos...
	else if (atendimento->totalRendaFamiliar <= 4 * salMinimo) {
		printf("Renda familiar menor ou igual que 4 salarios minimos. Verificando outras condi��es\n");
		//o perfil � enquadrado se:

		//o n�mero de membros da fam�lia for maior que 5
		if (atendimento->totalMembrosFamilia > 5)
		{
			printf("N�mero de membros da familia maior que 5. Perfil enquadarado\n");
			atendimento->perfilEnquadrado = true;
		}
		//ou se o atendido tiver gastos m�dicos 
		else if (atendimento->temGastosMedicos)
		{
			printf("Tem gastos medicos. Perfil enquadarado\n");
			atendimento->perfilEnquadrado = true;
		}
		//ou se o atendido possui membro da fam�lia com defici�ncia ou TGD
		else if (atendimento->membroFamiliaDeficiencia || atendimento->membroFamiliarTGD)
		{
			printf("Membro da familia com deficiencia ou TGD. Perfil enquadarado\n");
			atendimento->perfilEnquadrado = true;
		}
		//ou se o atendido possui membro da fam�lia idoso ou egresso prisional e o n�mero de membros da fam�lia for maior ou igual a 4.
		else if ((atendimento->membroFamiliarIdoso || atendimento->membroFamiliarEgressoPrisional) && atendimento->totalMembrosFamilia >= 4)
		{
			printf("Membro da familia idoso ou egresso prisional com mais de 4 membros. Perfil enquadarado\n");
			atendimento->perfilEnquadrado = true;
		}
		//Se nenhuma das condi��es acima for atendida, o perfil n�o � enquadrado
		else {
			printf("Perfil N�O enquadrado.\n");
			atendimento->perfilEnquadrado = false;
		}
	}

}