#ifndef SOCKETTCPSERVER_H
#define SOCKETTCPSERVER_H
#include <QTcpServer>
#include "serverclient.h"
#include "tsp.h"
class SocketTcpServer : public QTcpServer
{
Q_OBJECT
public:
    explicit SocketTcpServer(QList<ResultadoTSP*> *listaResultados,QObject *parent);
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
private:
    QList<ResultadoTSP*> *listaResultados;
};

#endif // SOCKETTCPSERVER_H
