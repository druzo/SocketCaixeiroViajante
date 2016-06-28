#include "sockettcpserver.h"

SocketTcpServer::SocketTcpServer(PCVAG *pCVAG, QList<ResultadoTSP *> *listaResultados, QObject *parent ):QTcpServer(parent)
{
    this->listaResultados = listaResultados;
    this->pCVAG = pCVAG;
}

void SocketTcpServer::iniciarServidor()
{
    int porta = 55555;

    if(!this->listen(QHostAddress::Any, porta))
    {
        qDebug() << "Não foi possível iniciar o servidor";
    }
    else
    {
        qDebug() << "Escutando na porta: " << porta << "...";
    }
}

void SocketTcpServer::aoEstabelecerConexaoCliente(ServerClient *cliente)
{
    emit aoConectarNovoCliente(cliente);
}

#if defined(_WIN32 ) || defined(Q_OS_OSX)
void SocketTcpServer::incomingConnection(qintptr socketDescriptor)
#else
void SocketTcpServer::incomingConnection(int socketDescriptor)
#endif
{
//     We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    ServerClient *conexaoCliente = new ServerClient(this->pCVAG, this->listaResultados, socketDescriptor, this);
    connect(conexaoCliente, SIGNAL(aoEstabelecerConexao(ServerClient*)), this, SLOT(aoEstabelecerConexaoCliente(ServerClient*)));
    //quando o objeto de conexão não é mais necessário, apaga o mesmo da memória
    //connect(conexaoCliente, SIGNAL(finished()), conexaoCliente, SLOT(deleteLater()));
    conexaoCliente->conectarCliente();
    emit aoConectarNovoCliente(conexaoCliente);
}
