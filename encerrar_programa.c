#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

void encerrarPrograma(Sala *salas, Reserva *reservas, int numReservas) {
    free(salas);
    free(reservas);
    printf("Encerrando o programa...\n");
}
