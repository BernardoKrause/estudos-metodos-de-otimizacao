#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <memory.h>
#include <string.h>

#include <omp.h>

#include "pmm.h"

#define MAX(X,Y)((X > Y) ? (X) : (Y))
#define MIN(X,Y)((X < Y) ? (X) : (Y))

//#define DBG

int PESO_CAP = 100;
int PESO_DUP = 1000;

int main()
{
    Solucao sol, sol_clone;
    clock_t h;
    double tempo;

    //srand(time(NULL));

    ler_dados("pmm3.txt");
    //escrever_dados(" ");

    ordenar_objetos();
    for (int j = 0; j < num_obj; j++)
        printf("%d ", vet_ind_ord[j]);

    h = clock();
    for (int i = 0; i < 1; i++)
        heu_cons_ale(sol);
    calcular_fo_solucao(sol);
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("\nALE: %d\tTempo: %.5f", sol.fo, tempo);

    Solucao MM, PM, PM2;
    memcpy(&MM, &sol, sizeof(Solucao));
    memcpy(&PM, &sol, sizeof(Solucao));
    memcpy(&PM2, &sol, sizeof(Solucao));

    h = clock();
    for (int i = 0; i < 1; i++)
        heu_BL_rand(sol, 3 * (num_moc + 1) * num_obj);
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("\nRND: %d\tTempo: %.5f", sol.fo, tempo);

    h = clock();
    for (int i = 0; i < 1; i++)
        heu_BL_MM(MM);
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("\nMM: %d\tTempo: %.5f", MM.fo, tempo);

    h = clock();
    for (int i = 0; i < 1; i++)
        heu_BL_PM(PM);
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("\nPM: %d\tTempo: %.5f", PM.fo, tempo);

    h = clock();
    for (int i = 0; i < 1; i++)
        heu_BL_PM2(PM2);
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("\nPM2: %d\tTempo: %.5f", PM2.fo, tempo);
    /*
    h = clock();
    for (int i = 0; i < 1; i++)
        heu_cons_gul(sol);
    calcular_fo_solucao(sol);
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("\nGUL: %d\tTempo: %.5f", sol.fo, tempo);

    h = clock();
    for (int i = 0; i < 1; i++)
        heu_cons_ale_gul(sol, 12);
    calcular_fo_solucao(sol);
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("\nALE GUL: %d\tTempo: %.5f", sol.fo, tempo);
    /*
    criar_solucao(sol);
    calcular_fo_solucao(sol);

    for (int i = 0; i < 1000000; i++)
    {
        memcpy(&sol_clone, &sol, sizeof(Solucao));
        gerar_vizinha(sol_clone);
        if (sol_clone.fo >= sol.fo)
            memcpy(&sol, &sol_clone, sizeof(Solucao));
    }

    escrever_solucao(sol);
    //escrever_solucao(sol_clone);
    */

    return 0;
}

void heu_BL_rand(Solucao& s, const int& iter)
{
    int mel_fo = s.fo;
    while (true)
    {
        int flag = 1;
        for (int i = 0; i < iter; i++)
        {
            int obj = rand() % num_obj;
            int moc_ori = s.vet_sol[obj];
            int moc_nov;
            do
                moc_nov = rand() % (num_moc + 1) - 1;
            while (moc_nov == moc_ori);
            int fo_ori = s.fo;
            s.vet_sol[obj] = moc_nov;
            calcular_fo_solucao(s);
            if (s.fo > mel_fo)
            {
                mel_fo = s.fo;
                flag = 0;
            }
            else
            {
                s.vet_sol[obj] = moc_ori;
                s.fo = fo_ori;
            }
        }
        if (flag)
            break;
    }
}

void heu_BL_MM(Solucao& s)
{
    int mel_fo = s.fo;
    while (true)
    {
        int mel_obj, mel_moc;
        int flag = 0;
        for (int j = 0; j < num_obj; j++)
        {
            int moc_ori = s.vet_sol[j];
            for (int i = -1; i < num_moc; i++)
            {
                s.vet_sol[j] = i;
                calcular_fo_solucao(s);
                if (s.fo > mel_fo)
                {
                    mel_fo = s.fo;
                    mel_obj = j;
                    mel_moc = i;
                    flag = 1;
                }
            }
            s.vet_sol[j] = moc_ori;
        }
        s.fo = mel_fo;
        if (flag)
            s.vet_sol[mel_obj] = mel_moc;
        else
            break;
    }
}

void heu_BL_PM(Solucao& s)
{
    int mel_fo = s.fo;
    INICIO : ;
    for (int j = 0; j < num_obj; j++)
    {
        int moc_ori = s.vet_sol[j];
        int fo_ori = s.fo;
        for (int i = -1; i < num_moc; i++)
        {
            s.vet_sol[j] = i;
            calcular_fo_solucao(s);
            if (s.fo > mel_fo)
            {
                mel_fo = s.fo;
                goto INICIO;
            }
            else
            {
                s.vet_sol[j] = moc_ori;
                s.fo = fo_ori;
            }
        }
    }
    s.fo = mel_fo;
}

void heu_BL_PM2(Solucao& s)
{
    int vet_aux[MAX_OBJ];
    for (int j = 0; j < num_obj; j++)
        vet_aux[j] = vet_ind_ord[j];
    int mel_fo = s.fo;
    INICIO : ;
    for (int j = 0; j < num_obj; j++)
    {
        int pos = j + rand() % (num_obj - j);
        int obj = vet_aux[pos];

        int moc_ori = s.vet_sol[obj];
        int fo_ori = s.fo;
        for (int i = -1; i < num_moc; i++)
        {
            s.vet_sol[obj] = i;
            calcular_fo_solucao(s);
            if (s.fo > mel_fo)
            {
                mel_fo = s.fo;
                goto INICIO;
            }
            else
            {
                s.vet_sol[obj] = moc_ori;
                s.fo = fo_ori;
            }
        }
        int aux = vet_aux[j];
        vet_aux[j] = vet_aux[pos];
        vet_aux[pos] = aux;
    }
    s.fo = mel_fo;
}

void heu_cons_ale_gul(Solucao& s, const double& percentual)
{
    int obj, qtd, pos, aux;
    int vet_aux[MAX_OBJ];
    for (int j = 0; j < num_obj; j++)
        vet_aux[j] = vet_ind_ord[j];
    qtd = MAX(2, (percentual / 100.0) * num_obj);
    for (int j = 0; j < qtd; j++)
    {
        pos = j + rand()%(num_obj-j);
        aux = vet_aux[j];
        vet_aux[j] = vet_aux[pos];
        vet_aux[pos] = aux;
    }
    //---
    memset(&s.vet_pes_moc, 0, sizeof(s.vet_pes_moc));
    memset(&s.vet_sol, -1, sizeof(s.vet_sol));
    for (int j = 0; j < num_obj; j++)
    {
        obj = vet_aux[j];
        for (int i = 0; i < num_moc; i++)
        {
            if (s.vet_pes_moc[i] + vet_pes_obj[obj] <= vet_cap_moc[i])
            {
                s.vet_sol[obj] = i;
                s.vet_pes_moc[i] += vet_pes_obj[obj];
                break;
            }
        }
    }
}

void heu_cons_gul(Solucao& s)
{
    int obj;
    memset(&s.vet_pes_moc, 0, sizeof(s.vet_pes_moc));
    memset(&s.vet_sol, -1, sizeof(s.vet_sol));
    for (int j = 0; j < num_obj; j++)
    {
        obj = vet_ind_ord[j];
        for (int i = 0; i < num_moc; i++)
        {
            if (s.vet_pes_moc[i] + vet_pes_obj[obj] <= vet_cap_moc[i])
            {
                s.vet_sol[obj] = i;
                s.vet_pes_moc[i] += vet_pes_obj[obj];
                break;
            }
        }
    }
}

void heu_cons_ale(Solucao& s)
{
    for (int j = 0; j < num_obj; j++)
        s.vet_sol[j] = rand() % (num_moc + 1) - 1;
}

void ordenar_objetos()
{
    int flag, aux;
    for (int j = 0; j < num_obj; j++)
        vet_ind_ord[j] = j;
    flag = 1;
    while(flag)
    {
        flag = 0;
        for (int j = 0; j < num_obj - 1; j++)
        {
            if ((double)vet_val_obj[vet_ind_ord[j]] / vet_pes_obj[vet_ind_ord[j]] <
                (double)vet_val_obj[vet_ind_ord[j + 1]] / vet_pes_obj[vet_ind_ord[j + 1]])
            {
                aux = vet_ind_ord[j];
                vet_ind_ord[j] = vet_ind_ord[j + 1];
                vet_ind_ord[j + 1] = aux;
                flag = 1;
            }
        }
    }
}

void gerar_vizinha(Solucao& s)
{
    int obj, moc;
    obj = rand() % num_obj;
    moc = s.vet_sol[obj];
    do
        s.vet_sol[obj] = rand() % (num_moc + 1) - 1;
    while(s.vet_sol[obj] == moc);
    calcular_fo_solucao(s);
}

void calcular_fo_solucao(Solucao& s)
{
    s.fo = 0;
    memset(&s.vet_pes_moc, 0, sizeof(s.vet_pes_moc));
    for (int j = 0; j < num_obj; j++)
    {
        if (s.vet_sol[j] != -1)
        {
            s.fo += vet_val_obj[j];
            s.vet_pes_moc[s.vet_sol[j]] += vet_pes_obj[j];
        }
    }
    for (int i = 0; i < num_moc; i++)
        s.fo -= PESO_CAP * MAX(0, (s.vet_pes_moc[i] - vet_cap_moc[i]));
}

void escrever_solucao(const Solucao& s)
{
    printf("\n\nFO: %d\n", s.fo);
    printf("Peso mochilas: ");
    for (int i = 0; i < num_moc; i++)
        printf("%d ", s.vet_pes_moc[i]);
    printf("\nVetor solucao: ");
    for (int j = 0; j < num_obj; j++)
        printf("%d ", s.vet_sol[j]);
}

void escrever_dados(char* arq)
{
    FILE* f;
    if (!strcmp(arq, " "))
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "%d %d\n", num_obj, num_moc);
    for (int j = 0; j < num_obj; j++)
        fprintf(f, "%d ", vet_val_obj[j]);
    fprintf(f, "\n");
    for (int j = 0; j < num_obj; j++)
        fprintf(f, "%d ", vet_pes_obj[j]);
    fprintf(f, "\n");
    for (int i = 0; i < num_moc; i++)
        fprintf(f, "%d ", vet_cap_moc[i]);
    if (strcmp(arq, " "))
        fclose(f);
}

void ler_dados(char* arq)
{
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_obj, &num_moc);
    for (int j = 0; j < num_obj; j++)
        fscanf(f, "%d", &vet_val_obj[j]);
    for (int j = 0; j < num_obj; j++)
        fscanf(f, "%d", &vet_pes_obj[j]);
    for (int i = 0; i < num_moc; i++)
        fscanf(f, "%d", &vet_cap_moc[i]);
    fclose(f);
}
