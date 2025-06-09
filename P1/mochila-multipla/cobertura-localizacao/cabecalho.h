#ifndef CABECALHO_H
#define CABELHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DEM 100
#define MAX_LOC 100

int num_dem; // pode se entender como numero de clientes
int num_loc; // localizacoes possiveis
int mat_cob[MAX_DEM][MAX_LOC];
int vet_custos[MAX_DEM];
int vet_cob[MAX_DEM];
double soma = 0;
// penalização se dá quando uma das demandas não é atendida (não há penalização e sim rejeição)

typedef struct tSolucao {
    int vet_sol[MAX_LOC];
    double fo;
} Solucao;

void ler_dados (const char* arq);
void escrever_dados(const char* arq);
void criar_solucao(Solucao& sol);
void calc_fo(Solucao& sol);

#endif