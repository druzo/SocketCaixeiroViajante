#ifndef SOCKETTCPSERVER_H
#define SOCKETTCPSERVER_H
#include <QTcpServer>
#include "serverclient.h"
#include "tsp.h"
#include "pcvag.h"
class SocketTcpServer : public QTcpServer
{
Q_OBJECT
public:
    explicit SocketTcpServer(PCVAG *pCVAG, QList<ResultadoTSP*> *listaResultados,QObject *parent);
    void iniciarServidor();
signals:
    void aoConectarNovoCliente(ServerClient *cliente);
public slots:
    void aoEstabelecerConexaoCliente(ServerClient *cliente);
protected:
#if defined(_WIN32 ) || defined(Q_OS_OSX)
    void incomingConnection(qintptr socketDescriptor);
#else
    void incomingConnection(int socketDescriptor);
#endif
private:
    QList<ResultadoTSP*> *listaResultados;
    PCVAG *pCVAG;
};

#endif // SOCKETTCPSERVER_H
