#include "tarefaresultadocaxeiroviajante.h"
#include <QDebug>
TarefaResultadoCaxeiroViajante::TarefaResultadoCaxeiroViajante(QList<ResultadoTSP *> *listaResultados, QString mensagem)
{
    qDebug() << "Rodando Tarefa de resultado do caxeiro Viajante";
    this->mensagem = mensagem;
    this->listaResultados = listaResultados;
}

void TarefaResultadoCaxeiroViajante::run()
{
    qDebug() <<"Iniciou a tarefa do caixeiro viajante";

    int opcao = mensagem.toInt();
    switch (opcao) {
    case 1:
        emit resultado("Bem vindo nós somos o grupo top, Fabiano, Paulo e Antônio!");
        break;
    case 2:
        emit resultado(buscaMelhorCaminho());
        break;
    default:
        emit resultado("Comando não reconhecido!");
        break;
    }

    qDebug() <<"Finalizou a tarefa do caixeiro viajante";
}

QString TarefaResultadoCaxeiroViajante::buscaMelhorCaminho()
{
    //pegando o maior número inteiro possível para um int
    int custo = std::numeric_limits<int>::max();
    int posicao = -1;
    for (int i = 0; i < this->listaResultados->count(); ++i) {
        if(this->listaResultados->at(i)->custo < custo){
            posicao = i;
            custo = this->listaResultados->at(i)->custo;
        }
    }
    return "Caminho:" + this->listaResultados->at(posicao)->caminhos +
            " Custo:" + QString::number(this->listaResultados->at(posicao)->custo) +
            " Tempo Processamento:" + QString::number(this->listaResultados->at(posicao)->tempoExecucao);
}

