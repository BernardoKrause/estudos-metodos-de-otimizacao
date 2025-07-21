#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <memory.h>
#include <string.h>

#include "pmm.h"

#define MAX(X,Y)((X > Y) ? (X) : (Y))
#define MIN(X,Y)((X < Y) ? (X) : (Y))

int PESO_CAP = 100;
int PESO_DUP = 1000;
// Uma busca local é uma meta heurística que começa com uma solução candidata (contruída por um método simples como guloso, aleatorio ou aleatorio guloso)
// A partir disso ela busca explorar a vizinhança dessa solução.
// E então move para uma solução vizinha se for melhor do que a atual
// então repete o processo até que nao se encontre nenhuma solução melhor na vizinhança (atingiu o ótimo local)

// Busca Local Randômica (Random Search)
// Passo a Passo:
// 1. Começa com uma solução s qualquer
// 2. A cada iteração, gere um vizinho aleatório dentro da vizinhança definida
// 3. Se o vizinho for melhor que a s atual, mova para ele
// 4. se não for melhor, permaneça na s atual e itere novamente
// 5. repita X vezes (X é o número de iterações a ser informado no for)

// recebo como parâmetros, uma solução inicial s e o número de iterações (int) 
void heu_BL_rand(Solucao& s, const int& iter)
{
    // declaro uma variável para armazenar a melhor FO
    int mel_fo = s.fo;
    while (true)
    {
        // defino uma variável flag para determinar quando encerrar o loop
        int flag = 1;
        // itero o número de vezes passado pelo parametro
        for (int i = 0; i < iter; i++) 
        {
            // escolho um objeto aleatório
            int obj = rand() % num_obj;
            // pego a mochila em que esse objeto está
            int moc_ori = s.vet_sol[obj];
            // declaro uma variavel para armazenar a nova mochila para qual o item será movido
            int moc_nov;
            do
            {
                // itero até aque escolha uma nova mochila
                moc_nov = rand() % (num_moc + 1) -  1;
            } while (moc_nov == moc_ori);

            // armazeno minha fo atual na variavel fo_ori
            int fo_ori = s.fo;
            // troco a mochila em que o item está armazenado no vet_sol
            s.vet_sol[obj] = moc_nov;
            // calculo a fo da nova solucao
            calcular_fo_solucao(s);
            
            // se a nova fo for melhor que a atual melhor fo, troco a melhor fo para a nova fo e seto a flag como false para tentar melhorar novamente
            if (s.fo > mel_fo)
            {
                mel_fo = s.fo;
                flag = 0;
            // se a nova fo não for melhor, volto os valores ao inicio (se não houver mais melhora, deixo a flag como 1 após iterar todo o for)
            } else {
                s.vet_sol[obj] = moc_ori;
                s.fo = fo_ori;
            }
        }
        // se ao final do for, a flag for = 1, paro a iteração pois não há mais melhora
        if (flag) break;
    }
}

// Busca Local Primeira Melhora (First Improvement)
// 1. Começo com uma solução inicial s
// 2. Itero sobre todos os vizinhos possíveis
// 3. Avalia os vizinhos em uma ordem específica (pode ser aleatória ou fixa)
// 4. Assim que encontrar o primeiro vizinho que melhore a solução, mova-se para ele e então inicie a próxima iteração.
// 5. Se nenhum vizinho for melhor que a solução atual, pare as iterações (atingiu o ótimo local)  
void heu_BL_PM(Solucao& s)
{
    // inicio a variável melhor fo com a fo atual
    int mel_fo = s.fo;
    // declaro um ponto para voltar em certo momento
    INICIO : ;
    // itero sobre o número de objetos
    for (int i = 0; i < num_obj; i++) {
        // declaro uma variável para armazenar a mochila em que o objeto atual está armazenado
        int moc_ori = s.vet_sol[i];
        // declaro uma variável para armazenar a fo atual
        int fo_ori = s.fo;

        // itero sobre o número de mochilas (-1 para não estar em nenhuma mochila) 
        for (int j = -1; j < num_moc; j++) {
            // armazeno o objeto atual i na mochila j
            s.vet_sol[i] = j;
            calcular_fo_solucao(s);
            // se houve melhora, mudo a melhor fo para a fo atual e volto ao ponto inicio
            if (s.fo > mel_fo) {
                mel_fo = s.fo;
                goto INICIO;
            // se não houve melhora, não mudo a solução
            } else {
                s.vet_sol[i] = moc_ori;
                s.fo = fo_ori;
            } 
        }
    }
    // Quando não houver mais melhora, atribuo a melhor fo a solucao s
    s.fo = mel_fo;
}

// Busca Local Melhor Melhora (Best Improvement)
// 1. Começa com uma solução s qualquer
// 2. Itero sobre todos os vizinhos possíveis
// 3. Se o melhor vizinho for melhor que a solução atual, movo pra ele
// 4. se nenhum vizinho for melhor, paro as iterações (atingiu o ótimo local)
void heu_BL_MM(Solucao& s) {
    // começo com uma variavel para armazenar a atual melhor fo
    int mel_fo = s.fo;
    while (true) {
        // declaro o melhor objeto e melhor mochila
        int mel_obj, mel_moc;
        // declaro a flag para servir como critério de parada para o loop
        int flag = 0;
        // itero sobre cada objeto
        for (int i = 0; i < num_obj; i++) {
            // armazeno a mochila atual do objeto em que estou operando
            int moc_ori = s.vet_sol[i];
            // itero sobre as possíveis lugares em que objeto pode estar (-1 para nenhuma mochila)
            for (int j = -1; j < num_moc; j++) {
                // armazeno o item na mochila atual
                s.vet_sol[i] = j;
                calcular_fo_solucao(s);
                // se a fo da sol vizinha atual, for melhor que a melhor fo, mudo a melhor fo para ela
                // então seto o melhor objeto e melhor mochila para os atuais
                // então seto a flag como true
                if (s.fo > mel_fo) {
                    mel_fo = s.fo;
                    mel_obj = i;
                    mel_moc = j;
                    flag = 1;
                }
            }
            // coloco o item i na mochila de origem após o loop
            // faço isso para seguir conforme as alterações ( no loop entre as mochilas, altero o vet_sol[i]), então aqui volto ele para a mochila original
            s.vet_sol[i] = moc_ori;
        }
        // uso a melhor fo na solução
        s.fo = mel_fo;
        // se a flag for 1, então atribuo o melhor objeto à melhor mochila;
        if (flag)
            s.vet_sol[mel_obj] = mel_moc;
        // se for 0, então não encontrou melhora, para o loop
        else
            break;
    }
}