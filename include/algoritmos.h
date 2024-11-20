#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(OrdInd_ptr ordind, int i, int j);
int Particao(OrdInd_t *ordind, int low, int high, const char *atributo);
void QuickSort(OrdInd_t *ordind, int low, int high, const char *atributo);

#endif // ALGORITMOS_H