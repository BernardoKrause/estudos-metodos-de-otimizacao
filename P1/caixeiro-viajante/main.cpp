#include "cabecalho.h"

void ler_dados (const char* arq) {
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d", &num_cidades);
    printf("%d\n",num_cidades);
    for (int i = 0; i < num_cidades; i++) {
        for (int j = 0; j < num_cidades; j++) {
            fscanf(f, "%d", &mat_dist_cidades[i][j]);
            printf("%d ", mat_dist_cidades[i][j]);
        }
        printf("\n");
    }
    fclose(f);
}

void escrever_dados (const char* arq) {
    FILE* f;

    if (!strcmp(arq, " ")) 
        f = stdout;
    else 
        f = fopen(arq, "w");
    
    fprintf(f, "%d \n", num_cidades);
    for (int i = 0; i < num_cidades; i++) {
        for (int j = 0; j < num_cidades; j++) {
            fprintf(f, "%d ", mat_dist_cidades[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}   

void criar_solucao(Solucao& sol) {
    for (int i = 0; i < num_cidades; i++) {
        sol.vet_sol[i] = rand() % num_cidades;
    }
}

void calc_fo(Solucao& sol) {
    double soma = 0;
    double cidades_percorridas[num_cidades];

    memset(cidades_percorridas, 0, sizeof(cidades_percorridas));
    for (int i = 0; i < num_cidades; i++) {
        cidades_percorridas[sol.vet_sol[i]]++; 
    }

    for (int i = 0; i < num_cidades - 1; i++) {
        if (cidades_percorridas[i] > 1) 
            soma += mat_dist_cidades[sol.vet_sol[i]][sol.vet_sol[i+1]] * ALPHA;
        else 
            soma += mat_dist_cidades[sol.vet_sol[i]][sol.vet_sol[i+1]];
    }
}

int main () {

    ler_dados("caixeiro_viajante.txt");
    escrever_dados("escrever.txt");

    return 0;
}