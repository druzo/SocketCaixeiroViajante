#ifndef SOCKETTCPSERVER_H
#define SOCKETTCPSERVER_H
#include <QTcpServer>
#include "serverclient.h"
class SocketTcpServer : public QTcpServer
{
Q_OBJECT
public:
    explicit SocketTcpServer(QObject *parent);
    void iniciarServidor();
signals:
    void aoConectarNovoCliente(ServerClient *cliente);
public slots:
    void aoEstabelecerConexaoCliente(ServerClient *cliente);
protected:
#ifdef _WIN32
    void incomingConnection(qintptr socketDescriptor);
#else
    void incomingConnection(int socketDescriptor);
#endif
};

#endif // SOCKETTCPSERVER_H
