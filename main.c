#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

int main() {
    Sala *salas = NULL;
    int numSalas = 0;
    Reserva *reservas = NULL;
    int numReservas = 0;
    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1 - Criar Sala\n");
        printf("2 - Reservar Sala\n");
        printf("3 - Encerrar Programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            criarSala(&salas, &numSalas);
            break;
        case 2:
            reservarSala(salas, numSalas, &reservas, &numReservas);
            break;
        case 3:
            encerrarPrograma(salas, reservas, numReservas);
            return 0;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 3);

    return 0;
}
