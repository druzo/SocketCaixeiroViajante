#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
class SocketClient : public QObject
{
    Q_OBJECT
public:
    explicit SocketClient(QObject *parent = 0);
    void conectar(QString enderecoHost, qint16 porta);
    void escrever(QString dados);
signals:
    void aoReceberMensagemServidorTCP(QString mensagem);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
private:
    QTcpSocket *socket;
};

#endif // SOCKETCLIENT_H
