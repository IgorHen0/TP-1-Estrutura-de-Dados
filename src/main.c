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

    printf("Numero de atributos: %d\n", num_atributos);
    printf("Numero de registros: %d\n", num_linhas);
    printf("Tamanho do payload: %d\n", tam_payload);
    printf("\nRegistros Carregados:\n");
    printf("----------------------------------------------------------\n");

    // Imprime cada registro
    for (int i = 0; i < num_linhas; i++) {
        printf("Registro %d:\n", i + 1);
        printf("  Nome: %s\n", o->nomes[i]);
        printf("  ID: %s\n", o->ids[i]);
        printf("  Endereço: %s\n", o->enderecos[i]);
        printf("  Payload: %s\n", o->payloads[i]);
        printf("----------------------------------------------------------\n");
    }

    Destroi(o);
    return 0;
}
