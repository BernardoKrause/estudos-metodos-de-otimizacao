#ifndef CABECALHO_H
#define CABECALHO_H

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

#define MAX_TAREFAS 500
#define MAX_TRIPULACOES 400

#define MAX(X,Y)((X > Y) ? (X) : (Y))
#define MIN(X,Y)((X < Y) ? (X) : (Y)) 

// penalização
const int PESO_EXTRA = 1;
const int PESO_OCIOSO = 1;
const int PESO_SOBREPOSICAO = 100;
const int PESO_EXCEDIDO = 100;

// valores referentes a tempo estão expressos em minutos

int num_tarefas = 0;
int num_trip = 0;
double contador_temp = 0;
int temp_normal_trab; // tempo de duração de um turno sem horas extras
int temp_max_trab; // tempo limite de duração de um turno incluido horas extras
int vet_h_ini_tarefa[MAX_TAREFAS];
int vet_h_term_tarefa[MAX_TAREFAS];

typedef struct tSolucao {
    int mat_sol[MAX_TRIPULACOES][MAX_TAREFAS]; // linha representa a tripulação e a coluna as tarefas 
    int vet_num_tarefas_trip[MAX_TRIPULACOES];
    
    int h_extra; // horas extras
    int t_ocioso; // tempo ocioso
    int t_sobre; // tempo de sobreposição
    int t_exce; // tsempo excessivo
    int fo;
} Solucao;

Solucao sol_vizinha;

void ler_dados(char* arq);
void criar_solucao(Solucao& sol);
void calcular_fo(Solucao& sol);
void clonar_solucao(Solucao& sol, Solucao& clone);
void gerar_vizinho(Solucao& sol);
void heu_BL_random(Solucao& sol, const int& iter);

#endif