#ifndef CABECALHO_H
#define CABECALHO_H

#include <iostream>
#include <string.h>
#include <iostream>

#define ZERO 0.001 // posso usar esse pra comparar (nunca usar = e sim <= ou >=, pq patricamente nunca vai ser exatamente 0.001)
#define MAX_OBJ 500
#define MAX_MOC 50

// vantajoso declarar variáveis globais pq ai n precisa de passar por parametro

typedef struct tSolucao
{
    int vet_sol[MAX_OBJ]; // Inicializo com -1 todos os obj e atribuo 
    int vet_pes_moc[MAX_MOC];
    int fo; // funcao objetivo (defino o tipo a depender do contexto do problema)
} Solucao;

typedef struct tSolucaoBIN
{
    int mat_sol[MAX_MOC][MAX_OBJ];
    int vet_pes_moc[MAX_MOC];
    int vet_obj_dup[MAX_OBJ];
    int fo;
} SolucaBIN;

int num_obj;
int num_moc;
int vet_val_obj[MAX_OBJ];
int vet_pes_obj[MAX_OBJ];
int vet_cap_moc[MAX_MOC];

#endif 