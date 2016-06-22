#ifndef TAREFARESULTADOCAXEIROVIAJANTE_H
#define TAREFARESULTADOCAXEIROVIAJANTE_H

#include <QRunnable>
#include <QObject>
#include <QRunnable>
class TarefaResultadoCaxeiroViajante : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit TarefaResultadoCaxeiroViajante(QString mensagem);

signals:
    void resultado(QString dados);
public slots:
protected:
    void run();
private:
    QString mensagem;
};

#endif // TAREFARESULTADOCAXEIROVIAJANTE_H
