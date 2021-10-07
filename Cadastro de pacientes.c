// Código para cadastrar e realizar uma triagem de pacientes com comorbidades. Ao final um arquivo .txt será gerado no mesmo
// diretório ao executar este código; irá conter todos os pacientes da triagem cadastral.
// O código está modularizado e poossui validação de dados, bem como para datas e anos bissextos.
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <dirent.h>
#include <ctype.h>
#define VERMELHO "\x1b[31m" // definição da cor vermelho para a palavra VERMELHO.
#define VERDE "\x1b[32m"    // definição da cor verde para a palavra VERDE.
#define RESET "\x1b[0m"     // definição da cor padrão para a palavra RESET.

void cabecalho() //função que cria um cabeçalho padrão.
{
    printf("--------------------------------------------------------------------------------------------\n");
    printf("         ----- <<< SISTEMA DE CADASTRAMENTO DE PACIENTES COM COVID-19 >>> -----\n");
    printf("--------------------------------------------------------------------------------------------\n");
}

void login() // função para realizar o login do usuário
{
    char root[5] = "root", pass[5] = "pass";
    char usuario[20], senha[20];
    int autenticado = 0;
    cabecalho();
    printf("\n                     -=-=-=-=-=-=-= LOGIN DE USUÁRIO =-=-=-=-=-=-=-\n\n");
    printf("Digite o nome de usuário: ");
    scanf("%s", &usuario);
    printf("Digite a senha: ");
    scanf("%s", &senha);
    if ((strcmp(root, usuario) == 0) && (strcmp(pass, senha) == 0))
            {
                autenticado = 1;
            }
    while (autenticado == 0)
        {
        system("cls");
        cabecalho();
        printf(VERMELHO "Usuário ou senha inválidos, digite novamente.\n" RESET);
        printf(VERMELHO "Confira usuário e senha de acesso no seu manual.\n\n" RESET);
        printf("\n                     -=-=-=-=-=-=-= LOGIN DE USUÁRIO =-=-=-=-=-=-=-\n\n");
        printf("Digite o nome de usuário: ");
        scanf("%s", &usuario);
        printf("Digite a senha: ");
        scanf("%s", &senha);
        if ((strcmp(root, usuario) == 0) && (strcmp(pass, senha) == 0))
            {
                break;
            }
        }
    system("cls");
    cabecalho();
    printf(VERDE"                       ---< USUÁRIO AUTENTICADO COM SUCESSO >---\n"RESET);
    printf(VERDE"                             ---< BEM VINDO AO SISTEMA >---\n"RESET);
    printf("\n >>> Após a execução deste programa, será criado dois arquivo .txt com as seguintes informações:\n");
    printf("   1. Os arquivos estarão dentro de uma pasta chamada PIM IV no diretório onde este código fonte foi executado.\n");
    printf("   2. Cadastro.txt --> será o arquivo que irá conter todos os dados de todos os pacientes cadastrados.\n");
    printf("   3. Secretaria.txt --> caso o paciente possua mais de 65 anos e possua comorbidade, será gravado no Secretaria.txt:\n");
    printf("      -> A idade do paciente cadastrado;\n");
    printf("      -> O CEP do paciente cadastrado.\n\n");
    system("pause");
    fflush(stdin);
    system("cls");
}

int verifica_string(char letras[60]) { // função que verifica se o que foi digitado é somente letras
    fflush(stdin);
    int saida = 0;
    int i;
    saida = 0;
    for (i = 0; letras[i] != '\0'; i++) {
        if (isspace(letras[0])){
            saida = 1;
            break;
        }
        if (!isalpha(letras[i]) && !isspace(letras[i])){
            printf("Caractere inválido [%c]\n", letras[i]);
            saida = 1;
        }
    }
    return saida;
}

int verifica_inteiro(char inteiro[20]) { //verifica se o que foi digitado é apenas números.
    fflush(stdin);
    int saida = 0;
    int i;
    saida = 0;
    for (i = 0; inteiro[i] != '\0'; i++) {
        if (isspace(inteiro[0])){
            saida = 1;
            break;
        }
        if (!isdigit(inteiro[i]) && !isspace(inteiro[i])){
            printf("Caractere inválido [%c]\n", inteiro[i]);
            saida = 1;
            }
        }
    return saida;
}

int verifica_bissexto(int ano) { //verifica se o ano digitado é bissexto
    bool bissexto;
    if (ano % 400 == 0) {
        bissexto = true;
    }else if ((ano % 4 == 0) && (ano % 100 != 0)) {
        bissexto = true;
    } else {
        bissexto = false;
    }
    return bissexto;
}
//---------------------------------------PROGRAMA PRINCIPAL---------------------------------------//
void main()
{
    setlocale(LC_ALL, "Portuguese"); //Define o sistema para que a sintaxe da língua portuguesa possa ser interpretada corretamente.
// Variáveis:
    char continua, possui;
    char nome[50], cpf[15], telefone[20];
    char CEP[10];
    char rua[40], numero[10], bairro[20], cidade[30], estado[30];
    char mes_nasc[3], dia_nasc[3], ano_nasc[10];
    char email[30];
    int maior65;
    char comorbidade[30], data_diagnostico[10];
    char dia_diagnostico[10], mes_diagnostico[10], ano_diagnostico[10];
    int anoAtual, idade;
    login(); // realiza o login do usuário.
    FILE *ponteiro; //cria a variável ponteiro para manipulação de arquivo.
    mkdir("PIM IV"); //cria o diretório chamado "PIM IV" na pasta onde o executável e código fonte estão localizados.
    continua = 's';
    while (continua == 's'){
        system("cls");
        cabecalho();
        fflush(stdin);
        printf("\n   -=-=-= DADOS DO PACIENTE =-=-=-\n\n");
        do {
            printf("Informe o nome do paciente [somente letras]: ");
            gets(nome);
        } while ( verifica_string(nome) == 1 || strcmp(nome, "") == 0 );
        fflush(stdin);
        do {
            printf("Informe o CPF [somente números]: ");
            gets(cpf);
        } while (verifica_inteiro(cpf) == 1 || strcmp(cpf, "") == 0 );
        do {
            printf("Informe o telefone [somente números]: ");
            gets(telefone);
        } while (verifica_inteiro(telefone) == 1 || strcmp(telefone, "") == 0 );
        system("cls");
        cabecalho();
        printf("\n   -=-=-= ENDEREÇO DO PACIENTE "VERDE"%s "RESET"=-=-=-\n\n", nome);
        do {
            printf("CEP [somente números]: ");
            gets(CEP);
        } while (verifica_inteiro(CEP) == 1 || strcmp(CEP, "") == 0 );
        fflush(stdin);
        do {
            printf("Rua........[somente letras]: ");
            gets(rua);
        } while ( verifica_string(rua) == 1 || strcmp(rua, "") == 0 );
        do {
            printf("Número....[somente números]: ");
            gets(numero);
        } while (verifica_inteiro(numero) == 1 || strcmp(numero, "") == 0 );
        do {
            printf("Bairro.....[somente letras]: ");
            gets(bairro);
        } while ( verifica_string(bairro) == 1 || strcmp(bairro, "") == 0 );
        do {
            printf("Cidade.....[somente letras]: ");
            gets(cidade);
        } while ( verifica_string(cidade) == 1 || strcmp(cidade, "") == 0 );
        do {
            printf("Estado.....[somente letras]: ");
            gets(estado);
        } while ( verifica_string(estado) == 1 || strcmp(estado, "") == 0 );
        system("cls");
        cabecalho();
        printf("\n   -=-=-= DATA DE NASCIMENTO DE " VERDE"%s"RESET" =-=-=-\n\n", nome);
        SYSTEMTIME anoAtual;
            GetSystemTime(&anoAtual);
        int ano = anoAtual.wYear;
        int transforma_ano; // variável para converter o ano digitado para inteiro.
        do {
            printf("O ano deve possuir 4 dígitos, ser maior que 1900 e menor que o ano atual.\n");
            printf("NOTA: se você nasceu em um ano bissexto, é possível digitar 29 de fevereiro.\n\n");
            printf("Ano de nascimento [xxxx]: ");
            gets(ano_nasc);
            transforma_ano = atoi(ano_nasc);
        } while (verifica_inteiro(ano_nasc) == 1 || transforma_ano < 1900 || transforma_ano > ano);
        verifica_bissexto(transforma_ano); // verifica se o ano digitado é bissexto, retornando true para sim ou false para não
        int transforma_mes; // variável para converter o mês digitado para inteiro.
        do {
            printf("Mês de nascimento [1 a 12]: ");
            gets(mes_nasc);
            transforma_mes = atoi(mes_nasc);
        } while (verifica_inteiro(mes_nasc) == 1 || transforma_mes > 12 || transforma_mes < 1);
        int transforma_dia; // variável para converter o dia digitado para inteiro.
        bool confirma_dia;
        do{
            confirma_dia = false;
            printf("Dia do nascimento: ");
            gets(dia_nasc);
            transforma_dia = atoi(dia_nasc);
            if (transforma_mes == 2 && verifica_bissexto(transforma_ano) == true && (transforma_dia <= 29 && transforma_dia >=1)) {
                confirma_dia = true;
            } else {
                if (transforma_mes == 2 && verifica_bissexto(transforma_ano) == false && (transforma_dia <= 28 && transforma_dia >=1))
                    confirma_dia = true;
                    }
            if ((transforma_mes == 1 || transforma_mes == 3 || transforma_mes == 5 || transforma_mes == 7 ||
                transforma_mes == 8 || transforma_mes == 10 || transforma_mes == 12) && (transforma_dia <=31 && transforma_dia >=1)){
                    confirma_dia = true;
                } else {
                    if ((transforma_mes == 4 || transforma_mes == 6 || transforma_mes == 9 || transforma_mes == 11)
                        && (transforma_dia <= 30 && transforma_dia >=1)){
                            confirma_dia = true;
                        }
                    }
            } while (verifica_inteiro(dia_nasc) == 1 || confirma_dia == false);
        printf("\nInfome o seu e-mail: ");
        gets(email);
        int transforma_dia_diag, transforma_mes_diag, transforma_ano_diag; // variáveis de controle para data do diagnóstico
        system("cls");
        cabecalho();
        printf("\n   -=-=-= DATA EM QUE "VERDE"%s"RESET" FOI DIAGNOSTICADO COM COVID-19 =-=-=-\n\n", nome);
        do {
            printf("NOTA: caso o ano seja bissesto, é possível digitar 29 de fevereiro.\n\n");
            printf("Ano do diagnóstico [xxxx]: ");
            gets(ano_diagnostico);
            transforma_ano_diag = atoi(ano_diagnostico);
        } while (verifica_inteiro(ano_diagnostico) == 1 || transforma_ano_diag < 1900 || transforma_ano_diag > ano);
        verifica_bissexto(transforma_ano_diag); // verifica se o ano digitado é bissexto, retornando true para sim ou false para não
        do {
            printf("Mês do diagnóstico [1 a 12]: ");
            gets(mes_diagnostico);
            transforma_mes_diag = atoi(mes_diagnostico);
        } while (verifica_inteiro(mes_diagnostico) == 1 || transforma_mes_diag > 12 || transforma_mes_diag < 1);
        do{
            confirma_dia = false;
            printf("Dia do diagnóstico: ");
            gets(dia_diagnostico);
            transforma_dia_diag = atoi(dia_diagnostico);
            if (transforma_mes_diag == 2 && verifica_bissexto(transforma_ano_diag) == true && (transforma_dia_diag <= 29 && transforma_dia_diag >=1)) {
                confirma_dia = true;
            } else {
                if (transforma_mes_diag == 2 && verifica_bissexto(transforma_ano_diag) == false && (transforma_dia_diag <= 28 && transforma_dia_diag >=1))
                    confirma_dia = true;
                    }
            if ((transforma_mes_diag == 1 || transforma_mes_diag == 3 || transforma_mes_diag == 5 || transforma_mes_diag == 7 ||
                transforma_mes_diag == 8 || transforma_mes_diag == 10 || transforma_mes_diag == 12) && (transforma_dia_diag <=31 && transforma_dia_diag >=1)){
                    confirma_dia = true;
                } else {
                    if ((transforma_mes_diag == 4 || transforma_mes_diag == 6 || transforma_mes_diag == 9 || transforma_mes_diag == 11)
                        && (transforma_dia_diag <= 30 && transforma_dia_diag >=1)){
                            confirma_dia = true;
                        }
                    }
        } while (verifica_inteiro(dia_diagnostico) == 1 || confirma_dia == false);

        do {
            fflush(stdin);
            printf("\nO paciente possui alguma comorbidade [s/n]: ");
            scanf("%c", &possui);
            if (possui == 's') {
            do {
                fflush(stdin);
                printf("\nComorbidade [somente letras]: ");
                gets(comorbidade);
            } while ( verifica_string(comorbidade) == 1 );
            }
        } while (possui != 's' && possui != 'n');

        int converte;
        converte = atoi(ano_nasc); // variável "converte" armazena e converte para INT o ano de nascimento que estava em STRING.
        idade = ano - converte;
        if (idade >= 65 && possui == 's'){
            printf(VERMELHO"Este paciente possui %d anos e possui comorbidade. É considerado paciente de GRUPO DE RISCO!\n", idade, RESET);
            printf(VERMELHO"O CEP e a idade deste paciente serão armazenados no arquivo de texto para que as informações\n"RESET);
            printf(VERMELHO"possam ser enviadas para a central da Secretaria da Saúde da cidade.\n\n"RESET);
            } else{
                if (idade >= 65 ) {
                    printf(VERDE"\nEste paciente possui mais de 65 anos, mas não possui nenhuma comorbidade.\n"RESET);
                    printf(VERDE"Os dados não serão salvos para ser enviados para a central da Secretaria da Saúde da cidade.\n\n"RESET);
                }else{
                printf(VERDE"\nEste paciente possui %d anos, NÃO é considerado paciente de grupo de risco.\n", idade, RESET);
                printf(VERDE"Os dados não serão salvos para ser enviados para a central da Secretaria da Saúde da cidade.\n\n"RESET);
                }
            }
        ponteiro = fopen("PIM IV/Cadastro.txt", "a");
        fprintf(ponteiro, "Paciente: %s\n", nome);
        fprintf(ponteiro, "CPF: %s\n", cpf);
        fprintf(ponteiro, "Telefone: %s\n", telefone);
        fprintf(ponteiro, "CEP: %s\n", CEP);
        fprintf(ponteiro, "Endereço: %s, número %s, bairro %s\n", rua, numero, bairro);
        fprintf(ponteiro, "          %s - %s\n", cidade, estado);
        fprintf(ponteiro, "Data de nascimento: %d/%d/%d\n", transforma_dia, transforma_mes, transforma_ano);
        fprintf(ponteiro, "E-mail: %s\n", email);
        if (possui == 's') {
            fprintf(ponteiro, "Coborbidade: %s\n", comorbidade);
        } else {
             fprintf(ponteiro, "Coborbidade: nenhuma\n");
        }
        fprintf(ponteiro, "Data do diagnóstico: %d/%d/%d\n", transforma_dia_diag, transforma_mes_diag, transforma_ano_diag);
        fprintf(ponteiro, "----------------------------------------\n");
        fclose(ponteiro);
        if (idade >= 65 && possui == 's'){
            ponteiro = fopen("PIM IV/Secretaria.txt", "a"); // insere no arquivo a idade e CEP de pessoas com mais de 65 anos que possuem coborbidade
            fprintf(ponteiro, "Paciente com %d anos de idade\n", idade);
            fprintf(ponteiro, "Residente no CEP %s\n", CEP);
            fprintf(ponteiro, "-------------------------------------\n");
            fclose(ponteiro);
        }
        system("pause");
        do {
            system("cls");
            cabecalho();
            fflush(stdin);
            printf("Deseja adicionar outro paciente [s/n]: ");
            scanf("%c", &continua);
        } while (continua != 's' && continua != 'n');
        if (continua == 'n')
        {
            break;
        }
    }
    system("cls");
    cabecalho();
    printf("                    -=-=-= OBRIGADO POR USAR NOSSO SISTEMA =-=-=-\n");
    printf(VERDE"                        Desenvolvido por Felipe Nodari Fogaça\n"RESET);
    printf("                       ---> UNIP - Universidade Paulista <---\n\n");
    system("pause");
}
