#include "paineldecontrole.h"
#include "ui_paineldecontrole.h"
#include <QTcpSocket>
#include <serverclient.h>



PainelDeControle::PainelDeControle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PainelDeControle)
{
    ui->setupUi(this);
    listaTSP = new QList<ResultadoTSP*>();
    Graph * graph4 = new Graph(50, 0, true);
    graph4->showInfoGraph();
    Genetic genetic(graph4, 10, 1000, 5, true);
    listaTSP->append(genetic.run());
    qDebug()<<"resultado:" <<listaTSP->at(0)->caminhos<< " custo:"<<listaTSP->at(0)->custo;
    socketTcpServer = new SocketTcpServer(this);
    connect(socketTcpServer, SIGNAL(aoConectarNovoCliente(ServerClient*)), this, SLOT(aoConectarNovoCliente(ServerClient*)));
    connect(socketTcpServer,SIGNAL(newConnection()), this, SLOT(newConnection()));
}

PainelDeControle::~PainelDeControle()
{
    delete ui;
}

void PainelDeControle::on_pushButton_clicked()
{
    socketTcpServer->iniciarServidor();
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
