#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

static void exibirSalas()
{
    printf("ID | Nome  | Descrição                  | Lotação Máxima\n");
    printf("1  |Sala A | Sala de Aula com Projetor  | 30\n");
    printf("2  |Sala B | Laboratório de Informática | 20\n");
    printf("3  |Sala C | Sala de Reuniões           | 15\n");
    printf("4  |Sala D | Auditório                  | 100\n");
    printf("5  |Sala E | Sala de Estudos            | 10\n");
    printf("6  |Sala F | Sala de Estudos            | 10\n");
    printf("7  |Sala G | Sala de Estudos            | 10\n");
    printf("8  |Sala H | Sala de Estudos            | 10\n");
    printf("\n");
}

void inicializarSalas(Sala **salas, int *numSalas)
{
    const char *nomes[] = {"Sala A", "Sala B", "Sala C", "Sala D", "Sala E", "Sala F", "Sala G", "Sala H"};
    const char *descricoes[] = {"Sala de Aula com Projetor", "Laboratório de Informática", "Sala de Reuniões", "Auditório", "Sala de Estudos", "Sala de Estudos", "Sala de Estudos", "Sala de Estudos"};
    int lotacoes[] = {30, 20, 15, 100, 10, 10, 10, 10};

    *salas = realloc(*salas, 8 * sizeof(Sala));
    if (*salas == NULL)
    {
        printf("Erro ao alocar memória para as salas.\n");
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        Sala *newSala = &(*salas)[i];
        newSala->id = i + 1;
        strcpy(newSala->nome, nomes[i]);
        strcpy(newSala->descricao, descricoes[i]);
        newSala->lotacaoMaxima = lotacoes[i];
    }

    *numSalas = 8;
}

void criarSala(Sala **salas, int *numSalas)
{
    exibirSalas();
    int id;
    printf("Digite um ID baseado no que foi exibido para criar uma sala: ");
    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("ID inválido.\n");
        return;
    }

    for (int i = 0; i < *numSalas; i++)
    {
        if ((*salas)[i].id == id)
        {
            printf("Este ID já está em uso. Por favor, escolha outro.\n");
            return;
        }
    }

   Sala *temp = realloc(*salas, (*numSalas + 1) * sizeof(Sala));
    if (temp == NULL) {
        printf("Erro ao alocar memória para a sala.\n");
        return;
    }
    *salas = temp;

    Sala *newSala = &(*salas)[*numSalas];
    newSala->id = id;

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Digite o nome da sala: ");
    fgets(newSala->nome, MAX_NOME, stdin);
    newSala->nome[strcspn(newSala->nome, "\n")] = 0;

    printf("Digite a descrição da sala: ");
    fgets(newSala->descricao, MAX_DESCRICAO, stdin);
    newSala->descricao[strcspn(newSala->descricao, "\n")] = 0;

    printf("Digite a lotação máxima da sala: ");
    if (scanf("%d", &newSala->lotacaoMaxima) != 1 || newSala->lotacaoMaxima <= 0)
    {
        printf("Lotação máxima inválida.\n");
        return;
    }
    newSala->disponivel = 1;
    (*numSalas)++;

    FILE *file = fopen("agendar_sala.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%d,%s,%s,%d,%d\n", newSala->id, newSala->nome, newSala->descricao, newSala->lotacaoMaxima, newSala->disponivel);
        fclose(file);
    }
    else
    {
        printf("Erro ao abrir o arquivo.\n");
    }
}

void reservarSala(Sala *salas, int numSalas, Reserva **reservas, int *numReservas)
{
    int idSala, quantidadePessoas;
    printf("Insira o Id da sala que gostaria de reservar: ");
    if (scanf("%d", &idSala) != 1 || idSala <= 0)
    {
        printf("ID da sala inválido.\n");
        return;
    }

    Sala *salaSelecionada = NULL;
    for (int i = 0; i < numSalas; i++)
    {
        if (salas[i].id == idSala)
        {
            salaSelecionada = &salas[i];
            break;
        }
    }

    if (salaSelecionada == NULL)
    {
        printf("ID da sala inválido.\n");
        return;
    }

    printf("ID: %d, Nome: %s, Descrição: %s, Lotação Máxima: %d\n",
           salaSelecionada->id, salaSelecionada->nome, salaSelecionada->descricao, salaSelecionada->lotacaoMaxima);

    char diaReservado[11];
    char convertedDate[11];
    bool dateIsValid = false;

    while (!dateIsValid)
    {
        printf("Insira a data que gostaria de reservar (no formato: DD-MM-YYYY): ");
        if (scanf("%10s", diaReservado) != 1)
        {
            printf("Data inválida.\n");
            return;
        }

        snprintf(convertedDate, sizeof(convertedDate), "%.4s-%.2s-%.2s", &diaReservado[6], &diaReservado[3], &diaReservado[0]);

        if (!verificaDisponibilidade(*reservas, *numReservas, idSala, convertedDate))
        {
            printf("A Sala não está disponível no dia solicitado. Por favor, escolha outra data.\n");
        }
        else
        {
            dateIsValid = true;
        }
    }

    do
    {
        printf("Insira o número de participantes: ");
        if (scanf("%d", &quantidadePessoas) != 1 || quantidadePessoas <= 0)
        {
            printf("Número de participantes inválido.\n");
            return;
        }

        if (quantidadePessoas > salaSelecionada->lotacaoMaxima)
        {
            printf("O número de participantes excede a lotação máxima da sala %s. A lotação máxima é de %d pessoas.\n",
                   salaSelecionada->nome, salaSelecionada->lotacaoMaxima);
        }
    } while (quantidadePessoas > salaSelecionada->lotacaoMaxima);

    *reservas = realloc(*reservas, (*numReservas + 1) * sizeof(Reserva));
    if (*reservas == NULL)
    {
        printf("Erro ao alocar memória para a reserva.\n");
        return;
    }

    Reserva *newReserva = &(*reservas)[*numReservas];
    newReserva->idSala = idSala;
    strcpy(newReserva->diaReservado, convertedDate);
    newReserva->quantidadePessoas = quantidadePessoas;
    (*numReservas)++;

    FILE *file = fopen("reservas.txt", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(file, "ID da Sala: %d, Data Reservada: %s, Número de Participantes: %d\n",
            idSala, convertedDate, quantidadePessoas);
    fclose(file);
}

bool verificaDisponibilidade(Reserva *reservas, int numReservas, int idSala, const char *diaReservado)
{
    for (int i = 0; i < numReservas; i++)
    {
        if (reservas[i].idSala == idSala && strcmp(reservas[i].diaReservado, diaReservado) == 0)
        {
            return false;
        }
    }

    return true;
}
