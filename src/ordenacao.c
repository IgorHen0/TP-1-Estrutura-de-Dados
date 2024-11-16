#include "../include/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

OrdInd_ptr Cria() {
    OrdInd_ptr o = (OrdInd_ptr) malloc(sizeof(OrdInd_t));
    o->dados = NULL;
    o->num_linhas = 0;
    o->num_atributos = 0;
    o->atributos = NULL;
    o->indices = NULL;
    return o;
}

int Destroi(OrdInd_ptr o) {
    if (o->dados != NULL) {
        for (int i = 0; i < o->num_linhas; i++) {
            free(o->dados[i]);
        }
        free(o->dados);
    }
    if (o->atributos != NULL) {
        for (int i = 0; i < o->num_atributos; i++) {
            free(o->atributos[i]);
        }
        free(o->atributos);
    }
    if (o->indices != NULL) {
        for (int i = 0; i < o->num_linhas; i++) { // Corrigido para num_linhas
            free(o->indices[i]);
        }
        free(o->indices);
    }
    free(o);
    return 0;
}

int CarregaArquivo(OrdInd_ptr o, char *nomeEntrada) {

    FILE *arq = fopen(nomeEntrada, "r");

    if (arq == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    // Lê a primeira linha do arquivo
    char tamLinha[1024];
    if (fgets(tamLinha, sizeof(tamLinha), arq) == NULL) {
        fclose(arq);
        printf("Arquivo vazio ou erro ao ler a primeira linha.\n");
        return -2;
    }

    // Conta o número de atributos
    o->num_atributos = 1; 
    for (char *p = tamLinha; *p != '\0'; p++) {
        if (*p == ',') {
            o->num_atributos++;
        }
    }

    // Conta quantas linhas tem o arquivo
    o->num_linhas = 1;
    while (fgets(tamLinha, sizeof(tamLinha), arq) != NULL) {
        o->num_linhas++;
    }

    fclose(arq);
    return 0;
}

int NumAtributos(OrdInd_ptr o) {
    return o->num_atributos;
}

int NumLinhas(OrdInd_ptr o) {
    return o->num_linhas;
}