#include "../include/algoritmos.h"
#include "../include/ordenacao.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Função para trocar elementos em todos os arrays
void Swap(OrdInd_ptr o, int i, int j) {
    if (!o->nomes || !o->ids || !o->enderecos || !o->payloads) {
        fprintf(stderr, "Erro: Memória não alocada para os vetores de registros.\n");
        return;
    }

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
    if (!o->nomes || !o->ids || !o->enderecos || !o->payloads) {
        fprintf(stderr, "Erro: Memória não alocada para os vetores de registros.\n");
        return -1;
    }

    if (inicio < 0 || fim >= o->num_registros || inicio > fim) {
        fprintf(stderr, "Erro: Índices inválidos (inicio=%d, fim=%d, num_registros=%d).\n", inicio, fim, o->num_registros);
        return -1;
    }

    char *pivot;
    if (strcmp(atributo, "nomes") == 0) {
        pivot = o->nomes[fim];
    } else if (strcmp(atributo, "ids") == 0) {
        pivot = o->ids[fim];
    } else if (strcmp(atributo, "enderecos") == 0) {
        pivot = o->enderecos[fim];
    } else {
        fprintf(stderr, "Erro: Atributo inválido '%s'.\n", atributo);
        return -1;
    }

    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if ((strcmp(atributo, "nomes") == 0 && strcmp(o->nomes[j], pivot) < 0) ||
            (strcmp(atributo, "ids") == 0 && strcmp(o->ids[j], pivot) < 0) ||
            (strcmp(atributo, "enderecos") == 0 && strcmp(o->enderecos[j], pivot) < 0)) {
            i++;
            Swap(o, i, j);
        }
    }
    Swap(o, i + 1, fim);
    return i + 1;
}

// Implementação do QuickSort
void QuickSort(OrdInd_ptr o, int inicio, int fim, const char *atributo) {
    if (!o || inicio < 0 || fim >= o->num_registros || inicio > fim) {
        fprintf(stderr, "Erro: Parâmetros inválidos para QuickSort.\n");
        return;
    }

    if (inicio < fim) {
        int pi = Particao(o, inicio, fim, atributo);

        if (pi == -1) {
            fprintf(stderr, "Erro: Partição falhou em QuickSort.\n");
            return;
        }

        // Ordena os elementos à esquerda e à direita do pivô
        QuickSort(o, inicio, pi - 1, atributo);
        QuickSort(o, pi + 1, fim, atributo);
    }
}

// BubbleSort com validações
void BubbleSort(char **arr, char **arr2, char **arr3, char **arr4, int n) {
    if (!arr || !arr2 || !arr3 || !arr4) {
        fprintf(stderr, "Erro: Memória não alocada para os arrays de BubbleSort.\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp;

                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                temp = arr2[j];
                arr2[j] = arr2[j + 1];
                arr2[j + 1] = temp;

                temp = arr3[j];
                arr3[j] = arr3[j + 1];
                arr3[j + 1] = temp;

                temp = arr4[j];
                arr4[j] = arr4[j + 1];
                arr4[j + 1] = temp;
            }
        }
    }
}

// Função de Insertion Sort para ordenar com base em uma coluna
void InsertionSort(OrdInd_ptr ordInd, char **base) {
    if (!ordInd || !base) {
        fprintf(stderr, "Erro: Parâmetros inválidos para InsertionSort.\n");
        return;
    }

    for (int i = 1; i < ordInd->num_registros; i++) {
        int j = i;

        // Enquanto a chave for menor, realize o swap
        while (j > 0 && strcmp(base[j - 1], base[j]) > 0) {
            Swap(ordInd, j, j - 1);
            j--; // Continue movendo para trás
        }
    }
}
