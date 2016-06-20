#include "sockettcpserver.h"

SocketTcpServer::SocketTcpServer(QObject *parent ):QTcpServer(parent)
{

}

void SocketTcpServer::iniciarServidor()
{
    int porta = 1234;

    if(!this->listen(QHostAddress::Any, porta))
    {
        qDebug() << "Não foi possível iniciar o servidor";
    }
    else
    {
        qDebug() << "Escutando na porta: " << porta << "...";
    }
}

void SocketTcpServer::incomingConnection(qintptr socketDescriptor)
{
//     We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    ServerClient *conexaoCliente = new ServerClient(socketDescriptor, this);
    conexaoCliente->conectarCliente();
    // connect signal/slot
    // once a thread is not needed, it will be deleted later
    connect(conexaoCliente, SIGNAL(finished()), conexaoCliente, SLOT(deleteLater()));
    conexaoCliente->start();
    emit aoConectarNovoCliente(conexaoCliente);
}
