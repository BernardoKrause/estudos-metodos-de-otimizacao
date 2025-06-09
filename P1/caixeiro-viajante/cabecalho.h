#ifndef CABECALHO_H
#define CABECALHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ALPHA 1.25
#define MAX_CIDADES 100

int num_cidades;
int mat_dist_cidades[MAX_CIDADES][MAX_CIDADES];

typedef struct tSolucao {
    int vet_sol[MAX_CIDADES];
    double fo;
} Solucao;

void ler_dados(const char* arq);
void escrever_dados(const char* arq);
void criar_solucao(Solucao& sol);
void calc_fo(Solucao& sol);

#endif