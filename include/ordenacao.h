#ifndef ORDENACAO_H
#define ORDENACAO_H

typedef struct OrdInd {
    int num_registros;
    int num_atributos;
    int tam_payload;
    char **atributos;
    char **nomes;
    char **ids;
    char **enderecos;
    char **payloads;
} OrdInd_t, *OrdInd_ptr;

OrdInd_ptr Cria();
void Destroi(OrdInd_ptr o);
int CarregaArquivo(OrdInd_ptr o, char *nomeEntrada);
int NumAtributos(OrdInd_ptr o);
int NumLinhas(OrdInd_ptr o);
int TamPayload(OrdInd_ptr o);
void Informacoes(OrdInd_ptr o);

#endif // ORDENACAO_H
