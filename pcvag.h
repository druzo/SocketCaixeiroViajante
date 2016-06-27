#ifndef PCVAG_H
#define PCVAG_H
#include "matriz.h"
#include <qstring.h>
#include <qfile.h>
#include <qdebug.h>
#include "libutil.h"
struct CaminhoCidades{
    Matriz<int> *matrizCaminhos;
    int pesoTotal;
};
bool ordenarCrescente(const CaminhoCidades *c1, const CaminhoCidades *c2);
//Classe que resolve o Problema do caixeiro Viajante utilizando algoritmo genético
class PCVAG
{
public:
    Matriz<int> *matrizAdjacencia;
    QList<CaminhoCidades*> *populacao;
    PCVAG(QString caminhoArquivoGrafo, unsigned int qtdeColunasGrafo, unsigned int qtdeLinhasGrafo, unsigned int tamanhoPopulacaoInicial);
    ~PCVAG();
    void carregarArquivo(QString caminhoArquivoGrafo, unsigned int qtdeColunasGrafo, unsigned int qtdeLinhasGrafo);
    void rodar();    
    QString caminhoParaString(int posicao);
private:
    bool *vetorComparacao;
    unsigned int qtdeColunasGrafo, qtdeLinhasGrafo, tamanhoPopulacaoInicial;
    void gerarPopulacaoInicial();
    void inicializaVetorComparacao();
    //Método que realiza crossover utilizando a técnica PMX(Partial Mapped Crossover)
    void crossover();
    //realiza uma mutação
    void mutacao();
    void calcularFitness(int itemPopulacao);
};

#endif // PCVAG_H
