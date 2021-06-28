#include "regioni.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Regioni w;
    w.show();

    return a.exec();
}
