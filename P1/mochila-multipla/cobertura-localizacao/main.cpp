#include "cabecalho.h"

void ler_dados (const char* arq) {
    FILE* f = fopen(arq, "r");

    fscanf(f, "%d %d", &num_dem, &num_loc);
    for (int i = 0; i < num_dem; i++) {
        for (int j = 0; j < num_loc; j++) {
            fscanf(f, "%d", &mat_cob[i][j]);
        }
    }

    for (int i = 0; i < num_loc; i ++) {
        fscanf(f, "%d", &vet_custos[i]);
    }

    fclose(f);
}

void escrever_dados (const char* arq) {
    FILE* f;

    if (!strcmp(arq, " ")) 
        f = stdout;
    else
        f = fopen(arq, "w");

    fprintf(f, "%d %d \n", num_dem, num_loc);
    for (int i = 0; i < num_dem; i++) {
        for (int j = 0; j < num_loc; j++) {
            fprintf(f, "%d ", mat_cob[i][j]);
        }
        fprintf(f,"\n");
    }

    for (int i = 0; i < num_loc; i ++) {
        fprintf(f, "%d ", vet_custos[i]);
    }

    fclose(f);
}

void criar_solucao(Solucao& sol) {
    for (int i = 0; i < num_dem; i++) {
        sol.vet_sol[i] = rand() % num_loc;
        printf("%d ", sol.vet_sol[i]);
    }
}

void calc_fo(Solucao& sol) {
    for (int i = 0; i < num_dem; i++) {
        soma += vet_custos[sol.vet_sol[i]];
    }

    for (int i = 0; i < num_dem; i++) {
        for (int j = 0; j < num_loc; j++) {
            
        }
    }
}

int main () {
    Solucao* sol;

    ler_dados("cobertura_localizacao.txt");
    escrever_dados("escrever.txt");

    criar_solucao(*sol);
    calc_fo(*sol);

    printf("\n");
    for (int i = 0; i < num_loc; i++) {
        printf("%d ", vet_custos[i]);
    }
    printf("\n%.2f", soma);
    
    return 0;
} 