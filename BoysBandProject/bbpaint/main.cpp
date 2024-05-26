#include "bbproject.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("fusion"));
    BBproject w;
    w.show();
    return a.exec();
}
