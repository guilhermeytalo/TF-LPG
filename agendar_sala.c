#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

void exibirSalas()
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
    *salas = realloc(*salas, (*numSalas + 1) * sizeof(Sala));
    if (*salas == NULL)
    {
        printf("Erro ao alocar memória para a sala.\n");
        return;
    }

    Sala *newSala = &(*salas)[*numSalas];
    newSala->id = *numSalas;
    (*numSalas)++;

    exibirSalas();

    int id;
    printf("Digite um Id baseado no que foi exibido para criar uma sala: ");
    scanf("%d", &id);

    for (int i = 0; i < *numSalas; i++)
    {
        if ((*salas)[i].id == id)
        {
            printf("Este ID já está em uso. Por favor, escolha outro.\n");
            return;
        }
    }

    newSala->id = id;

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
    scanf("%d", &idSala);

    if (idSala > 0 && idSala <= numSalas)
    {
        printf("ID: %d, Nome: %s, Descrição: %s, Lotação Máxima: %d\n", salas[idSala - 1].id, salas[idSala - 1].nome, salas[idSala - 1].descricao, salas[idSala - 1].lotacaoMaxima);
    }
    else
    {
        printf("ID da sala inválido.\n");
        return;
    }

    char diaReservado[11];
    printf("Insira a data que gostaria de reservar(no seguinte formato: DD-MM-YYYY): ");
    scanf("%s", diaReservado);

    do {
        printf("Insira o número de participantes: ");
        scanf("%d", &quantidadePessoas);

        if (quantidadePessoas > salas[idSala-1].lotacaoMaxima) {
            printf("O número de participantes excede a lotação máxima da sala %s. A lotação máxima é de %d pessoas.\n", salas[idSala-1].nome, salas[idSala-1].lotacaoMaxima);
        }
    } while (quantidadePessoas > salas[idSala-1].lotacaoMaxima);

    char convertedDate[11];
    snprintf(convertedDate, sizeof(convertedDate), "%s-%s-%s", &diaReservado[6], &diaReservado[3], &diaReservado[0]);
    diaReservado[10] = '\0';

    if (verificaDisponibilidade(*reservas, *numReservas, idSala, convertedDate))
    {
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
        fprintf(file, "ID da Sala: %d, Data Reservada: %s, Número de Participantes: %d\n", idSala, convertedDate, quantidadePessoas);
        fclose(file);
    }
    else
    {
        printf("A Sala não está disponível no dia solicitado.\n");
    }
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
