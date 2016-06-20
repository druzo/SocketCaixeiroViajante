#include "serverclient.h"

ServerClient::ServerClient(qintptr ID, QObject *parent): QThread(parent)
{
    socket = NULL;
    if (ID)
        this->socketDescriptor = ID;
}

void ServerClient::run()
{
    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // Mostrando no console qual cliente está conectado
    qDebug() << socketDescriptor << " Está Conectado com o ip:"<< socket->peerAddress().toString();

    //fazendo a thread entrar em loop
    //esse comando é necessário para que a thread
    //possa capturar os eventos signal/slot

    exec();
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
    return socket;
}

QTcpSocket *ServerClient::conectarCliente(QString enderecoIP, qint16 porta)
{
    // thread starts here
    qDebug() << " Iniciou uma thread de conexão com o servidor";
    socket = new QTcpSocket();
    socket->connectToHost(enderecoIP, porta);
    // verifica se é um descritor válido
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // Aconteceu algum problema, emitindo o erro
        emit serverClientErro(socket->error());
        return NULL;
    }
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

    socket->write(dados);

    emit aoReceberMensagem(socket, dados);
}

void ServerClient::disconnected()
{
    qDebug() << socketDescriptor << "IP:"<< socket->peerAddress().toString()<< " Desconectou";

    socket->deleteLater();
    exit(0);
}

