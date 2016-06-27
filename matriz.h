#ifndef MATRIZ_H
#define MATRIZ_H

template <class T>
class Matriz
{
private:
    T *matriz;
    unsigned int qtdeLinhas, qtdeColunas;
public:
    Matriz(const unsigned int qtdeLinhas, const unsigned int qtdeColunas);
    ~Matriz();
    unsigned int getQtdeLinhas() const;
    unsigned int getQtdeColunas() const;
    unsigned int getTotalPosicoes();
    T getItem(const unsigned int linha, const unsigned int coluna);
    T getItem(const unsigned int posicao);
    void setItem(const unsigned int linha, const unsigned int coluna, const T valor);
    void setItem(const unsigned int posicao,const T valor);
    void getLinColByPosition(int posicao, int *linha, int *coluna);
};
#include "matriz.cpp"
#endif // MATRIZ_H
