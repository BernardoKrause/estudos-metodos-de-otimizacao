#ifndef CABECALHO_H
#define CABECALHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>

#define MAX_ITENS 20
#define MAX_MOCHILAS 10
#define ALPHA 0.5

int num_mochilas;
int num_items;
int vet_pes_items[MAX_ITENS];
int vet_val_items[MAX_ITENS];
int vet_cap_moc[MAX_MOCHILAS];
int vet_item_rep[MAX_ITENS];
int vet_pes_moc[MAX_MOCHILAS];

typedef struct tSolucao {
    int vet_sol[MAX_ITENS];
    int fo;
} Solucao;

void ler_dados(const char* arq);
void escrever_dados(const char* arq);
void criar_solucao(Solucao& sol);
void calc_fo(Solucao& sol);

#endif