#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

void criarSala(Sala **salas, int *numSalas) {
    
    *salas = realloc(*salas, (*numSalas + 1) * sizeof(Sala));
    
    Sala *newSala = &(*salas)[*numSalas];
    newSala->id = *numSalas;
    (*numSalas)++;

    FILE *file = fopen("agendar_sala.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d,%s,%s,%d,%d\n", newSala->id, newSala->nome, newSala->descricao, newSala->lotacaoMaxima, newSala->disponivel);
        fclose(file);
    }
}

void reservarSala(Sala *salas, int numSalas, Reserva **reservas, int *numReservas) {
    int idSala;
    printf("Insira o Id da sala que gostaria de reservar: ");
    scanf("%d", &idSala);

    char diaReservado[11];
    printf("Insira a data que gostaria de reservar(no seguinte formato: DD-MM-YYYY): ");
    scanf("%s", diaReservado);

    char convertedDate[11];
    snprintf(convertedDate, sizeof(convertedDate), "%s-%s-%s", &diaReservado[6], &diaReservado[3], &diaReservado[0]);
    diaReservado[10] = '\0';

    if (verificaDisponibilidade(*reservas, *numReservas, idSala, convertedDate)) {
        
        *reservas = realloc(*reservas, (*numReservas + 1) * sizeof(Reserva));
        
        Reserva *newReserva = &(*reservas)[*numReservas];
        newReserva->idSala = idSala;
        strcpy(newReserva->diaReservado, convertedDate);
        (*numReservas)++;
    } else {
        printf("A Sala não está disponível no dia solicitado.\n");
    }
}

bool verificaDisponibilidade(Reserva *reservas, int numReservas, int idSala, const char *diaReservado) {
    for (int i = 0; i < numReservas; i++) {
        if (reservas[i].idSala == idSala && strcmp(reservas[i].diaReservado, diaReservado) == 0) {
            
            return false;
        }
    }

    return true;
}
