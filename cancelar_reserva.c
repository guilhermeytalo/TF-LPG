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

    // Adjust the ID to be zero-indexed for array manipulation
    idReserva -= 1;

    // Save the canceled reservation to the file
    FILE *file = fopen("cancelar_reserva.txt", "a");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo cancelar_reserva.txt");
        return;
    }

    fprintf(file, "ID da Sala: %d, Data Reservada: %s, Número de Participantes: %d\n",
            (*reservas)[idReserva].idSala,
            (*reservas)[idReserva].diaReservado,
            (*reservas)[idReserva].quantidadePessoas);
    fclose(file);

    // Shift reservations down to overwrite the canceled reservation
    for (int i = idReserva; i < (*numReservas) - 1; i++)
    {
        (*reservas)[i] = (*reservas)[i + 1];
    }

    // Resize the array to remove the last element
    *reservas = realloc(*reservas, (*numReservas - 1) * sizeof(Reserva));
    if (*reservas == NULL && *numReservas > 1)
    {
        perror("Erro ao redimensionar o array de reservas");
        return;
    }

    (*numReservas)--;
    printf("Reserva cancelada com sucesso.\n");
}
