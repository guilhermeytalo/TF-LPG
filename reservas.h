#define MAX_NOME 90
#define MAX_DESCRICAO 100
#define MAX_SALAS 3 // Número máximo de salas
#define MAX_RESERVAS 3 // Número máximo de reservas

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

// Funções para manipulação de salas
void criarSala(Sala **salas, int *numSalas);
void listarSalas(Sala *salas, int numSalas);
void reservarSala(Sala *salas, int numSalas, Reserva **reservas, int *numReservas);
bool verificaDisponibilidade(Reserva *reservas, int numReservas, int idSala, const char *diaReservado);

// Funções para manipulação de reservas
void cancelarReserva(Reserva **reservas, int *numReservas);
void listarReservas(Reserva *reservas, int numReservas);

// Funções auxiliares
void carregarSalas(Sala **salas, int *numSalas);
void carregarReservas(Reserva **reservas, int *numReservas);
void salvarReservas(Reserva *reservas, int numReservas);
void encerrarPrograma(Sala *salas, Reserva *reservas);
