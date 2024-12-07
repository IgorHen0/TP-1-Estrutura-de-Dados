#include "../include/ordenacao.h"
#include "../include/algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 6500 

OrdInd_ptr Cria() {
    OrdInd_ptr o = (OrdInd_ptr)malloc(sizeof(OrdInd_t));
    o->num_registros = 0;
    o->num_atributos = 0;
    o->tam_payload = 0;
    o->atributos = NULL;
    o->nomes = NULL;
    o->ids = NULL;
    o->enderecos = NULL;
    o->payloads = NULL;
    return o;
}

void Destroi(OrdInd_ptr o) {
    if (!o) return;

    if (o->atributos) {
        for (int i = 0; i < o->num_atributos; i++) {
            free(o->atributos[i]);
        }
        free(o->atributos);
    }

    if (o->nomes) {
        for (int i = 0; i < o->num_registros; i++) {
            free(o->nomes[i]);
        }
        free(o->nomes);
    }

    if (o->ids) {
        for (int i = 0; i < o->num_registros; i++) {
            free(o->ids[i]);
        }
        free(o->ids);
    }

    if (o->enderecos) {
        for (int i = 0; i < o->num_registros; i++) {
            free(o->enderecos[i]);
        }
        free(o->enderecos);
    }

    if (o->payloads) {
        for (int i = 0; i < o->num_registros; i++) {
            free(o->payloads[i]);
        }
        free(o->payloads);
    }

    free(o);
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

    // Aloca memória para os atributos
    o->atributos = (char **)malloc(o->num_atributos * sizeof(char *));
    if (!o->atributos) {
        perror("Erro ao alocar memória para os atributos");
        fclose(arq);
        return -1;
    }

    // Lê e armazena os atributos
    for (int i = 0; i < o->num_atributos; i++) {
        if (fgets(linha, sizeof(linha), arq)) {
            linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha
            o->atributos[i] = strdup(linha);
        } else {
            perror("Erro ao ler os atributos");
            for (int j = 0; j < i; j++) {
                free(o->atributos[j]);
            }
            free(o->atributos);
            fclose(arq);
            return -1;
        }
    }

    // Lê o número de registros
    if (fgets(linha, sizeof(linha), arq)) {
        o->num_registros = atoi(linha);
    } else {
        perror("Erro ao ler o número de registros");
        fclose(arq);
        return -1;
    }

    // Determina o tamanho do payload a partir do arquivo
    char *p_ptr = strstr(nomeEntrada, ".p");
    if (p_ptr) {
        o->tam_payload = atoi(p_ptr + 2);
    } else {
        perror("Erro ao ler o tamanho do payload");
        fclose(arq);
        return -1;
    }

    // Aloca memória para os vetores
    o->nomes = (char **)malloc(o->num_registros * sizeof(char *));
    o->ids = (char **)malloc(o->num_registros * sizeof(char *));
    o->enderecos = (char **)malloc(o->num_registros * sizeof(char *));
    o->payloads = (char **)malloc(o->num_registros * sizeof(char *));

    if (!o->nomes || !o->ids || !o->enderecos || !o->payloads) {
        perror("Erro ao alocar memória para os registros");
        free(o->nomes); free(o->ids); free(o->enderecos); free(o->payloads);
        fclose(arq);
        return -1;
    }

    // Lê os registros e armazena nos vetores
    for (int i = 0; i < o->num_registros; i++) {
        if (fgets(linha, sizeof(linha), arq)) {

            // Copia o nome
            int len = 0;
            while (linha[len] != ',') len++;
            o->nomes[i] = (char *)malloc((len + 1) * sizeof(char));
            strncpy(o->nomes[i], linha, len);
            o->nomes[i][len] = '\0';

            // Copia o id
            int start = len + 1;
            len = 0;
            while (linha[start + len] != ',') len++;
            o->ids[i] = (char *)malloc((len + 1) * sizeof(char));
            strncpy(o->ids[i], linha + start, len);
            o->ids[i][len] = '\0';

            // Copia o endereço
            start += len + 1;
            len = 0;
            while (linha[start + len] != ',') len++;
            o->enderecos[i] = (char *)malloc((len + 1) * sizeof(char));
            strncpy(o->enderecos[i], linha + start, len);
            o->enderecos[i][len] = '\0';

            // Copia o payload
            start += len + 1;
            len = 0;
            while (linha[start + len] != '\n' && linha[start + len] != '\0') len++;
            o->payloads[i] = (char *)malloc((len + 1) * sizeof(char));
            strncpy(o->payloads[i], linha + start, len);
            o->payloads[i][len] = '\0';
        } else {
            // Caso ocorra erro, libere a memória já alocada para o registro
            for (int j = 0; j < i; j++) {
                free(o->nomes[j]);
                free(o->ids[j]);
                free(o->enderecos[j]);
                free(o->payloads[j]);
            }
            free(o->nomes); free(o->ids); free(o->enderecos); free(o->payloads);
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
