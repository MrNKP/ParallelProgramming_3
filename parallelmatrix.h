#ifndef PARALLELMATRIX_H
#define PARALLELMATRIX_H

#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QElapsedTimer>

#include <iostream>
#include <thread>
#include <ctime>
#include <random>

#include <omp.h>

using namespace std;

const int sizeX = 1000;
const int sizeY = 1000;

struct threadResult
{
    int countSum;
    long long resultTime;
    unsigned int usedTreads;
    double timeForOMP;
};

class ParallelMatrix
{
    int numberElements;
    int logicThreads;
    int maxThreads;
public:
    ParallelMatrix();

    int getNumberElemets();
    void setNumberElements(int value);

    int getLogicThreads();
    void setLogicThreads(int value);

    long long generateMatrix();
    threadResult sumSingleThread();
    threadResult sumTwoThreads();
    threadResult sumLogicThreads();
    threadResult sum2LogicThreads();
    threadResult sumDynamicThreads();
};

#endif // PARALLELMATRIX_H
