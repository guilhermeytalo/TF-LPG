#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

void listarTodasReservas(Reserva *reservas, int numReservas, Sala *salas, int numSalas)
{
    printf("Listagem de todas as reservas:\n");
    printf("ID da Reserva | ID da Sala | Nome da Sala | Dia Reservado | Participantes\n");

    FILE *file = fopen("listar_todas_reservas.txt", "w");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo listar_todas_reservas.txt");
        return;
    }

    fprintf(file, "Listagem de todas as reservas:\n");
    fprintf(file, "ID da Reserva | ID da Sala | Nome da Sala           | Dia Reservado | Participantes\n");

    for (int i = 0; i < numReservas; i++)
    {
        char *nomeSala = NULL;
        for (int j = 0; j < numSalas; j++)
        {
            if (salas[j].id == reservas[i].idSala)
            {
                nomeSala = salas[j].nome;
                break;
            }
        }

        if (nomeSala != NULL)
        {
            printf("%13d | %10d | %-20s | %12s | %d\n", i + 1, reservas[i].idSala, nomeSala, reservas[i].diaReservado, reservas[i].quantidadePessoas);
            fprintf(file, "%13d | %10d | %-20s | %12s | %d\n", i + 1, reservas[i].idSala, nomeSala, reservas[i].diaReservado, reservas[i].quantidadePessoas);
        }
    }

    fclose(file);
}