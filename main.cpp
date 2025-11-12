#include "ccalculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CCalculator w;
    w.show();
    return a.exec();
}
