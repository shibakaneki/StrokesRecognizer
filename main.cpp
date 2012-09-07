#include "StrokesRecognizer.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StrokesRecognizer w;
    w.show();
    return a.exec();
}
