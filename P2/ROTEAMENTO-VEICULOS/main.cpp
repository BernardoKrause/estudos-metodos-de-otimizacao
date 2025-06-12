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
    int num_clientes;
    memset(sol.vet_qtd_cli_vei, 0, sizeof(sol.vet_qtd_cli_vei));
    for (int i = 0; i < num_vei; i++) {
        num_clientes = rand() % num_cli;
        for (int j = 0; j < num_clientes; j++) {
            sol.mat_sol[i][sol.vet_qtd_cli_vei[i]] = rand() % num_cli;
            sol.vet_qtd_cli_vei[i]++;
            printf("%d ", sol.mat_sol[i][j]);
        }
        printf("\n");
    }
}

// void calcular_fo2(Solucao& s)
// {
//     int vei = 0;
//     s.fo = 0;
//     memset(&s.vet_pes_vei, 0, sizeof(s.vet_pes_vei));
//     for (int j = 1; j < num_cli + num_vei + 1; j++)
//     {
//         if (s.vet_sol[j] == 0)
//             vei++;
//         s.fo += mat_custo[s.vet_sol[j-1]][s.vet_sol[j]];
//         s.vet_pes_vei[vei] += vet_dem_cli[s.vet_sol[j]];
//     }
//     for (int i = 0; i < num_vei; i++)
//         s.fo += PESO_CAP * MAX(0, s.vet_pes_vei[i] - vet_cap_vei[i]);
// }

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

int main()
{
    Solucao sol;
    ler_dados("instancia-toy.txt");

    criar_solucao_aleatoria(sol);
    calcular_fo(sol);

    // calcular_fo2(sol);
    printf("\n\nFO: %.2f\n", sol.fo);

    return 0;
}
