#include "paineldecontrole.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PainelDeControle w;
    w.show();

    return a.exec();
}
