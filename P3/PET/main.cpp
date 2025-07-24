#include "cabecalho.h"

void ler_dados(const char* arq) {
    FILE* f = fopen(arq, "r");

    fscanf(f, "%d %d %d", &num_tarefas, &temp_normal_trab, &temp_max_trab);
    for (int i = 0; i < num_tarefas; i++) {
        fscanf(f, "%d %d", &vet_h_ini_tarefa[i], &vet_h_term_tarefa[i]);
    }

    fclose(f);
}

void criar_solucao(Solucao& sol) {
    // no criar solucao, zero o vetor de numero de tarefas por tripulação
    memset(&sol.vet_num_tarefas_trip, 0, sizeof(sol.vet_num_tarefas_trip));
    
    for (int i = 0; i < num_tarefas; i++) {
        // escolho uma tripulação aleatória, preencho a matriz na linha da tripulação (indice da tripualação) e coluna da tarefa (indice da tripualacao no vetor de tarefas para ir pro indice a ser adicionado uma nova tarefa)
        // então somo 1 no numero de tarefas dessa tripulacao 
        int tripulacao = rand() % num_trip;
        sol.mat_sol[tripulacao][sol.vet_num_tarefas_trip[tripulacao]] = i; 
        sol.vet_num_tarefas_trip[tripulacao] += 1;
    }

    // for (int i = 0; i < num_trip; i++) {
    //     for (int j = 0; j < sol.vet_num_tarefas_trip[i]; j++) {
    //         printf("%d ", sol.mat_sol[i][j]);
    //     }
    //     printf("\n");
    //     printf("tripulação %d: %d tarefas \n",i , sol.vet_num_tarefas_trip[i]);
    // }
}

void calcular_fo(Solucao &s){

    s.h_extra = s.t_ocioso = s.t_sobre = s.t_exce = s.fo = 0; // zero todos os valores de horas na solucao

    for(int i = 0; i < num_trip; i++){

        if(s.vet_num_tarefas_trip[i] == 0) continue; // se o numero de tarefas da tripulação for 0, continua para a próxima iteração para só interagir com as tripulações com tarefas

        for(int j = 1; j < s.vet_num_tarefas_trip[i]; j++){ // itera sobre todas as tarefas de cada tripulação
            s.t_ocioso += MAX(0, (vet_h_ini_tarefa[s.mat_sol[i][j]] - vet_h_term_tarefa[s.mat_sol[i][j-1]])); // calcula o tempo ocioso que é a hora de inicio da tarefa menos a hora de termino da tarefa anterior 
            s.t_sobre += MAX(0, vet_h_term_tarefa[s.mat_sol[i][j-1]] - vet_h_ini_tarefa[s.mat_sol[i][j]]); // calcula o tempo de sobreposição que é a hora de termino da tarefa anterior - a tarefa de agora
        }

       s.t_ocioso += MAX(0, temp_normal_trab - (vet_h_term_tarefa[i] - vet_h_ini_tarefa[i])); // soma ao temp ocioso, o tempo normal de trabalho menos o tempo de uma tarefa  
       s.h_extra += MIN(temp_max_trab - temp_normal_trab, MAX(0, (vet_h_term_tarefa[s.mat_sol[i][s.vet_num_tarefas_trip[i] - 1]] - vet_h_ini_tarefa[s.mat_sol[i][0]]) - temp_normal_trab));
       s.t_exce += MAX(0, (vet_h_term_tarefa[s.mat_sol[i][s.vet_num_tarefas_trip[i] - 1]] - vet_h_ini_tarefa[s.mat_sol[i][0]]) - temp_max_trab);
    }

    s.fo += (PESO_EXTRA * s.h_extra) + (PESO_OCIOSO * s.t_ocioso) + (PESO_SOBREPOSICAO * s.t_sobre) + (PESO_EXCEDIDO * s.t_exce);
}

void clonar_solucao(Solucao& sol, Solucao& clone) {
    memcpy(&clone, &sol, sizeof(sol));
}

void remover_tarefa(Solucao& sol, const int &trip, const int &pos) {
    for (int i = pos; i < sol.vet_num_tarefas_trip[trip]; i++)
        sol.mat_sol[trip][i] = sol.mat_sol[trip][i+1];

    sol.vet_num_tarefas_trip[trip] --;
}

void adicionar_tarefa(Solucao& sol, const int &trip, const int &tarefa) {
    int i;
    for (i = sol.vet_num_tarefas_trip[trip] - 1 ; i >= 0; i--) {
        if (vet_h_ini_tarefa[sol.mat_sol[trip][i]] > vet_h_ini_tarefa[tarefa]) {
            sol.mat_sol[trip][i + 1] = sol.mat_sol[trip][i];
        } else {
            break;
        }
    }

    sol.mat_sol[trip][i + 1] = tarefa;
    sol.vet_num_tarefas_trip[trip]++;
}

void gerar_vizinho(Solucao& sol) {
    int trip1, trip2, pos, tarefa;

    // enquanto não gerar uma tripulação com tarefa, randomize
    do
    {
        trip1 = rand() % num_trip;
    } while (sol.vet_num_tarefas_trip[trip1] == 0);

    pos = rand() % sol.vet_num_tarefas_trip[trip1]; // pego uma posição aleatória entre 0 e o numero de tarefas da trip1
    tarefa = sol.mat_sol[trip1][pos]; // pego a tarefa da trip1 na posição gera aleatoriamente

    do
    {
        trip2 = rand() % num_trip; // gero uma trip2 diferente da trip1
    } while (trip1 == trip2);
    
    remover_tarefa(sol, trip1, pos);
    adicionar_tarefa(sol, trip2, tarefa);
    calcular_fo(sol);

    for (int i = 0; i < num_trip; i++) {
        for (int j = 0; j < sol.vet_num_tarefas_trip[i]; j++) {
            printf("%d ", sol.mat_sol[i][j]);
        }
        printf("\n");
        printf("tripulação %d: %d tarefas \n",i , sol.vet_num_tarefas_trip[i]);
    }
}

void heu_BL_random(Solucao& sol, const int& iter) {
    int flag;
    while (true) {
        flag = 1;
        
        for (int i = 0; i < iter; i++) {
            Solucao sol_ori;
            memcpy(&sol, &sol_ori, sizeof(sol));
            
            gerar_vizinho(sol);

            if (sol.fo < sol_ori.fo) {
                memcpy(&sol_ori, &sol, sizeof(sol_ori));
                flag = 0;
            }

        }
        if (flag) break;
    }
}

void hel_BL_PM(Solucao& sol) {
    int mel_fo = sol.fo;
    int pos, tarefa;

    INICIO : ;
    for (int i = 0; i < num_trip; i++) {
        Solucao sol_ori;
        memcpy(&sol, &sol_ori, sizeof(sol));
        for (int j = 0; j < num_tarefas; j++) {
            pos = rand() % sol.vet_num_tarefas_trip[i];
            tarefa = sol.mat_sol[i][pos];
            remover_tarefa(sol, i, tarefa);
            adicionar_tarefa(sol, i, j);

            calcular_fo(sol);
            if (sol.fo > mel_fo) {
                mel_fo = sol.fo;
                goto INICIO;
            } else {
                memcpy(&sol_ori, &sol, sizeof(sol_ori));
            }
        }
    }
}

void hel_BL_PM2(Solucao& sol) {
    INICIO : ;
    for (int i = 0; i < num_trip; i++) {
        for (int j = 0; j < sol.vet_num_tarefas_trip[i]; j++) {
            memcpy(&sol_vizinha, &sol, sizeof(Solucao));
            int tarefa = sol.mat_sol[i][j];
            remover_tarefa(sol_vizinha, i, tarefa);
            for (int k = 0; k < num_trip; k++) {
                if (k != i) {
                    adicionar_tarefa(sol_vizinha, i, tarefa);
                    calcular_fo(sol_vizinha);

                    if (sol_vizinha.fo > sol.fo) {
                        memcpy(&sol, &sol_vizinha, sizeof(Solucao));
                        goto INICIO;
                    } else {
                        remover_tarefa(sol_vizinha, i, tarefa);
                        calcular_fo(sol_vizinha);
                    }
                }
            }
            
        }
    }
}

int main () {
    Solucao sol;
    Solucao clone;
    
    ler_dados("csp25.txt");

    // Primeiro calculo no número de tripulações que vai ser o número total de horas divido pelo tempo normal de trabalho que é o tempo normal de um turno, e então arredondo para cima com o ceil()
    for (int i = 0; i < num_tarefas; i++) {
        contador_temp += (vet_h_term_tarefa[i] - vet_h_ini_tarefa[i]);
    }

    num_trip = ceil(contador_temp / temp_normal_trab);

    criar_solucao(sol);
    calcular_fo(sol);
    
    // printf("%d\n", sol.fo);
    for (int i = 0; i < 50; i++) {
        clonar_solucao(sol, clone);
        gerar_vizinho(clone);
        
        if (clone.fo < sol.fo) {
            clonar_solucao(clone, sol);
            // printf("%d \n", sol.fo);
        } 
    }

    return 0;
}