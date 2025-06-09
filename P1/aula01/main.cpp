#include "problema.h"
#include "cabecalho.h"

Problema PRB;

// se for vetor pode usar ponteiro
void ler_dados(const char* arq) {
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_obj, &num_moc);
    for (int j = 0; j < num_obj; j++) {
        fscanf(f, "%d", &vet_val_obj[j]);
    }
    for (int j = 0; j < num_obj; j++) {
        fscanf(f, "%d", &vet_pes_obj[j]);
    }
    for (int j = 0; j < num_moc; j++) {
        fscanf(f, "%d", &vet_cap_moc[j]);
    }
    fclose(f);
}

// função que serve tanto para escrever os dados num arquivo quanto para printar
void escrever_dados(const char* arq) {
    FILE* f;
    
    if (!strcmp(arq, " "))
        f = stdout;
    else
        f = fopen(arq, "w");
        
    fprintf(f, "%d %d \n", &num_obj, &num_moc);
    for (int j = 0; j < num_obj; j++) {
        fprintf(f, "%d ", &vet_val_obj[j]);
    }
    fprintf(f, "\n");
    for (int j = 0; j < num_obj; j++) {
        fprintf(f, "%d ", &vet_pes_obj[j]);
    }
    fprintf(f, "\n");
    for (int j = 0; j < num_moc; j++) {
        fprintf(f, "%d ", &vet_cap_moc[j]);
    }
    
    if (strcmp(arq, " "))
        fclose(f);
}

// se nao vou usar alguma variavel, passo como parametro constante (const Solucao& s)
// tentar ao máximo sempre passar o endereço da variavel
void clone(Solucao& s1, Solucao& s2) { // o * aponta, o & passa o endereço de memória. Na prática eu economizo um caracter pra digitar (s.fo = 0). Para * seria s->fo = 0
    // Alocação estática -> &
    // Alocação dinâmica -> *
    memcpy(&s2, &s1, sizeof(Solucao));

}

int main()
{
    // criar variáveis no inicio do código. Evitar ao máximo declarar variáveis no meio do código, principalmente dentro de for 
    // 
    
    // std::cout<<"Hello World";
    
    
    Solucao sol;
    
    ler_dados("./base.txt");
    escrever_dados("./escrever.txt");

    return 0;
}