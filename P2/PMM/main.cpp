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

void criar_solucao_aleatoria(Solucao& sol) {
    for (int j = 0; j < num_items; j++){
        sol.vet_sol[j] = rand() % (num_mochilas + 1) - 1;
    }
}

void criar_solucao_gulosa(Solucao& sol) {
    memset(sol.vet_pes_moc, 0, sizeof(sol.vet_sol));
    memset(sol.vet_sol, -1, sizeof(sol.vet_sol));

    for (int i = 0; i < num_items; i++) {
        for (int j = 0; j < num_mochilas; j++) {
            if ((sol.vet_pes_moc[j] + vet_pes_items[i]) < vet_cap_moc[j]) {
                sol.vet_sol[i] = j;
                sol.vet_pes_moc[j] += vet_pes_items[i];
            }
        }
    }

}

void calc_fo(Solucao& sol) {
    sol.fo = 0;
    memset(&sol.vet_pes_moc, 0, sizeof(sol.vet_pes_moc));

    for (int i = 0; i < num_items; i++) {
        if (sol.vet_sol[i] != -1) {
            sol.fo += vet_val_items[i];
            sol.vet_pes_moc[sol.vet_sol[i]] += vet_pes_items[i];
        }
    }

    for (int i = 0; i < num_mochilas; i++) {
        sol.fo -= ALPHA * MAX(0, (sol.vet_pes_moc[i] - vet_cap_moc[i]));
    }
}

void clonar_sol(Solucao& sol, Solucao& clone) {
    memcpy(&clone, &sol, sizeof(Solucao));
}

void gerar_vizinho(Solucao& sol) {
    int item, mochila;
    item = rand() % num_items;
    printf("item: %d\n", item);
    mochila = sol.vet_sol[item];
    printf("mochila: %d\n", mochila);

    do
    {
        sol.vet_sol[item] = rand() % (num_mochilas + 1) - 1;
        printf("sol.vet_sol[%d]: %d\n", item, sol.vet_sol[item]);
    } while (sol.vet_sol[item] == mochila);
    
    calc_fo(sol);
}

void escrever_solucao(const Solucao& s)
{
    printf("\n\nFO: %.2f\n", s.fo);
    printf("Peso mochilas: ");
    for (int i = 0; i < num_mochilas; i++)
        printf("%d ", s.vet_pes_moc[i]);
    printf("\nVetor solucao: ");
    for (int j = 0; j < num_items; j++)
        printf("%d ", s.vet_sol[j]);
    printf("\n");
}

int main () {
    Solucao sol, clone;
    // Solucao sol;

    srand(time(NULL));

    ler_dados("pmm1.txt");
    // escrever_dados("escrever.txt");

    // criar_solucao_aleatoria(sol);
    criar_solucao_gulosa(sol);
    calc_fo(sol);

    for (int i = 0; i < 10; i++) {
        clonar_sol(sol, clone);
        gerar_vizinho(clone);

        if (clone.fo >= sol.fo) {
           clonar_sol(clone, sol); 
           printf("teste");
        }
    }
        
    escrever_solucao(sol);

    return 0;
}