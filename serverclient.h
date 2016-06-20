#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QThreadPool>
#include <QTcpSocket>
#include <QDebug>
#include <qhostaddress.h>
#include "tarefaresultadocaxeiroviajante.h"
//classe responsável por manter a conexão entre o cliente externo com o servidor socket
class ServerClient : public QObject
{
public:
Q_OBJECT

public:
    explicit ServerClient(qintptr ID, QObject *parent);
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
    qintptr socketDescriptor;
};

#endif // SERVERCLIENT_H
