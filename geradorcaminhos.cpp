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

void GeradorCaminhos::run()
{
    QTime temporizador;

    Genetic *genetic = new Genetic(this->grafo, 10, 1000, 5, true);
    while(!fPararTarefa) {
        //variável responsável por fazer transição de grafos, caso seja chamado o setter setGrafo
        if(grafo != grafoTransicao){
            delete grafo;
            grafo = grafoTransicao;
            delete genetic;
            genetic = new Genetic(this->grafo, 10, 1000, 5, true);
        }
        //iniciando captura do tempo de execução do algoritmo
        temporizador.start();
        ResultadoTSP *resultado;
        resultado = genetic->run();

        resultado->tempoExecucao = temporizador.elapsed();
        this->listaResultados->append(resultado);
        sleep(1);
    }
    exec();
}
