#ifndef PAINELDECONTROLE_H
#define PAINELDECONTROLE_H

#include <QMainWindow>
#include <QList>
#include "sockettcpserver.h"
#include "tsp.h"
#include "geradorcaminhos.h"
namespace Ui {
class PainelDeControle;
}

class PainelDeControle : public QMainWindow
{
    Q_OBJECT

public:
    explicit PainelDeControle(QWidget *parent = 0);
    ~PainelDeControle();
    QList<ResultadoTSP*> *listaTSP;
private slots:
    void on_pushButton_clicked();
    void aoReceberMensagem(QTcpSocket *cliente, QByteArray dados);
    void aoConectarNovoCliente(ServerClient *cliente);    
    void on_btCarregarGrafo_clicked();

private:
    Ui::PainelDeControle *ui;
    SocketTcpServer *socketTcpServer;
    Graph *grafoCidades;
    GeradorCaminhos *geradorCaminhos;
    void carregarArquivoGrafos(QString caminho, Graph *grafo);
};

#endif // PAINELDECONTROLE_H
