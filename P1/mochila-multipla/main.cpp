#include "cabecalho.h"

void ler_dados(const char* arq) {
    FILE* f = fopen(arq, "r");
    
    fscanf(f, "%d %d", &num_items, &num_mochilas);
    for (int i = 0; i < num_items; i++) {
        fscanf(f, "%d", &vet_pes_items[i]);
    }
    for (int i = 0; i < num_items; i++) {
        fscanf(f, "%d", &vet_val_items[i]);
    }
    for (int i = 0; i < num_mochilas; i++) {
        fscanf(f, "%d", &vet_cap_moc[i]);
    }

    fclose(f);
}

void escrever_dados(const char* arq) {
    FILE* f;
    if (!strcmp(arq, "")) {
        f = stdout;
    } else {
        f = fopen(arq, "w");
    }

    fprintf(f, "%d %d\n", num_items, num_mochilas);
    for (int i = 0; i < num_items; i++) {
        fprintf(f, "%d ", vet_pes_items[i]);
    }
    fprintf(f, "\n");
    for (int i = 0; i < num_items; i++) {
        fprintf(f, "%d ", vet_val_items[i]);
    }
    fprintf(f, "\n");
    for (int i = 0; i < num_mochilas; i++) {
        fprintf(f, "%d ", vet_cap_moc[i]);
    }
}

void criar_solucao(Solucao& sol) {
    memset(vet_pes_moc, 0, sizeof(vet_pes_moc));

    memset(sol.vet_sol, -1, sizeof(sol.vet_sol));
    for (int i = 0; i < num_items; i++) {
        sol.vet_sol[i] = rand() % num_mochilas;  
        vet_pes_moc[sol.vet_sol[i]] += vet_pes_items[i];
    }
}

void calc_fo(Solucao& sol) {
    for (int i = 0; i < num_items; i++) {
        if (sol.vet_sol[i] != -1) {
            sol.fo += vet_val_items[i];
        }
    }
    if (vet_pes_moc > vet_cap_moc) {
        sol.fo *= ALPHA;
    }
}

int main () {
    srand(time(0));
    Solucao* sol;
    ler_dados("mochila_multipla.txt");
    escrever_dados("escrever.txt");
    criar_solucao(*sol);
    calc_fo(*sol);

    printf("%d", sol->fo);
    return 0;
} 