#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <memory.h>
#include <string.h>

#include <omp.h>

#include "cabecalho.h"
//#include "novo.h"

//#define DBG

int main()
{
    ler_dados("pmm1.txt");
    //escrever_dados(" ");

    return 0;
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






    /*
    teste();

    int a = 1;
    Solucao sol;
    teste(sol, a);




    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
            continue;

        printf("%d\n", i);
    }

    printf("\n%d threads disponiveis!\n\n", omp_get_max_threads());
    //#pragma omp parallel
	//{
	//	int thread_id = omp_get_thread_num();
	//	printf("Hello from thread %d\n", thread_id);
	//}

	int tam = 22;
	int vet[tam];
	#pragma omp parallel for
	for (int i = 0; i < tam; i++)
        vet[i] = omp_get_thread_num();

    for (int i = 0; i < tam; i++)
        printf("%d ", vet[i]);

    /*
    int m_s[TAMANHO][TAMANHO];
    int m2[TAMANHO][TAMANHO];
    memset(&m_s, 0, sizeof(m_s));
    memset(&m2, 0, sizeof(m2));

    memcpy(&m2, &m_s, sizeof(m_s));
    //m2 = m_s;
    m_s[0][0] = 50;

    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
            printf("%d ", m_s[i][j]);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
            printf("%d ", m2[i][j]);
        printf("\n");
    }

*/

    //alocacao();
/*
    int** m_n = new int* [TAMANHO];
    for (int i = 0; i < TAMANHO; i++)
        m_n[i] = new int [TAMANHO];
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            m_n[i][j] = 0;

    int** m2;

    //m2 = m_n;
    memcpy(&m2, &m_n, sizeof(m_n));
    m2[0][0] = 50;


    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
            printf("%d ", m_n[i][j]);
        printf("\n");
    }



    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
            printf("%d ", m2[i][j]);
        printf("\n");
    }


    for (int i = 0; i < TAMANHO; i++)
        delete[] m_n[i];
    delete[] m_n;

*/

void clone(Solucao& s1, Solucao& s2)
{
    memcpy(&s2, &s1, sizeof(Solucao));
}

void alocacao()
{
    clock_t h;
    double tempo;

    h = clock();
    for (int r = 0; r < REPETICOES; r++)
    {
        int** m_m = (int**)malloc(TAMANHO * sizeof(int*));
        for (int i = 0; i < TAMANHO; i++)
            m_m[i] = (int*)malloc(TAMANHO * sizeof(int));
        for (int i = 0; i < TAMANHO; i++)
            for (int j = 0; j < TAMANHO; j++)
                m_m[i][j] = 0;
        #ifdef DBG
        for (int i = 0; i < TAMANHO; i++)
        {
            for (int j = 0; j < TAMANHO; j++)
                printf("%d ", m_m[i][j]);
            printf("\n");
        }
        #endif
        for (int i = 0; i < TAMANHO; i++)
            free(m_m[i]);
        free(m_m);

    }
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("Tempo MALLOC: %.5f\n\n", tempo);


    h = clock();
    for (int r = 0; r < REPETICOES; r++)
    {
        int** m_c = (int**)calloc(TAMANHO, sizeof(int*));
        for (int i = 0; i < TAMANHO; i++)
            m_c[i] = (int*)calloc(TAMANHO, sizeof(int));
        #ifdef DBG
        for (int i = 0; i < TAMANHO; i++)
        {
            for (int j = 0; j < TAMANHO; j++)
                printf("%d ", m_c[i][j]);
            printf("\n");
        }
        #endif
        for (int i = 0; i < TAMANHO; i++)
            free(m_c[i]);
        free(m_c);
    }
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("Tempo CALLOC: %.5f\n\n", tempo);



    h = clock();
    for (int r = 0; r < REPETICOES; r++)
    {
        int** m_n = new int* [TAMANHO];
        for (int i = 0; i < TAMANHO; i++)
            m_n[i] = new int [TAMANHO];
        for (int i = 0; i < TAMANHO; i++)
            for (int j = 0; j < TAMANHO; j++)
                m_n[i][j] = 0;
        #ifdef DBG
        for (int i = 0; i < TAMANHO; i++)
        {
            for (int j = 0; j < TAMANHO; j++)
                printf("%d ", m_n[i][j]);
            printf("\n");
        }
        #endif
        for (int i = 0; i < TAMANHO; i++)
            delete[] m_n[i];
        delete[] m_n;
    }
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("Tempo NEW: %.5f\n\n", tempo);



    h = clock();
    for (int r = 0; r < REPETICOES; r++)
    {
        std::vector<std::vector<int>> m_v(TAMANHO, std::vector<int>(TAMANHO));
        #ifdef DBG
        for (int i = 0; i < m_v.size(); i++)
        {
            for (int j = 0; j < m_v[i].size(); j++)
                printf("%d ", m_v[i][j]);
            printf("\n");
        }
        #endif
    }
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("Tempo VECTOR: %.5f\n\n", tempo);

    h = clock();
    for (int r = 0; r < REPETICOES; r++)
    {
        int m_s[TAMANHO][TAMANHO];
        //memset(&m_s, 0, sizeof(m_s));
        #ifdef DBG
        for (int i = 0; i < TAMANHO; i++)
        {
            for (int j = 0; j < TAMANHO; j++)
                printf("%d ", m_s[i][j]);
            printf("\n");
        }
        #endif
    }
    tempo = (double)(clock() - h) / CLOCKS_PER_SEC;
    printf("Tempo ESTATICA: %.5f\n\n", tempo);

}

