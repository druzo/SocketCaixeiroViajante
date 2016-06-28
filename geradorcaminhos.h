#ifndef GERADORCAMINHOS_H
#define GERADORCAMINHOS_H

#include <QObject>
#include <QThread>
#include <QList>
#include "tsp.h"
#include <QSemaphore>
#include <QTime>
#include <QDebug>
#include "pcvag.h"
class GeradorCaminhos : public QThread
{
    Q_OBJECT
public:
    explicit GeradorCaminhos(QList<ResultadoTSP*> *listaResultados, Graph *grafo, QObject *parent = 0);

    Graph *getGrafo() const;
    void setGrafo(Graph *value);
    void pararTarefa();
    PCVAG *pCVAG;

signals:

public slots:
private:
    QList<ResultadoTSP*> *listaResultados;
    Graph *grafo;
    Graph *grafoTransicao;
    QSemaphore gerenteLista;

    bool fPararTarefa;
    bool verList(int peso);
protected:
    void run();
};

#endif // GERADORCAMINHOS_H
