#include "prinsipal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Prinsipal w;
    w.show();
    return a.exec();
}
