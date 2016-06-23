#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QThreadPool>
#include <QTcpSocket>
#include <QDebug>
#include <qhostaddress.h>
#include "tarefaresultadocaxeiroviajante.h"
#include "tsp.h"
//classe responsável por manter a conexão entre o cliente externo com o servidor socket
class ServerClient : public QObject
{
public:
Q_OBJECT

public:
//diretivas de compilação pois no windows o tipo do construtor é diferente
#ifdef _WIN32
    explicit ServerClient(QList<ResultadoTSP*> *listaResultados,qintptr ID, QObject *parent);
#else
    explicit ServerClient(QList<ResultadoTSP*> *listaResultados,int ID, QObject *parent);
#endif
    QTcpSocket *conectarCliente();
    QTcpSocket *conectarCliente(QString enderecoIP, qint16 porta);

    QString getIpCliente();

    QTcpSocket *getSocket() const;

signals:
    void serverClientErro(QTcpSocket::SocketError socketerror);
    void aoReceberMensagem(QTcpSocket *cliente, QByteArray dados);
    void aoEstabelecerConexao(ServerClient *cliente);

public slots:
    void readyRead();
    void disconnected();
    void connected();
    void resultado(QString dados);


private:    
    QTcpSocket *socket;
    QList<ResultadoTSP*> *listaResultados;
//diretivas de compilação pois no windows o tipo do ID é um e no Linux é outro
#ifdef _WIN32
    qintptr socketDescriptor;
#else
    int socketDescriptor;
#endif
};

#endif // SERVERCLIENT_H
