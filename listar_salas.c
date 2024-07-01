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

void listarTodasSalas(Sala *salas, int numSalas, Reserva *reservas, int numReservas)
{
    // Reset all rooms to available
    for (int i = 0; i < numSalas; i++)
    {
        salas[i].disponivel = true;
    }

    // Mark rooms as unavailable based on reservations
    for (int i = 0; i < numReservas; i++)
    {
        for (int j = 0; j < numSalas; j++)
        {
            if (reservas[i].idSala == salas[j].id)
            {
                salas[j].disponivel = false;
                break; 
            }
        }
    }

    printf("Listagem de todas as salas cadastradas:\n");
    for (int i = 0; i < numSalas; i++)
    {
        printf("ID: %d, Nome: %s, Descrição: %s, Lotação Máxima: %d, Disponível: %s\n",
               salas[i].id, salas[i].nome, salas[i].descricao, salas[i].lotacaoMaxima,
               salas[i].disponivel ? "Sim" : "Não");
    }
}

void lerReservasDoArquivo(Reserva **reservas, int *numReservas)
{
    FILE *file = fopen("reservas.txt", "r");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo de reservas");
        return;
    }

    char linha[256];
    int idSala;
    char diaReservado[11];
    int quantidadePessoas;
    *numReservas = 0;

    while (fgets(linha, sizeof(linha), file))
    {
        if (sscanf(linha, "ID da Sala: %d, Data Reservada: %10s, Número de Participantes: %d", &idSala, diaReservado, &quantidadePessoas) == 3)
        {
            *reservas = realloc(*reservas, (*numReservas + 1) * sizeof(Reserva));
            if (*reservas == NULL)
            {
                perror("Erro ao redimensionar o array de reservas");
                fclose(file);
                return;
            }

            (*reservas)[*numReservas].idSala = idSala;
            strcpy((*reservas)[*numReservas].diaReservado, diaReservado);
            (*reservas)[*numReservas].quantidadePessoas = quantidadePessoas;
            (*numReservas)++;
        }
    }

    fclose(file);
}
