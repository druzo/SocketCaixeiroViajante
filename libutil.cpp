#include "libutil.h"
unsigned int randEntre(int valorInicial, int valorFinal)
{
    return   rand()%(valorFinal - valorInicial + 1) + valorInicial;
}

int gerarId()
{
    //Variável estática para ter senhas diferentes em qualquer instancia do objeto
    static int s_nID = 1;
    return s_nID++;
}

bool buscaValor(int *vetor, int valor, unsigned int quantidade){
    for (unsigned int i = 0; i < quantidade; ++i) {
        if (valor == vetor[i])
            return true;
    }
    return false;
}

void inicializaVetor(int *vetor, int valorInicial, unsigned int quantidade){
    for (unsigned int i = 0; i < quantidade; ++i) {
        vetor[i] = valorInicial;
    }
}

int *gerarVetorNumerosRandomicos(int valorInicial, int valorFinal, unsigned int quantidade){
    int *retorno = new int(quantidade);
    inicializaVetor(retorno, -1, quantidade);
    unsigned int i = 0;
    while(i < quantidade){
        int valor = randEntre(valorInicial, valorFinal);
        if (!buscaValor(retorno, valor, quantidade)){
            retorno[i] = valor;
            i++;
        }
    }
    return retorno;
}
