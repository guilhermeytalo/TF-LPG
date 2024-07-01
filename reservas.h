#ifndef RESERVAS_H
#define RESERVAS_H

#include <stdbool.h>

#define MAX_NOME 90
#define MAX_DESCRICAO 100
#define MAX_SALAS 3
#define MAX_RESERVAS 3

typedef struct {
    int id;
    char nome[MAX_NOME];
    char descricao[MAX_DESCRICAO];
    int lotacaoMaxima;
    bool disponivel;
} Sala;

typedef struct {
    int idSala;
    char diaReservado[11];
    int quantidadePessoas;
} Reserva;

void criarSala(Sala **salas, int *numSalas);
void reservarSala(Sala *salas, int numSalas, Reserva **reservas, int *numReservas);
bool verificaDisponibilidade(Reserva *reservas, int numReservas, int idSala, const char *diaReservado);
void encerrarPrograma(Sala *salas, Reserva *reservas, int numReservas);
void inicializarSalas(Sala **salas, int *numSalas);
void listarTodasSalas(Sala *salas, int numSalas, Reserva *reservas, int numReservas);
void lerReservasDoArquivo(Reserva **reservas, int *numReservas);
void listarReservasDeUmaSala(Reserva *reservas, int numReservas, Sala *salas, int numSalas);
void cancelarReserva(Reserva **reservas, int *numReservas, Sala *salas, int numSalas);
void listarTodasReservas(Reserva *reservas, int numReservas, Sala *salas, int numSalas);
#endif // RESERVAS_H
