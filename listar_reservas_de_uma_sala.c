#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

void listarReservasDeUmaSala(Reserva *reservas, int numReservas, Sala *salas, int numSalas)
{
    int idSala;
    printf("Insira o ID da sala para listar suas reservas: ");
    scanf("%d", &idSala);

    char *nomeSala = NULL;
    for (int i = 0; i < numSalas; i++)
    {
        if (salas[i].id == idSala)
        {
            nomeSala = salas[i].nome;
            break;
        }
    }

    if (nomeSala == NULL)
    {
        printf("Sala com ID %d não encontrada.\n", idSala);
        return;
    }

    printf("Listagem de reservas para a sala %s (ID: %d):\n", nomeSala, idSala);
    printf("ID da Reserva | Dia Reservado | Número de Participantes\n");

    FILE *file = fopen("listar_reservas_de_uma_sala.txt", "w");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo listar_reservas_de_uma_sala.txt");
        return;
    }

    fprintf(file, "Listagem de reservas para a sala %s (ID: %d):\n", nomeSala, idSala);
    fprintf(file, "ID da Reserva | Dia Reservado | Número de Participantes\n");

    bool found = false;
    for (int i = 0; i < numReservas; i++)
    {
        if (reservas[i].idSala == idSala)
        {
            printf("%13d | %12s | %20d\n", i + 1, reservas[i].diaReservado, reservas[i].quantidadePessoas);
            fprintf(file, "%13d | %12s | %20d\n", i + 1, reservas[i].diaReservado, reservas[i].quantidadePessoas);
            found = true;
        }
    }

    if (!found)
    {
        printf("Nenhuma reserva encontrada para a sala %s (ID: %d).\n", nomeSala, idSala);
        fprintf(file, "Nenhuma reserva encontrada para a sala %s (ID: %d).\n", nomeSala, idSala);
    }

    fclose(file);
}