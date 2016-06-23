#include "socketclient.h"

SocketClient::SocketClient(QObject *parent) : QObject(parent)
{

}

void SocketClient::conectar(QString enderecoHost, qint16 porta)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "Socket Client iniciando a conexão...";

    socket->connectToHost(enderecoHost, porta);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        qCritical() << "Erro ao tentar conectar: " << socket->errorString();
    }
}

void SocketClient::escrever(QString dados)
{
    if(socket->isOpen())
        socket->write(dados.toLatin1());
    else{
        qCritical()<<"Socket Client não se encontra conectado a nenhum servidor.";
        return;
    }
}

void SocketClient::connected()
{
    qDebug() << "Socket Client Conectou...";
}

void SocketClient::disconnected()
{
    qDebug() << "Socket Client desconectou...";
}

void SocketClient::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes enviados...";
}

void SocketClient::readyRead()
{
    qDebug() << "lendo dados...";

    emit aoReceberMensagemServidorTCP(socket->readAll());
    // dados lidos do socket
    //qDebug() << socket->readAll();
}

