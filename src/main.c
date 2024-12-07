#include "../include/algoritmos.h"
#include "../include/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    OrdInd_ptr o = Cria();

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Erro ao obter o diretório atual");
        Destroi(o);
        return 1;
    }

    char caminho_arquivo[2048];
    snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s/entradas/input.xcsv", cwd);

    if (CarregaArquivo(o, caminho_arquivo) != 0) {
        printf("Erro ao carregar o arquivo.\n");
        Destroi(o);
        return 1;
    }

    int num_linhas = NumLinhas(o);
    // int num_atributos = NumAtributos(o);
    // int tam_payload = TamPayload(o);

    // printf("Número de linhas: %d\n", num_linhas);
    // printf("Número de atributos: %d\n", num_atributos);
    // printf("Tamanho do%d\n", tam_payload);

    // printf("Antes da ordenação:\n");
    // for (int i = 0; i < num_linhas; i++) {
    //     printf("ID: %s, %s,%s,\n", o->ids[i], o->nomes[i], o->enderecos[i]);
    // }

    // printf("------------------------");

    // Quick

    Informacoes(o);

    QuickSort(o, 0, num_linhas - 1, "nomes");
    // printf("\nDepois da ordenação por Nome:\n");
    for (int i = 0; i < num_linhas; i++) {
        printf("%s,%s,%s,%s\n", o->nomes[i], o->ids[i], o->enderecos[i], o->payloads[i]);
    }

    Informacoes(o);

    QuickSort(o, 0, num_linhas - 1, "ids");
    // printf("\nDepois da ordenação por ID:\n");
    for (int i = 0; i < num_linhas; i++) {
        printf("%s,%s,%s,%s\n", o->nomes[i], o->ids[i], o->enderecos[i], o->payloads[i]);
    }

    Informacoes(o);

    QuickSort(o, 0, num_linhas - 1, "enderecos");
    // printf("\nDepois da ordenação por Endereco:\n");
    for (int i = 0; i < num_linhas; i++) {
        printf("%s,%s,%s,%s\n", o->nomes[i], o->ids[i], o->enderecos[i], o->payloads[i]);
    }


    // Bubble

    Informacoes(o);

    // printf("Ordenado por Nomes:\n");
    BubbleSort(o->nomes, o->ids, o->enderecos, o->payloads, o->num_registros);
    for (int i = 0; i < o->num_registros; i++) {
        printf("%s,%s,%s,%s\n", o->nomes[i], o->ids[i], o->enderecos[i], o->payloads[i]);
    }

    Informacoes(o);

    // printf("\nOrdenado por IDs:\n");
    BubbleSort(o->ids, o->nomes, o->enderecos, o->payloads, o->num_registros);
    for (int i = 0; i < o->num_registros; i++) {
        printf("%s,%s,%s,%s\n", o->nomes[i], o->ids[i], o->enderecos[i], o->payloads[i]);
    }

    Informacoes(o);

    // printf("\nOrdenado por Endereços:\n");
    BubbleSort(o->enderecos, o->nomes, o->ids, o->payloads, o->num_registros);
    for (int i = 0; i < o->num_registros; i++) {
        printf("%s,%s,%s,%s\n", o->nomes[i], o->ids[i], o->enderecos[i], o->payloads[i]);
    }

    // Insertion

    Informacoes(o);

    // printf("Ordenado por Nomes:\n");
    InsertionSort(o, o->nomes);
    for (int i = 0; i < o->num_registros; i++) {
        printf("%s,%s,%s,%s\n", o->nomes[i], o->ids[i], o->enderecos[i], o->payloads[i]);
    }

    Informacoes(o);

    // printf("\nOrdenado por IDs:\n");
    InsertionSort(o, o->ids);
    for (int i = 0; i < o->num_registros; i++) {
        printf("%s,%s,%s,%s\n", o->nomes[i], o->ids[i], o->enderecos[i], o->payloads[i]);
    }

    Informacoes(o);

    // printf("\nOrdenado por Endereços:\n");
    InsertionSort(o, o->enderecos);
    for (int i = 0; i < o->num_registros; i++) {
        printf("%s,%s,%s,%s\n", o->nomes[i], o->ids[i], o->enderecos[i], o->payloads[i]);
    }

    Destroi(o);
    return 0;
}
