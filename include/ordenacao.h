#ifndef ORDENACAO_H
#define ORDENACAO_H

typedef struct OrdInd {
    char **dados;
    int num_linhas;
    int num_atributos;
    char **atributos;
    int **indices;
} OrdInd_t, *OrdInd_ptr;

OrdInd_ptr Cria();
int Destroi (OrdInd_ptr o);
int CarregaArquivo (OrdInd_ptr o, char *nomeEntrada);
int NumAtributos (OrdInd_ptr o);
int NumLinhas (OrdInd_ptr o);

#endif // ORDENACAO_H