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

    // Initialize rooms
    inicializarSalas(&salas, &numSalas);
    
    // Read reservations from file
    lerReservasDoArquivo(&reservas, &numReservas); 

    do {
        printf("\nMenu Principal\n");
        printf("1 - Criar Sala\n");
        printf("2 - Reservar Sala\n");
        printf("3 - Listar Salas\n");
        printf("4 - Listar Todas Reservas\n");
        printf("5 - Listar Reservas de uma Sala\n");
        printf("6 - Cancelar Reserva\n");
        printf("0 - Encerrar Programa\n");
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
            listarTodasSalas(salas, numSalas, reservas, numReservas); 
            break;
        case 4:
            listarTodasReservas(reservas, numReservas, salas, numSalas);
            break;
        case 5:
            listarReservasDeUmaSala(reservas, numReservas, salas, numSalas);
            break;
        case 6:
            cancelarReserva(&reservas, &numReservas, salas, numSalas);
            break;
        case 0:
            encerrarPrograma(salas, reservas, numReservas);
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0); 

    free(salas);
    free(reservas);

    return 0;
}
