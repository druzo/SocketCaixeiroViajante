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

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SOCKETTCPSERVER_H
