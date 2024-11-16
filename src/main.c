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
    snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s/entrada.csv", cwd);
        
    if (CarregaArquivo(o, caminho_arquivo) != 0) {
        printf("Erro ao carregar o arquivo.\n");
        Destroi(o);
        return 1;
    }

    int num_atributos = NumAtributos(o);
    int num_linhas = NumLinhas(o);
    printf("Numero de atributos: %d\n", num_atributos);
    printf("Numero de linhas: %d\n", num_linhas);

    Destroi(o);
    return 0;
}
