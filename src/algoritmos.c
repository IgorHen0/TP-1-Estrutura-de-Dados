#include "../include/algoritmos.h"
#include "../include/ordenacao.h"
#include <string.h>

// Função para trocar elementos em todos os arrays
void Swap(OrdInd_ptr o, int i, int j) {
    char *temp;

    // Troca os nomes
    temp = o->nomes[i];
    o->nomes[i] = o->nomes[j];
    o->nomes[j] = temp;

    // Troca os ids
    temp = o->ids[i];
    o->ids[i] = o->ids[j];
    o->ids[j] = temp;

    // Troca os endereços
    temp = o->enderecos[i];
    o->enderecos[i] = o->enderecos[j];
    o->enderecos[j] = temp;

    // Troca os payloads
    temp = o->payloads[i];
    o->payloads[i] = o->payloads[j];
    o->payloads[j] = temp;
}

// Partição do QuickSort
int Particao(OrdInd_ptr o, int inicio, int fim, const char *atributo) {
    char *pivot;
    if (strcmp(atributo, "nomes") == 0) {
        pivot = o->nomes[fim];
    } else if (strcmp(atributo, "ids") == 0) {
        pivot = o->ids[fim];
    } else if (strcmp(atributo, "enderecos") == 0) {
        pivot = o->enderecos[fim];
    } else {
        printf("Atributo invalido!");
        return -1;
    }
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (strcmp(atributo, "nomes") == 0) {
            if (strcmp(o->nomes[j], pivot) < 0) {
                i++;
                Swap(o, i, j);
            }
        } else if (strcmp(atributo, "ids") == 0) {
            if (strcmp(o->ids[j], pivot) < 0) {
                i++;
                Swap(o, i, j);
            }
        } else if (strcmp(atributo, "enderecos") == 0) {
            if (strcmp(o->enderecos[j], pivot) < 0) {
                i++;
                Swap(o, i, j);
            }
        } 
    }
    Swap(o, i + 1, fim);
    return i + 1;
}

// Implementação do QuickSort
void QuickSort(OrdInd_ptr o, int inicio, int fim, const char *atributo) {
    if (inicio < fim) {
        int pi = Particao(o, inicio, fim, atributo);

        // Ordena os elementos à esquerda e à direita do pivô
        QuickSort(o, inicio, pi - 1, atributo);
        QuickSort(o, pi + 1, fim, atributo);
    }
}