#ifndef LIBUTIL
#define LIBUTIL
#include <stdlib.h>
unsigned int randEntre(int valorInicial, int valorFinal);
int gerarId();
int *gerarVetorNumerosRandomicos(int valorInicial, int valorFinal, unsigned int quantidade);
bool buscaValor(int *vetor, int valor, unsigned int quantidade);
void inicializaVetor(int *vetor, int valorInicial, unsigned int quantidade);
#endif // LIBUTIL

