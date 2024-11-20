#include "../include/algoritmos.h"
#include "../include/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    OrdInd_ptr o = Cria();

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Erro ao obter o diretório atual");
        Destroi(o);
        return 1;
    }

    char caminho_arquivo[2048];
    snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s/entradas/cad.r10.p1000.xcsv", cwd);

    if (CarregaArquivo(o, caminho_arquivo) != 0) {
        printf("Erro ao carregar o arquivo.\n");
        Destroi(o);
        return 1;
    }

    //int num_atributos = NumAtributos(o);
    int num_linhas = NumLinhas(o);
    //int tam_payload = TamPayload(o);

    printf("Antes da ordenação:\n");
    for (int i = 0; i < num_linhas; i++) {
        printf("ID: %s, Nome: %s, Endereço: %s, Payload: \n", o->ids[i], o->nomes[i], o->enderecos[i]);
    }

    printf("------------------------");

    QuickSort(o, 0, num_linhas - 1, "ids");

    printf("\nDepois da ordenação por ID:\n");
    for (int i = 0; i < num_linhas; i++) {
        printf("Nome: %s, ID: %s, Endereço: %s, Payload: \n", o->nomes[i], o->ids[i], o->enderecos[i]);
    }

    QuickSort(o, 0, num_linhas - 1, "enderecos");

    printf("\nDepois da ordenação por Endereco:\n");
    for (int i = 0; i < num_linhas; i++) {
        printf("Nome: %s, ID: %s, Endereço: %s, Payload: \n", o->nomes[i], o->ids[i], o->enderecos[i]);
    }

    QuickSort(o, 0, num_linhas - 1, "nomes");

    printf("\nDepois da ordenação por Nome:\n");
    for (int i = 0; i < num_linhas; i++) {
        printf("Nome: %s, ID: %s, Endereço: %s, Payload: \n", o->nomes[i], o->ids[i], o->enderecos[i]);
    }

    Destroi(o);
    return 0;
}
