#include "../include/algoritmos.h"
#include "../include/ordenacao.h"
#include <string.h>

// Função auxiliar para trocar strings e os dados relacionados
void TrocaStrings(char *vet[], int i, int j, OrdInd_ptr o) {
    // Troca as strings no vetor
    char *temp = vet[i];
    vet[i] = vet[j];
    vet[j] = temp;

    // Troca os valores correspondentes em outras colunas
    char *temp_nome = o->nomes[i];
    o->nomes[i] = o->nomes[j];
    o->nomes[j] = temp_nome;

    char *temp_endereco = o->enderecos[i];
    o->enderecos[i] = o->enderecos[j];
    o->enderecos[j] = temp_endereco;

    char *temp_payload = o->payloads[i];
    o->payloads[i] = o->payloads[j];
    o->payloads[j] = temp_payload;
}

// Particiona para QuickSort de strings
int ParticionaStrings(char *vet[], int inicio, int fim, OrdInd_ptr o) {
    char *pivo = vet[fim];
    int pivo_indice = inicio;

    for (int i = inicio; i < fim; i++) {
        if (strcmp(vet[i], pivo) <= 0) {
            TrocaStrings(vet, i, pivo_indice, o);
            pivo_indice++;
        }
    }

    TrocaStrings(vet, pivo_indice, fim, o);
    return pivo_indice;
}

// QuickSort para strings, mantendo consistência com outros vetores
void QuickSortStrings(char *vet[], int inicio, int fim, OrdInd_ptr o) {
    if (inicio < fim) {
        int pivo_indice = ParticionaStrings(vet, inicio, fim, o);
        QuickSortStrings(vet, inicio, pivo_indice - 1, o);
        QuickSortStrings(vet, pivo_indice + 1, fim, o);
    }
}
