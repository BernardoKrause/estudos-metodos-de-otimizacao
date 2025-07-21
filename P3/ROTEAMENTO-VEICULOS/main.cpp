#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <memory.h>
#include <string.h>
#include <math.h>

#include "cabecalho.h"

#define MAX(X,Y)((X > Y) ? (X) : (Y))

const int PESO_CAP = 100;

void ler_dados(const char* arq)
{
    int aux;
    int vetX[MAX_CLI];
    int vetY[MAX_CLI];
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_cli, &num_vei);
    for (int j = 0; j <= num_cli; j++)
        fscanf(f, "%d %d %d %d", &aux, &vetX[j], &vetY[j], &vet_dem_cli[j]);
    for (int i = 0; i < num_vei; i++)
        fscanf(f, "%d", &vet_cap_vei[i]);
    fclose(f);

    for (int i = 0; i <= num_cli; i++)
        for (int j = 0; j <= num_cli; j++)
            mat_custo[i][j] = sqrt(pow(vetX[i]-vetX[j],2)+pow(vetY[i]-vetY[j],2));
}

void criar_solucao_aleatoria(Solucao& sol)
{
    memset(&sol.vet_qtd_cli_vei, 0, sizeof(sol.vet_qtd_cli_vei));
    memset(&sol.vet_pes_vei, 0, sizeof(sol.vet_pes_vei));
    memset(&visitado, 0, sizeof(visitado));

    int counter = 0, cli, vei, pos;
    while (counter < num_cli) {
        cli = 1 + rand() % num_cli;
        if (visitado[cli] == 1) continue;

        vei = rand() % num_vei;
        pos = sol.vet_qtd_cli_vei[vei];

        sol.mat_sol[vei][pos] = cli;
        sol.vet_qtd_cli_vei[vei] ++;
        sol.vet_pes_vei[vei] += vet_dem_cli[cli];
        visitado[cli] = 1;
        counter++;
    }

    for (int i = 0; i < num_vei; i++) {
        printf("%d ", sol.vet_qtd_cli_vei[i]);
    }

    printf("\n");

    for (int i = 0; i < num_vei; i++) {
        for (int j = 0; j < num_cli; j++) {
            printf("%d ", sol.mat_sol[i][j]);
        }
        printf("\n");
    }
}

void calcular_fo(Solucao& sol)
{
    sol.fo = 0;
    memset(&sol.vet_pes_vei, 0, sizeof(sol.vet_pes_vei));
    for (int i = 0; i < num_vei; i++) // linha
    {
        sol.fo += mat_custo[0][sol.mat_sol[i][0]];
        sol.vet_pes_vei[i] += vet_dem_cli[sol.mat_sol[i][0]];
        for (int j = 1; j < sol.vet_qtd_cli_vei[i]; j++) // coluna
        {
            sol.fo += mat_custo[sol.mat_sol[i][j-1]][sol.mat_sol[i][j]];
            sol.vet_pes_vei[i] += vet_dem_cli[sol.mat_sol[i][j]];
        }
        sol.fo += mat_custo[sol.mat_sol[i][sol.vet_qtd_cli_vei[i]-1]][0];
        //---
        sol.fo += PESO_CAP * MAX(0, sol.vet_pes_vei[i] - vet_cap_vei[i]);
    }
}

void clonar_solucao (Solucao& clone, Solucao& sol) {
    memcpy(&clone, &sol, sizeof(sol));
}

void remover_cliente(Solucao& s, const int& vei, const int& pos) {
    int cli = s.mat_sol[vei][pos]; // Salva antes de deslocar
    for (int i = pos; i < s.vet_qtd_cli_vei[vei] - 1; i++)
        s.mat_sol[vei][i] = s.mat_sol[vei][i + 1];
    s.vet_qtd_cli_vei[vei]--;
    s.vet_pes_vei[vei] -= vet_dem_cli[cli];
}

void inserir_cliente(Solucao& s, const int& vei, const int& pos, const int& cli) {
    for (int i = s.vet_qtd_cli_vei[vei]; i > pos; i--)
        s.mat_sol[vei][i] = s.mat_sol[vei][i - 1];
    s.mat_sol[vei][pos] = cli;
    s.vet_qtd_cli_vei[vei]++;
    s.vet_pes_vei[vei] += vet_dem_cli[cli];
}

void gerar_vizinho(Solucao& sol) {
    int vei1,vei2,pos1,pos2,cli;

    do {
        vei1 = rand() % num_vei;
    } while (sol.vet_qtd_cli_vei[vei1] == 0);

    do {
        vei2 = rand() % num_vei;
    } while (sol.vet_qtd_cli_vei[vei2] == 0 || vei1 == vei2);

    pos1 = rand() % sol.vet_qtd_cli_vei[vei1];
    pos2 = rand() % sol.vet_qtd_cli_vei[vei2];

    cli = sol.mat_sol[vei1][pos1];

    remover_cliente(sol, vei1, pos1);
    inserir_cliente(sol, vei2, pos2, cli);
}

void heu_BL_rand(Solucao& sol, const int& n) {
    double mel_fo = sol.fo;
    int flag;
    while (true) {
        flag = 1;

        for (int i = 0; i < n; i++) {
            Solucao sol_ori;
            memcpy(&sol, &sol_ori, sizeof(&sol));
            gerar_vizinho(sol);
            calcular_fo(sol);

            if (sol.fo > sol_ori.fo) {
                mel_fo = sol.fo;
                flag = 0;
            } else {
                memcpy(&sol_ori, &sol, sizeof(&sol_ori));
            }
        }

        if (flag) break;
    }
}

int main()
{
    Solucao sol;
    Solucao clone;

    srand(time(NULL));

    ler_dados("instancia.txt");

    criar_solucao_aleatoria(sol);
    calcular_fo(sol);

    for (int i = 0; i < 100000; i++) {
        clonar_solucao(clone, sol);
        gerar_vizinho(clone);

        if (clone.fo < sol.fo) {
            clonar_solucao(sol, clone);
        }
    }

    printf("\n\nFO: %.2f\n", sol.fo);

    return 0;
}
