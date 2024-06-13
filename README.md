# Trabalho Final (TF) - Linguagem de Programação (LPG0002)

Neste projeto final, você será responsável por desenvolver um sistema de agendamento de salas em C para a universidade.
O sistema deverá ser capaz de gerenciar informações sobre as salas disponíveis, suas características (como nome, lotação
e disponibilidade), as reservas feitas para cada sala em dias específicos e a possibilidade de agendar a sala em um
determinado dia.

## O menu principal da operação deve conter as seguintes opções:

- Listar salas: Essa opção permite ao usuário listar todas as salas disponíveis, exibindo suas informações como nome,
  lotação e disponibilidade.
- Listar todas as reservas: Essa opção exibe todas as reservas feitas para todas as salas, mostrando o ID da reserva, ID
  da sala, seu nome e o dia reservado.
- Listar reservas de uma sala: O usuário deve informar o ID de uma sala e visualizar todas as reservas feitas para essa
  sala em particular.
- Agendar sala: O usuário agenda uma sala para um dia específico, fornecendo informações como o ID da sala, o dia
  desejado e quantidade de pessoas.
- Cancelar reserva: O usuário deve informar o ID da reserva a ser cancelada.
- Encerrar o programa: Opção para encerrar o programa e sair do sistema de agendamento de salas, aqui deve ser printado
  todas as reservas antes de sair.

## Pontos de atenção:

- As salas possuem capacidade máxima, se o usuário precisar de uma sala com menor capacidade do que o número de
  integrantes, trate o problema.
- Não poderão ser realizadas duas reservas para a mesma sala no mesmo dia/horário.
- O arquivo final deverá ser atualizado contendo todas as reservas, e deverá ser removido do arquivo todas as reservas
  canceladas. (faça o registro/controle de cancelamentos, em um arquivo à parte)
- Ações erradas devem ser tratadas com mensagens adequadas, o usuário não pode ter liberdade de quebrar o programa com
  ações que poderiam ser previstas (ex: o usuário tentar fazer uma reserva para um dia onde a sala já está reservada).

**Você deverá considerar que os recursos são FINITOS. Ou seja, podem existir casos onde alguns dos recursos disponíveis,
para as salas, são FINITOS e INSUFICIENTES! Isto poderá influenciar nas decisões quanto a reserva de salas.**

## Arquivo de entrada (somente leitura):

ID, Nome, Descrição, Lotação Máxima
1, Sala A. Sala de Aula com Projetor, 30
2, Sala B. Laboratório de Informática, 20
3, Sala C, Sala de Reuniões, 15
4, Sala D, Auditório, 100

5. Sala E, Sala de Estudos, 10
   6, Sala F, Sala de Estudos, 10
7. Sala G, Sala de Estudos, 10
8. Sala H, Sala de Estudos, 10

**Você deverá gerar um novo arquivo final para armazenar as informações das reservas com as seguintes informações para
cada linha:
ID da sala, dia reservado, número de participantes**

## Exemplo de menu que deverá ficar em loop durante a execução do programa:

Menu Principal

1 - Listar Salas

2 - Listar Reservas

3 - Reservas de uma Sala

4 - Agendar Sala

5 - Cancelar Reserva

6 - Encerrar Programa

**Importante: Todo o trabalho deverá fazer uso de alocação dinâmica. Visando otimizar o uso de memória do sistema.**

## Exemplo de estruturas que você poderá desenvolver:

```c
typedef struct {
    int id;
    char descricao[100];
    int lotacaoMaxima;
} Sala;

typedef struct {
    int idSala;
    char nomeSala[90];
    char diaReservado[11]; // Formato "dd/mm/aaaa"
    int quantidadePessoas;
} Reserva;

#include <stdio.h>

int main(){
    int opcao;
    
    do{
        printf("1 - Listar Salas\n");
        printf("2 - Reservar Sala\n");
        printf("3 - Cancelar Reserva\n");
        printf("4 - Sair\n");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                // listar salas
                break;
            case 2:
                // reservar sala
                break;
            case 3:
                // cancelar reserva
                break;
            case 4:
                // sair do programa
                break;
            default:
                printf("Opção Inválida!\n");
        }
    }while(opcao != 4);
    
    return 0;
}
```

## Sistema de agendamento de salas da UDESC

![image](https://github.com/guilhermeytalo/TF-LPG/assets/25457238/4b0a6a99-e556-4d46-a595-5c1f3a5a6b3c)

