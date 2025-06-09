#include "cabecalho.h"

void ler_dados(const char* arq) {
    FILE* f = fopen(arq, "r");

    fscanf(f, "%d %d", &num_loc, &num_veic);
    for (int i = 0; i < num_loc + 1; i++) {
        for (int j =  0; j < num_loc + 1; j++) {
            fscanf(f, "%d", &mat_dist[i][j]);
        }
    }

    for (int i = 0; i < num_loc; i++) {
        fscanf(f, "%d", &vet_dem[i]);
    }

    for (int i = 0; i < num_veic; i++) {
        fscanf(f, "%d", &vet_cap_veic[i]);
    }
}

void escrever_dados(const char* arq) {
    FILE* f;

    if (!strcmp(arq, " ")) 
        f = stdout;
    else
        f = fopen(arq, "w");
        
    fprintf(f, "%d %d\n", num_loc, num_veic);
    
    for (int i = 0; i < num_loc + 1; i++) {
        for (int j =  0; j < num_loc + 1; j++) {
            fprintf(f, "%d ", mat_dist[i][j]);
        }
        fprintf(f, "\n");
    }

    for (int i = 0; i < num_loc; i++) {
        fprintf(f, "%d ", vet_dem[i]);
    }
    fprintf(f, "\n");
    for (int i = 0; i < num_veic; i++) {
        fprintf(f, "%d ", vet_cap_veic[i]);
    }
}

void criar_solucao (Solucao& sol) {
    for (int i = 0; i < num_veic; i++) {
        sol.vet_sol[i] = rand() % num_loc;
        printf("%d ", sol.vet_sol[i]);
    }


}

void calc_fo (Solucao& sol) {
    
}

int main () {
    Solucao* sol;
    srand(time(0));
    ler_dados("roteamento_veiculos.txt");
    escrever_dados("escrever.txt");
    criar_solucao(*sol);
    return 0;
} 