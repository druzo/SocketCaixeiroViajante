#include "matriz.h"
#define TEMPL template <class T>

TEMPL unsigned int Matriz<T>::getQtdeLinhas() const
{
    return qtdeLinhas;
}

TEMPL unsigned int Matriz<T>::getQtdeColunas() const
{
    return qtdeColunas;
}

TEMPL unsigned int Matriz<T>::getTotalPosicoes()
{
    return qtdeColunas * qtdeLinhas;
}

//funcao responsavel para pegar o valor de uma matriz
TEMPL T Matriz<T>::getItem(const unsigned int linha, const unsigned int coluna)
{
    //Validações
    if(linha > qtdeLinhas - 1)
    {
        throw "Essa matriz não possui essa linha!";
    }

    if(coluna > qtdeColunas - 1)
    {
        throw "Essa matriz não possui essa coluna!";
    }

    return this->matriz[linha * this->qtdeColunas + coluna];
}

TEMPL T Matriz<T>::getItem(const unsigned int posicao)
{
    if(posicao > (this->qtdeColunas * this->qtdeLinhas) - 1)
    {
        throw "Posição inválida";
    }
    return this->matriz[posicao];
}

//funcao responsável por atribuir um valor na matriz
TEMPL void Matriz<T>::setItem(const unsigned int linha, const unsigned int coluna, const T valor)
{
    //Validações
    if(linha > qtdeLinhas - 1)
    {
        throw "Essa matriz não possui essa linha!";
    }

    if(coluna > qtdeColunas - 1 )
    {
        throw "Essa matriz não possui essa coluna!";
    }

    this->matriz[linha * this->qtdeColunas + coluna] = valor;
}

TEMPL void Matriz<T>::setItem(const unsigned int posicao, const T valor)
{
    if(posicao > (this->qtdeColunas * this->qtdeLinhas) - 1)
    {
        throw "Posição inválida";
    }
    this->matriz[posicao] = valor;
}

TEMPL void Matriz<T>::getLinColByPosition(int posicao, int *linha, int *coluna)
{
    if(posicao > (this->qtdeColunas * this->qtdeLinhas) - 1)
    {
        throw "Posição inválida";
    }

    *linha = posicao/this->qtdeColunas;
    *coluna = posicao%this->qtdeColunas;
}

TEMPL Matriz<T>::Matriz(const unsigned int qtdeLinhas, const unsigned int qtdeColunas)
{
    if (qtdeLinhas <= 0)
    {
        throw "A quantidade de linhas da matriz deve ser maior do que zero";
    }

    if (qtdeColunas <= 0)
    {
        throw "A quantidade de colunas da matriz deve ser maior do que zero";
    }
    this->qtdeLinhas = qtdeLinhas;
    this->qtdeColunas = qtdeColunas;
    matriz = new T[qtdeLinhas * qtdeColunas];
    for(unsigned int i = 0; i < qtdeLinhas * qtdeColunas; i++)
    {
        matriz[i] = NULL;
    }
}

TEMPL Matriz<T>::~Matriz()
{
    delete []matriz;
}
