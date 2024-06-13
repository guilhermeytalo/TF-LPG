#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

void criarSala(Sala **salas, int *numSalas) {
    // Allocate memory for a new Sala
    *salas = realloc(*salas, (*numSalas + 1) * sizeof(Sala));
    
    // Initialize the new Sala
    Sala *newSala = &(*salas)[*numSalas];
    newSala->id = *numSalas;
    // TODO: Initialize other fields of newSala

    // Increment the number of Salas
    (*numSalas)++;

    // Write the new Sala to agendar_sala.txt
    FILE *file = fopen("agendar_sala.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d,%s,%s,%d,%d\n", newSala->id, newSala->nome, newSala->descricao, newSala->lotacaoMaxima, newSala->disponivel);
        fclose(file);
    }
}

void reservarSala(Sala *salas, int numSalas, Reserva **reservas, int *numReservas) {
    // TODO: Implement the logic to reserve a Sala
}

bool verificaDisponibilidade(Reserva *reservas, int numReservas, int idSala, const char *diaReservado) {
    // TODO: Implement the logic to verify the availability of a Sala
    return true;
}
