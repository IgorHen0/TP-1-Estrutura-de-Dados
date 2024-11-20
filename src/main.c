#include "../include/algoritmos.h"
#include "../include/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

    int num_atributos = NumAtributos(o);
    int num_linhas = NumLinhas(o);
    int tam_payload = TamPayload(o);

    printf("Antes da ordenação:\n");
    for (int i = 0; i < num_linhas; i++) {
        printf("ID: %s, Nome: %s, Endereço: %s, Payload: %s\n", o->ids[i], o->nomes[i], o->enderecos[i], o->payloads[i]);
    }

    printf("------------------------");

    // Ordena os IDs e ajusta os vetores associados
    QuickSortStrings(o->ids, 0, num_linhas - 1, o);

    printf("\nDepois da ordenação:\n");
    for (int i = 0; i < num_linhas; i++) {
        printf("ID: %s, Nome: %s, Endereço: %s, Payload: %s\n", o->ids[i], o->nomes[i], o->enderecos[i], o->payloads[i]);
    }

    Destroi(o);
    return 0;
}
