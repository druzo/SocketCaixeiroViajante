#include "serverclient.h"


#ifdef _WIN32
ServerClient::ServerClient(QList<ResultadoTSP*> *listaResultados,qintptr ID, QObject *parent): QObject(parent)
#else
ServerClient::ServerClient(QList<ResultadoTSP*> *listaResultados, int ID, QObject *parent): QObject(parent)
#endif

{
    socket = NULL;
    if (ID)
        this->socketDescriptor = ID;
    QThreadPool::globalInstance()->setMaxThreadCount(5);
    this->listaResultados = listaResultados;
}

QTcpSocket *ServerClient::conectarCliente()
{
    // thread starts here
    qDebug() << " Iniciou uma thread de conexão com o servidor";
    socket = new QTcpSocket();

    // verifica se é um descritor válido
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // Aconteceu algum problema, emitindo o erro
        emit serverClientErro(socket->error());
        return NULL;
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    socket->write("Bem vindo ao nosso servidor!\n");
    return socket;
}

QTcpSocket *ServerClient::conectarCliente(QString enderecoIP, qint16 porta)
{
    // thread starts here
    qDebug() << " Iniciou uma thread de conexão com o servidor";
    socket = new QTcpSocket();
    socket->connectToHost(enderecoIP, porta);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    return socket;
}

QString ServerClient::getIpCliente()
{
    if (socket)
        return socket->peerAddress().toString();
    else
        return "sem ip";
}

void ServerClient::readyRead()
{
    // get the information
    QByteArray dados = socket->readAll();

    // will write on server side window
    qDebug() << socketDescriptor << "IP:" << socket->peerAddress().toString() << " Dados: " << dados;
    QString mensagem = dados;
    TarefaResultadoCaxeiroViajante *tarefaRCV = new TarefaResultadoCaxeiroViajante(this->listaResultados, mensagem);
    tarefaRCV->setAutoDelete(true);
    connect(tarefaRCV, SIGNAL(resultado(QString)), this, SLOT(resultado(QString)), Qt::QueuedConnection);
    qDebug()<< "Iniciando nova tarefa no pool de thread";
    QThreadPool::globalInstance()->start(tarefaRCV);
    emit aoReceberMensagem(socket, dados);
}

void ServerClient::disconnected()
{
    qDebug() << socketDescriptor << "IP:"<< socket->peerAddress().toString()<< " Desconectou";
    socket->deleteLater();
   // exit(0);
}

void ServerClient::connected()
{
    qDebug() << "Cliente conectado...";
    emit aoEstabelecerConexao(this);
}

void ServerClient::resultado(QString dados)
{
    QByteArray buffer;
    buffer.append(dados);
    socket->write(buffer);
}

QTcpSocket *ServerClient::getSocket() const
{
    return socket;
}

