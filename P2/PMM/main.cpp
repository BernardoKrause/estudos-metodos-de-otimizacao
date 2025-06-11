#include "cabecalho.h"

void ler_dados(const char* arq) {
    FILE* f = fopen(arq, "r");
    
    fscanf(f, "%d %d", &num_items, &num_mochilas);
    for (int i = 0; i < num_items; i++) {
        fscanf(f, "%d", &vet_val_items[i]);
    }
    for (int i = 0; i < num_items; i++) {
        fscanf(f, "%d", &vet_pes_items[i]);
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
    memset(sol.vet_pes_moc, 0, sizeof(sol.vet_pes_moc));
    memset(sol.vet_sol, -1, sizeof(sol.vet_sol));

    for (int i = 0; i < num_items; i++) {
        for (int j = 0; j < num_mochilas; j++) {
            if ((sol.vet_pes_moc[j] + vet_pes_items[i]) < vet_cap_moc[j]) {
                sol.vet_sol[i] = j;
                sol.vet_pes_moc[j] += vet_pes_items[i];
                break;
            }
        }
    }

}

void criar_solucao_aleatoria_gulosa(Solucao& sol) {
    int itens_comeco = ceil(num_items * 0.1);
    int vet_itens[itens_comeco];

    memset(sol.vet_pes_moc, 0, sizeof(sol.vet_pes_moc));
    memset(sol.vet_sol, -1, sizeof(sol.vet_sol));
    
    for (int i = 0; i < itens_comeco; i++) {
        vet_itens[i] = rand() % num_items;
    }

    for (int i = 0; i < itens_comeco; i++) {
        for (int j = 0; j < num_mochilas; j++) {
            if ((sol.vet_pes_moc[j] + vet_pes_items[vet_itens[i]]) < vet_cap_moc[j]) {
                sol.vet_sol[vet_itens[i]]  = j;
                sol.vet_pes_moc[j] += vet_pes_items[vet_itens[i]];
                break;
            }
        }
    }


}

void calc_fo(Solucao& sol) {
    sol.fo = 0;

    for (int i = 0; i < num_items; i++) {
        if (sol.vet_sol[i] != -1)
            sol.fo += vet_val_items[i];
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
    item = rand() % num_items; // vou pegar um item aleatório
    mochila = sol.vet_sol[item]; // pegar a mochila desse item

    do
    {
        sol.vet_sol[item] = (rand() % (num_mochilas + 1)) - 1; // pego uma mochila aleatoria e coloco esse item nela (-1,0 ou 1)
    } while (sol.vet_sol[item] == mochila && sol.vet_pes_moc[mochila] + sol.vet_sol[item] > vet_cap_moc[mochila]);

    if (mochila != -1) { // se o item tava em alguma mochila
        sol.vet_pes_moc[mochila] -= vet_pes_items[item]; // tira o peso do item da mochila atual
    }

    if (sol.vet_sol[item] != -1) {
        sol.vet_pes_moc[sol.vet_sol[item]] += vet_pes_items[item];
    }
    
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

    // srand(time(NULL));

    ler_dados("pmm3.txt");
    // escrever_dados("escrever.txt");

    // criar_solucao_aleatoria(sol);
    // criar_solucao_gulosa(sol);
    criar_solucao_aleatoria_gulosa(sol);
    calc_fo(sol); 

    // escrever_solucao(sol);

    for (int i = 0; i < 1000000; i++) {
        clonar_sol(sol, clone);
        gerar_vizinho(clone);

        if (clone.fo > sol.fo) {
           clonar_sol(clone, sol); 
        }
    }
        
    escrever_solucao(sol);
    return 0;
}