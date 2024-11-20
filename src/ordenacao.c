#include "../include/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 2048

OrdInd_ptr Cria() {
    OrdInd_ptr o = (OrdInd_ptr)malloc(sizeof(OrdInd_t));
    o->num_registros = 0;
    o->num_atributos = 0;
    o->tam_payload = 0;
    o->nomes = NULL;
    o->ids = NULL;
    o->enderecos = NULL;
    o->payloads = NULL;
    return o;
}

int Destroi(OrdInd_ptr o) {
    if (o) {
        for (int i = 0; i < o->num_registros; i++) {
            free(o->nomes[i]);
            free(o->ids[i]);
            free(o->enderecos[i]);
            free(o->payloads[i]);
        }
        free(o->nomes);
        free(o->ids);
        free(o->enderecos);
        free(o->payloads);
        free(o);
    }
    return 0;
}

int CarregaArquivo(OrdInd_ptr o, char *nomeEntrada) {
    FILE *arq = fopen(nomeEntrada, "r");
    if (!arq) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char linha[MAX_LINHA];
    if (fgets(linha, sizeof(linha), arq)) {
        o->num_atributos = atoi(linha);
    } else {
        perror("Erro ao ler a primeira linha");
        fclose(arq);
        return -1;
    }

    // Pula as próximas 4 linhas (nomes dos atributos)
    for (int i = 0; i < 4; i++) {
        if (!fgets(linha, sizeof(linha), arq)) {
            perror("Erro ao pular as linhas dos atributos");
            fclose(arq);
            return -1;
        }
    }

    // Lê o tamanho do payload
    if (fgets(linha, sizeof(linha), arq)) {
        o->tam_payload = atoi(linha);
    } else {
        perror("Erro ao ler o tamanho do payload");
        fclose(arq);
        return -1;
    }

    // Determina o número de registros a partir do arquivo
    char *r_ptr = strstr(nomeEntrada, ".r");
    if (r_ptr) {
        o->num_registros = atoi(r_ptr + 2);
    } else {
        perror("Erro ao determinar o número de registros");
        fclose(arq);
        return -1;
    }

    // Aloca memória para os vetores
    o->nomes = (char **)malloc(o->num_registros * sizeof(char *));
    o->ids = (char **)malloc(o->num_registros * sizeof(char *));
    o->enderecos = (char **)malloc(o->num_registros * sizeof(char *));
    o->payloads = (char **)malloc(o->num_registros * sizeof(char *));

    // Lê os registros e armazena nos vetores
    for (int i = 0; i < o->num_registros; i++) {
        if (fgets(linha, sizeof(linha), arq)) {
            char *token = strtok(linha, ",");
            o->nomes[i] = strdup(token);

            token = strtok(NULL, ",");
            o->ids[i] = strdup(token);

            token = strtok(NULL, ",");
            o->enderecos[i] = strdup(token);

            token = strtok(NULL, ",");
            o->payloads[i] = strdup(token);
        } else {
            perror("Erro ao ler um registro");
            fclose(arq);
            return -1;
        }
    }

    fclose(arq);
    return 0;
}

int NumAtributos(OrdInd_ptr o) {
    return o->num_atributos;
}

int NumLinhas(OrdInd_ptr o) {
    return o->num_registros;
}

int TamPayload(OrdInd_ptr o) {
    return o->tam_payload;
}
