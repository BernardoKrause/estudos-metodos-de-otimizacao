#ifndef CABECALHO_H
#define CABELHO_H

#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ctime>

#define MAX_VEIC 50
#define MAX_LOC 100

int num_loc;
int num_veic;
int mat_dist[MAX_VEIC][MAX_VEIC];
int vet_dem[MAX_LOC];
int vet_cap_veic[MAX_VEIC];
int vet_pes_veic[MAX_VEIC];

typedef struct tSolucao {
    int vet_sol[MAX_VEIC];
    int fo;
} Solucao;

void ler_dados(const char* arq);
void escrever_dados(const char* arq);
void criar_solucao(Solucao& sol);
void calc_fo(Solucao& sol);

#endif