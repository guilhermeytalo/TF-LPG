#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"
#include "agenda_sala.c"
#include "cancelar_reserva.c"
#include "encerrar_programa.c"

int main() {
    Sala *salas = NULL;
    int numSalas = 0;
    Reserva *reservas = NULL;
    int numReservas = 0;
    int opcao;

    carregarSalas(&salas, &numSalas);
    carregarReservas(&reservas, &numReservas);

    do {
        printf("\nMenu Principal\n");
        printf("1 - Listar Salas\n");
        printf("2 - Listar Reservas\n");
        printf("3 - Reservar Sala\n");
        printf("4 - Cancelar Reserva\n");
        printf("5 - Criar Sala\n"); 
        printf("6 - Encerrar Programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            listarSalas(salas, numSalas);
            break;
        case 2:
            listarReservas(reservas, numReservas);
            break;
        case 3:
            reservarSala(salas, numSalas, &reservas, &numReservas);
            break;
        case 4:
            cancelarReserva(&reservas, &numReservas);
            break;
        case 5:
            criarSala(&salas, &numSalas);
            break;
        case 6:
            encerrarPrograma(salas, reservas);
            return 0;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    return 0;
}
