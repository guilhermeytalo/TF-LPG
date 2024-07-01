#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

void cancelarReserva(Reserva **reservas, int *numReservas, Sala *salas, int numSalas)
{
    int idReserva;
    printf("Insira o ID da reserva a ser cancelada: ");
    scanf("%d", &idReserva);

    if (idReserva <= 0 || idReserva > *numReservas)
    {
        printf("ID de reserva inválido.\n");
        return;
    }

    idReserva--;

    memmove(&(*reservas)[idReserva], &(*reservas)[idReserva + 1],
            (*numReservas - idReserva - 1) * sizeof(Reserva));

    *reservas = realloc(*reservas, (*numReservas - 1) * sizeof(Reserva));
    if (*reservas == NULL && *numReservas > 1)
    {
        perror("Erro ao redimensionar o array de reservas");
        return;
    }

    (*numReservas)--;

    FILE *file = fopen("reservas.txt", "w");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo reservas.txt");
        return;
    }

    for (int i = 0; i < *numReservas; i++)
    {
        fprintf(file, "ID da Sala: %d, Data Reservada: %s, Número de Participantes: %d\n",
                (*reservas)[i].idSala,
                (*reservas)[i].diaReservado,
                (*reservas)[i].quantidadePessoas);
    }
    fclose(file);

    printf("Reserva cancelada com sucesso.\n");
}
