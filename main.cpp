#include "super_kulky.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SuperKulky w;
    w.show();

    return a.exec();
}
