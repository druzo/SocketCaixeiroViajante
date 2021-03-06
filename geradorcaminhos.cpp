#include "geradorcaminhos.h"

GeradorCaminhos::GeradorCaminhos(QList<ResultadoTSP*> *listaResultados, Graph *grafo, QObject *parent) : QThread(parent)
{
    this->listaResultados = listaResultados;
    this->grafo = grafo;
    this->grafoTransicao = grafo;
    fPararTarefa = false;
}

Graph *GeradorCaminhos::getGrafo() const
{
    return grafoTransicao;
}

void GeradorCaminhos::setGrafo(Graph *value)
{
    grafoTransicao = value;
}

void GeradorCaminhos::pararTarefa()
{
    this->fPararTarefa = true;
}

bool GeradorCaminhos::verList(int peso)
{
    for (int a; a<listaResultados->count(); a++)
    {
        if(peso== listaResultados->at(a)->custo){
            return true;
        }
    }
    return false;
}

void GeradorCaminhos::run()
{
    QTime temporizador;
    //rodando o AG construido para o trabalho
    //que por sua vez está na versão
    //Mini ALPHA 0.0001
    pCVAG->rodar();

    qDebug()<<"iniciando a busca no grafo";
    while(!fPararTarefa) {
        Genetic *genetic = new Genetic(this->grafo, randEntre(1000,20000), randEntre(2000, 50000), randEntre(0, 100), true);
        //variável responsável por fazer transição de grafos, caso seja chamado o setter setGrafo
        if(grafo != grafoTransicao){
            delete grafo;
            grafo = grafoTransicao;
            delete genetic;
            genetic = new Genetic(this->grafo, 2000, 1000, 100, false);
        }
        //iniciando captura do tempo de execução do algoritmo
        temporizador.start();
        ResultadoTSP *resultado;
        resultado = genetic->run();

        resultado->tempoExecucao = temporizador.elapsed();
        this->listaResultados->append(resultado);
        qDebug()<<"finalizou busca no grafo";
        qDebug()<< this->listaResultados->at(this->listaResultados->count()-1)->custo;
        //sleep(1);
        delete genetic;
    }
    exec();
}
