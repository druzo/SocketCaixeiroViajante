#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <qhostaddress.h>
//classe responsável por manter a conexão entre o cliente externo com o servidor socket
class ServerClient : public QThread
{
public:
Q_OBJECT

public:
    explicit ServerClient(qintptr ID, QObject *parent);

    void run();
    QTcpSocket *conectarCliente();
    QTcpSocket *conectarCliente(QString enderecoIP, qint16 porta);

    QString getIpCliente();

signals:
    void serverClientErro(QTcpSocket::SocketError socketerror);
    void aoReceberMensagem(QTcpSocket *cliente, QByteArray dados);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // SERVERCLIENT_H
