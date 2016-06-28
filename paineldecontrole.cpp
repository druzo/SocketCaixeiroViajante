#include "paineldecontrole.h"
#include "ui_paineldecontrole.h"
#include <QTcpSocket>
#include <serverclient.h>
#include <QFileDialog>


PainelDeControle::PainelDeControle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PainelDeControle)
{
    ui->setupUi(this);
    //Atenção alterar caminho para o nome do arquivo correto.
  //  pcvag = new PCVAG("/tmp/grafos-caixeiro_viajante/grafo-caixeiro-matriz-250.txt", 250, 250, 100);
//    pcvag = new PCVAG("/tmp/grafos-caixeiro_viajante/grafo-500.txt", 500, 500, 100);
    pcvag = new PCVAG("/tmp/grafos-caixeiro_viajante/grafo-300.txt", 300, 500, 100);
    listaTSP = new QList<ResultadoTSP*>();
    grafoCidades = new Graph(259, 0);
    socketTcpServer = new SocketTcpServer(this->pcvag, listaTSP, this);
    connect(socketTcpServer, SIGNAL(aoConectarNovoCliente(ServerClient*)), this, SLOT(aoConectarNovoCliente(ServerClient*)));
    geradorCaminhos = new GeradorCaminhos(listaTSP, grafoCidades, this);
    geradorCaminhos->pCVAG = this->pcvag;
    sc = NULL;
}

PainelDeControle::~PainelDeControle()
{
    delete ui;
}

void PainelDeControle::on_pushButton_clicked()
{
    socketTcpServer->iniciarServidor();
    geradorCaminhos->start(QThread::LowestPriority);
}

void PainelDeControle::aoReceberMensagem(QTcpSocket *cliente, QByteArray dados)
{
    ui->edtMensagens->appendPlainText("cliente:" + cliente->peerAddress().toString() + " mensagem: " + dados);
}

void PainelDeControle::aoConectarNovoCliente(ServerClient *cliente)
{
    connect(cliente, SIGNAL(aoReceberMensagem(QTcpSocket*,QByteArray)), this, SLOT(aoReceberMensagem(QTcpSocket*,QByteArray)));
    ui->listaClientes->addItem(cliente->getIpCliente());
}

void PainelDeControle::aoReceberMensagemServidorTCP(QString mensagem)
{
    ui->EdtMensagensRecebidasCliente->appendPlainText(mensagem);
}

void PainelDeControle::carregarArquivoGrafos(QString caminho, Graph *grafo)
{
    QFile *arquivo = new QFile(caminho);
    //abrindo o arquivo para modo leitura de texto
    if(!arquivo->open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"Falha ao abrir arquivo";
        return;
    }
    QTextStream dados(arquivo);
    unsigned int linhaAtual = 0;
    while(!dados.atEnd()){
        unsigned int colunaAtual = 0;
        QString strAux = dados.readLine();
        unsigned int inicio = 0;
        for (int i = 0; i < strAux.length(); ++i) {
            if (strAux[i] == ';'){
                grafo->addEdge(linhaAtual, colunaAtual, strAux.mid(inicio, i - inicio - 1).toInt());
                colunaAtual++;
                inicio = i + 1;
            }
        }
        linhaAtual++;
    }
    delete arquivo;
}

void PainelDeControle::on_btCarregarGrafo_clicked()
{
    QString nomeArquivo = QFileDialog::getOpenFileName(this,tr("Abrir Arquivo de Grafo"), "", tr("Arquivos Textos (*.txt)"));
    if(nomeArquivo == "")
        return;
    grafoCidades = new Graph(259, 0);
    this->carregarArquivoGrafos(nomeArquivo, grafoCidades);
    geradorCaminhos->setGrafo(grafoCidades);
}

void PainelDeControle::on_btConectarHost_clicked()
{
    sc = new SocketClient(this);
    sc->conectar(ui->edtEnderecoHost->text(), ui->edtNumeroPorta->text().toInt());
    connect(sc, SIGNAL(aoReceberMensagemServidorTCP(QString)), this, SLOT(aoReceberMensagemServidorTCP(QString)));
}

void PainelDeControle::on_btEnviarMensagemClienteServidor_clicked()
{
    if (!sc)
        return;
    sc->escrever(ui->edtNovaMensagemCliente->text());
    ui->edtMensagensEnviadasCliente->appendPlainText(ui->edtNovaMensagemCliente->text());
    ui->edtNovaMensagemCliente->setText("");
}

void PainelDeControle::on_edtNovaMensagemCliente_returnPressed()
{
    on_btEnviarMensagemClienteServidor_clicked();
}
