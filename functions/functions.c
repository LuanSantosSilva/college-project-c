#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int opcao;
int opcao_setor;
int setor;
int atendimento;
char nome_atendimento[20];
int indice = 0;

bool validarCPF(char cpf[]) {
    if (strlen(cpf) != 11) {
        return false;
    }

    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return false;
        }
    }

    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int digito1 = 11 - (soma % 11);
    if (digito1 >= 10) {
        digito1 = 0;
    }

    if (digito1 != cpf[9] - '0') {
        return false;
    }

    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * (11 - i);
    }
    int digito2 = 11 - (soma % 11);
    if (digito2 >= 10) {
        digito2 = 0;
    }

    if (digito2 != cpf[10] - '0') {
        return false;
    }

    return true;
}

void limpar()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
}

struct Pessoa
{
    char nome[50];
    char cpf[12];
    char tipo_atendimento[50];
};

void menu_inicial();

void opcao_atendimento(struct Pessoa *registro)
{
    scanf("%d", &opcao_setor);

    switch (opcao_setor)
    {

    case 1:
        strcpy(registro->tipo_atendimento, "1 - Abertura de Conta");
        break;

    case 2:
        strcpy(registro->tipo_atendimento, "2 - Caixa");
        break;

    case 3:
        strcpy(registro->tipo_atendimento, "3 - Gerente Pessoa Física");
        break;

    case 4:
        strcpy(registro->tipo_atendimento, "4 - Gerente Pessoa Jurídica");
        break;

    default:
        printf("Por favor, selecione uma opção válida");
        opcao_atendimento(registro);
        break;
    }
}

struct Pessoa registro[50];
void solicitar_atendimento()
{
    if (indice < 50)
    {
        printf("Escreva seu nome completo:\n");
        getchar();
        fgets(registro[indice].nome, sizeof(registro[indice].nome), stdin);
        registro[indice].nome[strcspn(registro[indice].nome, "\n")] = '\0';

        while (1) {
        printf("Digite o CPF (apenas números): ");
        scanf("%s",registro[indice].cpf);

        if (validarCPF(registro[indice].cpf)) {
            printf("CPF válido!\n");
            break;
        } else {
            printf("CPF inválido! Tente novamente.\n");
        }}

        printf("\nSelecione o tipo de atendimento:\n");
        printf("1 - Abertura de Conta\n");
        printf("2 - Caixa\n");
        printf("3 - Gerente Pessoa Física\n");
        printf("4 - Gerente Pessoa Jurídica\n");

        opcao_atendimento(&registro[indice]);
        indice++;
    }else{
        printf("Não é possível fazer mais nenhum registro, o limite de 50 registros foi atingido\n");
    }
}
void listar_atendimentos(int pesquisa_setor)
{
    int quantidade = 0;
    if (pesquisa_setor == 0)
    {
        for (int i = 0; i < indice; i++)
        {
            printf("Nome: %s\n", registro[i].nome);
            printf("CPF: %s\n", registro[i].cpf);
            printf("Tipo Atendimento: %s\n", registro[i].tipo_atendimento);

            if (indice != 1)
            {
                printf("===============================\n");
            }
            else
            {
                printf("\n");
            }
            quantidade++;
        }
    }
    else
    {
        const char *setores[4];
        setores[0] = "1 - Abertura de Conta";
        setores[1] = "2 - Caixa";
        setores[2] = "3 - Gerente Pessoa Física";
        setores[3] = "4 - Gerente Pessoa Jurídica";

        pesquisa_setor--;

        for (int i = 0; i < indice; i++)
        {
            if (strcmp(registro[i].tipo_atendimento, setores[pesquisa_setor]) == 0)
            {
                printf("Nome: %s\n", registro[i].nome);
                printf("CPF: %s\n", registro[i].cpf);
                printf("Tipo Atendimento: %s\n", registro[i].tipo_atendimento);

                if (indice != 1)
                {
                    printf("===============================\n");
                }
                else
                {
                    printf("\n");
                }

                quantidade++;
            }
        }
    }

    if (quantidade == 0)
    {
        printf("Nenhum registro encontrado\n");
    }
}
void listar_atendimentos_setor()
{
    do
    {
        printf("Setores disponíveis para listagem\n");
        printf("1 - Abertura de Conta\n");
        printf("2 - Caixa\n");
        printf("3 - Gerente Pessoa Física\n");
        printf("4 - Gerente Pessoa Jurídica\n");

        printf("\nDigite o número do setor que deseja listar:\n");
        scanf("%d", &setor);
        if (setor < 1 || setor > 4)
        {
            printf("Por favor, digite um número válido\n");
        }
    } while (setor < 1 || setor > 4);

    listar_atendimentos(setor);
}

void menu_inicial()
{
    do
    {
        printf("Bem-vindo ao sistema de atendimento\n");
        printf("1 - Solicitar Atendimento\n");
        printf("2 - Listar Atendimentos Registrados\n");
        printf("3 - Listar Atendimento por Setor\n");
        printf("4 - Sair\n");
        printf("\nDigite o número correspondente a ação que deseja realizar:\n");
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:
            limpar();
            solicitar_atendimento();
            break;

        case 2:
            limpar();
            listar_atendimentos(0);
            break;

        case 3:
            limpar();
            listar_atendimentos_setor();
            break;

        case 4:
            limpar();
            printf("Encerrando programa");
            break;

        default:
            printf("Por favor, selecione uma opção válida");
            break;
        }
    } while (opcao != 4);
}