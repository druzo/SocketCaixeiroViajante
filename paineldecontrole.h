#ifndef PAINELDECONTROLE_H
#define PAINELDECONTROLE_H

#include <QMainWindow>
#include "sockettcpserver.h"
namespace Ui {
class PainelDeControle;
}

class PainelDeControle : public QMainWindow
{
    Q_OBJECT

public:
    explicit PainelDeControle(QWidget *parent = 0);
    ~PainelDeControle();

private slots:
    void on_pushButton_clicked();
    void aoReceberMensagem(QTcpSocket *cliente, QByteArray dados);
    void aoConectarNovoCliente(ServerClient *cliente);
private:
    Ui::PainelDeControle *ui;
    SocketTcpServer *socketTcpServer;
};

#endif // PAINELDECONTROLE_H
