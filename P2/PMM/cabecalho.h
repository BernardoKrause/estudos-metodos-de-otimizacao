#ifndef CABECALHO_H
#define CABECALHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <math.h>

#define MAX_ITENS 500
#define MAX_MOCHILAS 2000
#define ALPHA 100

#define MAX(X,Y)((X > Y) ? (X) : (Y))
#define MIN(X,Y)((X < Y) ? (X) : (Y)) 

int num_mochilas;
int num_items;
int vet_pes_items[MAX_ITENS];
int vet_val_items[MAX_ITENS];
int vet_cap_moc[MAX_MOCHILAS];
int vet_item_rep[MAX_ITENS];

typedef struct tSolucao {
    int vet_sol[MAX_ITENS];
    int vet_pes_moc[MAX_MOCHILAS];
    double fo;
} Solucao;

void ler_dados(const char* arq);
void escrever_dados(const char* arq);
void criar_solucao_aleatoria(Solucao& sol);
void criar_solucao_gulosa(Solucao& sol);
void criar_solucao_aleatoria_gulosa(Solucao& sol);
void calc_fo(Solucao& sol);
void clonar_sol(Solucao& sol, Solucao& clone);
void gerar_vizinho(Solucao& sol);

#endif