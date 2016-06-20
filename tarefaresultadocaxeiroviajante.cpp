#include "tarefaresultadocaxeiroviajante.h"
#include <QDebug>
TarefaResultadoCaxeiroViajante::TarefaResultadoCaxeiroViajante()
{
    qDebug() << "Rodando Tarefa de resultado do caxeiro Viajante";
}

void TarefaResultadoCaxeiroViajante::run()
{
    qDebug() <<"Iniciou a tarefa do caixeiro viajante";
    qDebug() <<"Finalizou a tarefa do caixeiro viajante";
    emit resultado("retorno");
}

