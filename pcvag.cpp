#include "pcvag.h"
#include <time.h>       /* time */
PCVAG::PCVAG(QString caminhoArquivoGrafo, unsigned int qtdeColunasGrafo, unsigned int qtdeLinhasGrafo, unsigned int tamanhoPopulacaoInicial)
{
    this->qtdeColunasGrafo = qtdeColunasGrafo;
    this->qtdeLinhasGrafo = qtdeLinhasGrafo;
    this->tamanhoPopulacaoInicial = tamanhoPopulacaoInicial;
    matrizAdjacencia = NULL;
    carregarArquivo(caminhoArquivoGrafo, qtdeColunasGrafo, qtdeLinhasGrafo);
    populacao = new QList<CaminhoCidades*>();
    vetorComparacao = new bool[qtdeColunasGrafo * qtdeLinhasGrafo];
}

PCVAG::~PCVAG()
{
    delete matrizAdjacencia;
    delete vetorComparacao;
    delete populacao;
}

void PCVAG::carregarArquivo(QString caminhoArquivoGrafo, unsigned int qtdeColunasGrafo, unsigned int qtdeLinhasGrafo)
{
    QFile *arquivo = new QFile(caminhoArquivoGrafo);
    //abrindo o arquivo para modo leitura de texto
    if(!arquivo->open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"Falha ao abrir arquivo";
        return;
    }
    QTextStream dados(arquivo);
    if(matrizAdjacencia)
    {
        delete matrizAdjacencia;
    }
    matrizAdjacencia = new Matriz<int>(qtdeLinhasGrafo, qtdeColunasGrafo);
    unsigned int linhaAtual = 0;
    while(!dados.atEnd()){
        unsigned int colunaAtual = 0;
        QString strAux = dados.readLine();
        unsigned int inicio = 0;
        for (int i = 0; i < strAux.length(); ++i) {
            if (strAux[i] == ';'){
                matrizAdjacencia->setItem(linhaAtual, colunaAtual, strAux.mid(inicio, i - inicio - 1).toInt());
                colunaAtual++;
                inicio = i + 1;
            }
        }
        linhaAtual++;
    }
    delete arquivo;
}

void PCVAG::rodar()
{
    gerarPopulacaoInicial();
    while(1)
    {
        //adicionando uma probabilidade de realizar uma mutação de 30%
        if(randEntre(0, 9) < 3)
            mutacao();
        else
            crossover();
    }
}

QString PCVAG::caminhoParaString(int posicao)
{
    QString retorno = "";
    for (unsigned int i = 0; i < populacao->at(posicao)->matrizCaminhos->getQtdeColunas(); ++i) {
        retorno += QString::number(populacao->at(posicao)->matrizCaminhos->getItem(i)) + ";";
    }
    retorno.remove(retorno.count()-1, 1);
    return retorno.trimmed();
}

void PCVAG::gerarPopulacaoInicial()
{
    srand (time(NULL));
    for (unsigned int i = 0; i < this->tamanhoPopulacaoInicial; ++i) {
        unsigned int qtdeCidades = 0;
        inicializaVetorComparacao();
        CaminhoCidades *caminhoCidades = new CaminhoCidades;
        caminhoCidades->matrizCaminhos = new Matriz<int>(1, this->qtdeColunasGrafo);
        caminhoCidades->pesoTotal = 0;
        populacao->append(caminhoCidades);
        while(qtdeCidades < qtdeColunasGrafo) {
            int cidade = randEntre(0, qtdeColunasGrafo -1);
            while(this->vetorComparacao[cidade])
            {
                cidade = randEntre(0, qtdeColunasGrafo -1);
            }
            caminhoCidades->matrizCaminhos->setItem(qtdeCidades, cidade);
            vetorComparacao[cidade] = true;
            if(qtdeCidades >= 1){
                caminhoCidades->pesoTotal += this->matrizAdjacencia->getItem(caminhoCidades->matrizCaminhos->getItem(0, qtdeCidades -1), caminhoCidades->matrizCaminhos->getItem(0, qtdeCidades));
            }
            qtdeCidades++;
        }
    }
    qDebug() << "Peso sem ordenar";
    for (int i = 0; i < populacao->count(); ++i) {
        qDebug() <<"Peso:" <<populacao->at(i)->pesoTotal;
        qDebug() << this->caminhoParaString(i);
    }
    //ordenando de forma crescente
    qSort(populacao->begin(), populacao->end(), ordenarCrescente);
}

void PCVAG::inicializaVetorComparacao()
{
    for (unsigned int i = 0; i < qtdeColunasGrafo; ++i) {
        vetorComparacao[i] = false;
    }
}

void PCVAG::crossover()
{
    unsigned int pontoCorteInicial, pontoCorteFinal;
    pontoCorteInicial = randEntre(0, qtdeColunasGrafo/2);
    pontoCorteFinal  = randEntre((qtdeColunasGrafo/2) + 1, qtdeColunasGrafo);
    CaminhoCidades *caminhoCidades1 = new CaminhoCidades;
    caminhoCidades1->matrizCaminhos = new Matriz<int>(1, this->qtdeColunasGrafo);
    caminhoCidades1->pesoTotal = 0;
    CaminhoCidades *caminhoCidades2 = new CaminhoCidades;
    caminhoCidades2->matrizCaminhos = new Matriz<int>(1, this->qtdeColunasGrafo);
    caminhoCidades2->pesoTotal = 0;

    //inicializando a matriz
    for (unsigned int i = 0; i < caminhoCidades1->matrizCaminhos->getTotalPosicoes(); ++i) {
        caminhoCidades1->matrizCaminhos->setItem(i, -1);
        caminhoCidades2->matrizCaminhos->setItem(i, -1);
    }

    //copiando faixa para o caminho
    for (unsigned int i = pontoCorteInicial; i < pontoCorteFinal; ++i) {
        caminhoCidades1->matrizCaminhos->setItem(i, populacao->at(1)->matrizCaminhos->getItem(i));
        caminhoCidades2->matrizCaminhos->setItem(i, populacao->at(0)->matrizCaminhos->getItem(i));
    }

    QList <Matriz<int>*> *listaDiferencas = new QList<Matriz<int>*>();
    //verificando os elementos que não foram copiados
    for (unsigned int i = pontoCorteInicial; i < pontoCorteFinal; ++i) {
        int valorI = caminhoCidades1->matrizCaminhos->getItem(i);
        int valorJ = -1;
        for (unsigned int j = pontoCorteInicial; j < pontoCorteFinal; ++j) {
            if (valorI != caminhoCidades2->matrizCaminhos->getItem(j)){
                valorJ = caminhoCidades2->matrizCaminhos->getItem(j);
            }
            else{
                valorJ = -1;
                break;
            }
        }
        if(valorJ != -1)
        {
            Matriz <int>*matAux = new Matriz<int>(1, 2);
            matAux->setItem(0, valorI);
            matAux->setItem(1, valorJ);
            listaDiferencas->append(matAux);
        }
    }

    //copiando elementos que nao foram encontrados nas faixas
    for (unsigned int i = 0; i < populacao->at(0)->matrizCaminhos->getTotalPosicoes(); ++i) {
        for (int j = 0; j < listaDiferencas->count(); ++j) {
            if(populacao->at(0)->matrizCaminhos->getItem(i) == listaDiferencas->at(j)->getItem(1)){
                caminhoCidades1->matrizCaminhos->setItem(i, listaDiferencas->at(j)->getItem(1));
            }
            else if(populacao->at(1)->matrizCaminhos->getItem(i) == listaDiferencas->at(j)->getItem(0)){
                caminhoCidades2->matrizCaminhos->setItem(i, listaDiferencas->at(j)->getItem(0));
            }
        }
    }
    //copiando o restante das matrizes pai e contabilizando peso
    for (unsigned int i = 0; i < caminhoCidades1->matrizCaminhos->getTotalPosicoes(); ++i) {
        if(caminhoCidades1->matrizCaminhos->getItem(i) == -1)
        {
            caminhoCidades1->matrizCaminhos->setItem(i, populacao->at(1)->matrizCaminhos->getItem(i));
        }
        if(caminhoCidades2->matrizCaminhos->getItem(i) == -1)
        {
            caminhoCidades2->matrizCaminhos->setItem(i, populacao->at(0)->matrizCaminhos->getItem(i));
        }
        if(i >= 1){
            caminhoCidades1->pesoTotal += this->matrizAdjacencia->getItem(caminhoCidades1->matrizCaminhos->getItem(0, i -1), caminhoCidades1->matrizCaminhos->getItem(0, i));
            caminhoCidades2->pesoTotal += this->matrizAdjacencia->getItem(caminhoCidades2->matrizCaminhos->getItem(0, i -1), caminhoCidades2->matrizCaminhos->getItem(0, i));
        }
    }
    populacao->removeLast();
    populacao->removeLast();
    populacao->append(caminhoCidades1);
    populacao->append(caminhoCidades2);
    qSort(populacao->begin(), populacao->end(), ordenarCrescente);
//    qDebug()<<"peso 1 "<<caminhoCidades1->pesoTotal;
//    qDebug()<<"peso 2 "<<caminhoCidades2->pesoTotal;
}

void PCVAG::mutacao()
{
    unsigned int pontoCorteInicial = randEntre(0, qtdeColunasGrafo/2);
    unsigned int pontoCorteFinal  = randEntre((qtdeColunasGrafo/2) + 1, qtdeColunasGrafo -1);
    int valor1 = populacao->last()->matrizCaminhos->getItem(pontoCorteInicial);
    populacao->last()->matrizCaminhos->setItem(pontoCorteInicial, populacao->last()->matrizCaminhos->getItem(pontoCorteFinal));
    populacao->last()->matrizCaminhos->setItem(pontoCorteInicial, valor1);

//    while(pontoCorteFinal != pontoCorteInicial)
//    {
//        int item = populacao->last()->matrizCaminhos->getItem(pontoCorteInicial);
//        populacao->last()->matrizCaminhos->setItem(pontoCorteInicial, populacao->last()->matrizCaminhos->getItem(pontoCorteFinal -1));
//        populacao->last()->matrizCaminhos->setItem(pontoCorteFinal, item);
//        pontoCorteFinal--;
//        pontoCorteInicial++;
//    }
    calcularFitness(populacao->count() -1);
    qSort(populacao->begin(), populacao->end(), ordenarCrescente);
}

void PCVAG::calcularFitness(int itemPopulacao)
{
    for (unsigned int i = 0; i < populacao->at(itemPopulacao)->matrizCaminhos->getQtdeColunas(); ++i) {
        if(i >= 1){
            populacao->at(itemPopulacao)->pesoTotal += this->matrizAdjacencia->getItem(populacao->at(itemPopulacao)->matrizCaminhos->getItem(0, i -1), populacao->at(itemPopulacao)->matrizCaminhos->getItem(0, i));
        }
    }
}

bool ordenarCrescente(const CaminhoCidades *c1, const CaminhoCidades *c2)
{
    return c1->pesoTotal < c2->pesoTotal;
}
