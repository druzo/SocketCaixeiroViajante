#include "tarefaresultadocaxeiroviajante.h"
#include <QDebug>
#include "libutil.h"
TarefaResultadoCaxeiroViajante::TarefaResultadoCaxeiroViajante(PCVAG *pCVAG, QList<ResultadoTSP *> *listaResultados, QString mensagem)
{
    qDebug() << "Rodando Tarefa de resultado do caxeiro Viajante";
    this->mensagem = mensagem;
    this->listaResultados = listaResultados;
    this->pCVAG = pCVAG;
}

void TarefaResultadoCaxeiroViajante::run()
{
    qDebug() <<"Iniciou a tarefa do caixeiro viajante";

    int opcao = mensagem.toInt();
    switch (opcao) {
    case 1:
        emit resultado("Druzo, Fabiano e Paulo");
        break;
    case 2:
        emit resultado( buscaMelhorCaminho());
        //emit resultado(pCVAG->caminhoParaString(0));
        break;
    case 3:
        //emit resultado( buscaMelhorCaminho());
        //emit resultado(pCVAG->caminhoParaString(pCVAG->populacao->count() -1));
        break;
    case 4:
        //emit resultado( buscaMelhorCaminho());
        //emit resultado(pCVAG->caminhoParaString(randEntre(0, pCVAG->populacao->count() -1)));
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
    return this->listaResultados->at(posicao)->caminhos;// +
//            " Custo:" + QString::number(this->listaResultados->at(posicao)->custo) +
//            " Tempo Processamento:" + QString::number(this->listaResultados->at(posicao)->tempoExecucao);
}
