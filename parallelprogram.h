#ifndef PARALLELPROGRAM_H
#define PARALLELPROGRAM_H

#include <QMainWindow>

#include "parallelmatrix.h"

namespace Ui {
class ParallelProgram;
}

class ParallelProgram : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParallelProgram(QWidget *parent = nullptr);
    ~ParallelProgram();

private slots:
    void on_generatePushButton_clicked();

    void on_startSingleThreadPushButton_clicked();

    void on_startTwoThreadsPushButton_clicked();

    void on_startLogicThreadsPushButton_clicked();

    void on_maxElementsPerThreadSpinBox_valueChanged(int arg1);

    void on_logicThreadSpinBox_valueChanged(int arg1);

    void on_start2xLogicThreadsPushButton_clicked();

private:
    Ui::ParallelProgram *ui;
    ParallelMatrix parmatrix;
};

#endif // PARALLELPROGRAM_H
