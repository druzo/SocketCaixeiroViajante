#include "tarefaresultadocaxeiroviajante.h"
#include <QDebug>
TarefaResultadoCaxeiroViajante::TarefaResultadoCaxeiroViajante(QString mensagem)
{
    qDebug() << "Rodando Tarefa de resultado do caxeiro Viajante";
    this->mensagem = mensagem;
}

void TarefaResultadoCaxeiroViajante::run()
{
    qDebug() <<"Iniciou a tarefa do caixeiro viajante";

    int opcao = mensagem.toInt();
    switch (opcao) {
    case 1:
        emit resultado("Bem vindo nós somos o grupo top, Fabiano, Paulo e Antônio!");
        break;
    default:
        emit resultado("Comando não reconhecido!");
        break;
    }

    qDebug() <<"Finalizou a tarefa do caixeiro viajante";
}

