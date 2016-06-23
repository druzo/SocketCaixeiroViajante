#ifndef TAREFARESULTADOCAXEIROVIAJANTE_H
#define TAREFARESULTADOCAXEIROVIAJANTE_H

#include <QRunnable>
#include <QObject>
#include <QRunnable>
#include "tsp.h"
#include <limits>
class TarefaResultadoCaxeiroViajante : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit TarefaResultadoCaxeiroViajante(QList<ResultadoTSP*> *listaResultados, QString mensagem);

signals:
    void resultado(QString dados);
public slots:
protected:
    void run();
private:
    QString mensagem;
    QList<ResultadoTSP*> *listaResultados;
    QString buscaMelhorCaminho();
};

#endif // TAREFARESULTADOCAXEIROVIAJANTE_H
