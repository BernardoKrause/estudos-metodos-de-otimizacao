#ifndef NOVO_H_INCLUDED
#define NOVO_H_INCLUDED

#include "cabecalho.h"

typedef struct tProblema
{
    int num_obj;
    int nm_moc;
    int vet_val_obj[MAX_OBJ];
    int vet_pes_obj[MAX_OBJ];
    int vet_cap_moc[MAX_MOC];
} Problema;

extern Problema PRB;

#endif 