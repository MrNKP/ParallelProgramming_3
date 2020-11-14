#include "parallelprogram.h"
#include "ui_parallelprogram.h"

ParallelProgram::ParallelProgram(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParallelProgram)
{
    ui->setupUi(this);
    ui->maxElementsPerThreadSpinBox->setValue(parmatrix.getNumberElemets());
    ui->logicThreadSpinBox->setValue(parmatrix.getLogicThreads());
    ui->startSingleThreadPushButton->setEnabled(false);
    ui->startTwoThreadsPushButton->setEnabled(false);
    ui->startLogicThreadsPushButton->setEnabled(false);
    ui->start2xLogicThreadsPushButton->setEnabled(false);
    ui->startDynamicThreadsPushButton->setEnabled(false);
    ui->matrixInfoLabel->setText(ui->matrixInfoLabel->text() +
                                 QString::number(sizeX) + "*" + QString::number(sizeY));
}

ParallelProgram::~ParallelProgram()
{
    delete ui;
}

void ParallelProgram::on_generatePushButton_clicked()
{
    long long time;
    time = parmatrix.generateMatrix();
    ui->matrixGenerationTimeLabel->setText(QString::number(time) + " ms");
    ui->generatedCheckBox->setChecked(true);
    ui->startSingleThreadPushButton->setEnabled(true);
    ui->startTwoThreadsPushButton->setEnabled(true);
    ui->startLogicThreadsPushButton->setEnabled(true);
    ui->start2xLogicThreadsPushButton->setEnabled(true);
    ui->startDynamicThreadsPushButton->setEnabled(true);
}

void ParallelProgram::on_startSingleThreadPushButton_clicked()
{
    threadResult ThreadResult;
    ThreadResult = parmatrix.sumSingleThread();
    ui->resultTableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(ThreadResult.countSum)));
    ui->resultTableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(ThreadResult.usedTreads)));
    ui->resultTableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(ThreadResult.resultTime) + " ms"));
    ui->resultTableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(ThreadResult.timeForOMP * 1000) + " ms"));
}

void ParallelProgram::on_startTwoThreadsPushButton_clicked()
{
    threadResult ThreadResult;
    ThreadResult = parmatrix.sumTwoThreads();
    ui->resultTableWidget->setItem(1, 0, new QTableWidgetItem(QString::number(ThreadResult.countSum)));
    ui->resultTableWidget->setItem(1, 1, new QTableWidgetItem(QString::number(ThreadResult.usedTreads)));
    ui->resultTableWidget->setItem(1, 2, new QTableWidgetItem(QString::number(ThreadResult.resultTime) + " ms"));
    ui->resultTableWidget->setItem(1, 3, new QTableWidgetItem(QString::number(ThreadResult.timeForOMP * 1000) + " ms"));
}

void ParallelProgram::on_startLogicThreadsPushButton_clicked()
{
    threadResult ThreadResult;
    ThreadResult = parmatrix.sumLogicThreads();
    ui->resultTableWidget->setItem(2, 0, new QTableWidgetItem(QString::number(ThreadResult.countSum)));
    ui->resultTableWidget->setItem(2, 1, new QTableWidgetItem(QString::number(ThreadResult.usedTreads)));
    ui->resultTableWidget->setItem(2, 2, new QTableWidgetItem(QString::number(ThreadResult.resultTime) + " ms"));
    ui->resultTableWidget->setItem(2, 3, new QTableWidgetItem(QString::number(ThreadResult.timeForOMP * 1000) + " ms"));
}

void ParallelProgram::on_maxElementsPerThreadSpinBox_valueChanged(int arg1)
{
    parmatrix.setNumberElements(arg1);
}

void ParallelProgram::on_logicThreadSpinBox_valueChanged(int arg1)
{
    parmatrix.setLogicThreads(arg1);
}

void ParallelProgram::on_start2xLogicThreadsPushButton_clicked()
{
    threadResult ThreadResult;
    ThreadResult = parmatrix.sum2LogicThreads();
    ui->resultTableWidget->setItem(3, 0, new QTableWidgetItem(QString::number(ThreadResult.countSum)));
    ui->resultTableWidget->setItem(3, 1, new QTableWidgetItem(QString::number(ThreadResult.usedTreads)));
    ui->resultTableWidget->setItem(3, 2, new QTableWidgetItem(QString::number(ThreadResult.resultTime) + " ms"));
    ui->resultTableWidget->setItem(3, 3, new QTableWidgetItem(QString::number(ThreadResult.timeForOMP * 1000) + " ms"));
}
