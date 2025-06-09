#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED

#define ZERO 0.00001
#define MAX_OBJ 500
#define MAX_MOC 50

typedef struct tSolucao
{
    int vet_sol[MAX_OBJ];
    int vet_pes_moc[MAX_MOC];
    int fo;
} Solucao;

typedef struct tSolucaoBIN
{
    int mat_sol[MAX_MOC][MAX_OBJ];
    int vet_pes_moc[MAX_MOC];
    int vet_obj_dup[MAX_OBJ];
    int fo;
}SolucaoBIN;

int num_obj;
int num_moc;
int vet_val_obj[MAX_OBJ];
int vet_pes_obj[MAX_OBJ];
int vet_cap_moc[MAX_MOC];

void ler_dados(char* arq);
void escrever_dados(char* arq);


#define TAMANHO 5
#define REPETICOES 10000

void alocacao();




#endif // CABECALHO_H_INCLUDED
