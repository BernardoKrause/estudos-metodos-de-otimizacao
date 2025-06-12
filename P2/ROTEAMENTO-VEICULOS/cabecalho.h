#ifndef PROVA1_H_INCLUDED
#define PROVA1_H_INCLUDED

#define MAX_CLI 501
#define MAX_VEI 100

typedef struct tSolucao {
    int mat_sol[MAX_VEI][MAX_CLI]; // linha é o veículo e coluna é o cliente que aquele veículo vai atender (cliente = demanda)
    int vet_qtd_cli_vei[MAX_VEI]; // será a quantidade que cada veiculo (indice) atenderá
    // int vet_sol[MAX_CLI+MAX_VEI+1]; // vetor que representa a rota completa, incluindo todos os veículos e clientes. Os veículos podem ser separados por um identificador (ex: 0 para o depósito).

    int vet_pes_vei[MAX_VEI]; // vetor que armazena a carga total (soma das demandas) transportada por cada veículo (índice).
    double fo;
} Solucao;

int num_cli, num_vei;
int vet_dem_cli[MAX_CLI];
int vet_cap_vei[MAX_VEI];
double mat_custo[MAX_CLI][MAX_CLI];

void criar_solucao_aleatoria(Solucao& sol);
// void calcular_fo2(Solucao& s);
void calcular_fo(Solucao& sol);
void ler_dados(const char* arq);


#endif // PROVA1_H_INCLUDED
