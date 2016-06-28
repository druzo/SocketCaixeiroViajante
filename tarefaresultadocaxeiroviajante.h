#ifndef TAREFARESULTADOCAXEIROVIAJANTE_H
#define TAREFARESULTADOCAXEIROVIAJANTE_H

#include <QRunnable>
#include <QObject>
#include <QRunnable>
#include "tsp.h"
#include <limits>
#include "pcvag.h"
class TarefaResultadoCaxeiroViajante : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit TarefaResultadoCaxeiroViajante(PCVAG *pCVAG, QList<ResultadoTSP*> *listaResultados, QString mensagem);

signals:
    void resultado(QString dados);
public slots:
protected:
    void run();
private:
    QString mensagem;
    QList<ResultadoTSP*> *listaResultados;
    QString buscaMelhorCaminho();
    PCVAG *pCVAG;
};

#endif // TAREFARESULTADOCAXEIROVIAJANTE_H
