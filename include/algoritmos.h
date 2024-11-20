#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Troca(int vet[], int i, int j);
int Particiona(int vet[], int inicio, int fim);
int ParticionaRandom(int vet[], int inicio, int fim);
void QuickSortStrings(char *vet[], int inicio, int fim, OrdInd_ptr o);

#endif // ALGORITMOS_H