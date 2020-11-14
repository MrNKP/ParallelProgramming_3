#include "parallelprogram.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ParallelProgram w;
    w.show();

    return a.exec();
}
