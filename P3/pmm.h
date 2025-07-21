#ifndef PMM_H_INCLUDED
#define PMM_H_INCLUDED

#define MAX_OBJ 500
#define MAX_MOC 50

typedef struct tSolucao
{
    int vet_sol[MAX_OBJ];
    int vet_pes_moc[MAX_MOC];
    int fo;
}Solucao;

int num_obj;
int num_moc;
int vet_val_obj[MAX_OBJ];
int vet_pes_obj[MAX_OBJ];
int vet_cap_moc[MAX_MOC];

int vet_ind_ord[MAX_OBJ];

void heu_BL_rand(Solucao& s, const int& iter);
void heu_BL_MM(Solucao& s);
void heu_BL_PM(Solucao& s);
void heu_BL_PM2(Solucao& s);

void heu_cons_ale(Solucao& s);
void heu_cons_gul(Solucao& s);
void heu_cons_ale_gul(Solucao& s, const double& percentual);

void ordenar_objetos();

void ler_dados(char* arq);
void escrever_dados(char* arq);
void gerar_vizinha(Solucao& s);
void calcular_fo_solucao(Solucao& s);
void escrever_solucao(const Solucao& s);

#endif // PMM_H_INCLUDED
