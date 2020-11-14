#include "parallelmatrix.h"

int matrix[sizeX][sizeY];

ParallelMatrix::ParallelMatrix()
{
    numberElements = 43333333;
    logicThreads = 8;
    maxThreads = logicThreads;
}

int ParallelMatrix::getNumberElemets()
{
    return numberElements;
}

void ParallelMatrix::setNumberElements(int value)
{
    numberElements = value;
}

int ParallelMatrix::getLogicThreads()
{
    return logicThreads;
}

void ParallelMatrix::setLogicThreads(int value)
{
    logicThreads = value;
    maxThreads = logicThreads;
}

long long ParallelMatrix::generateMatrix()
{
    QElapsedTimer timer;
    timer.start();
    mt19937 generate(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<> rnd(0, 9);

    for (int i=0; i<sizeX; i++)
        for (int j=0; j<sizeY; j++)
            matrix[i][j] = rnd(generate);

    QFile output("GeneratedMatrix.txt");
    output.open(QIODevice::WriteOnly);
    QTextStream out(&output);
    for (int i=0; i<sizeX; i++)
    {
        for (int j=0; j<sizeY; j++)
        {
            out << matrix[i][j];
            if (j < sizeY - 1)
                out << "\t";
        }
        out << "\n";
    }
    output.close();
    long long time = timer.elapsed();
    return time;
}

threadResult ParallelMatrix::sumSingleThread()
{
    QElapsedTimer timer;
    int matrixSum = 0;
    int *matrixPtr = matrix[0];
    cout << endl << "Single Thread" << endl;
    double startTime, finishTime;
    timer.start();
    startTime = omp_get_wtime();
    //sum(matrixPtr, 0, sizeX*sizeY, ref(lms));
//    for (int i=0; i<sizeX; i++)
//        for (int j=0; j<sizeY; j++)
//            matrixSum += matrix[i][j];
    for (int i=0; i<sizeX*sizeY; i++)
        matrixSum += matrixPtr[i];
    finishTime = omp_get_wtime();
    long long time = timer.elapsed();
//    cout << "Matrix Sum Single Thread = " << matrixSum << endl;
//    cout << "Elapsed Time = " << time << " ms" << endl;
    threadResult res;
    res.countSum = matrixSum;
    res.resultTime = time;
    res.usedTreads = 1;
    res.timeForOMP = finishTime - startTime;
    return res;
}

threadResult ParallelMatrix::sumTwoThreads()
{
    QElapsedTimer timer;
    int matrixSum = 0;
    int *matrixPtr = matrix[0];
    int blocksize = sizeX*sizeY / 2;
    cout << endl << "Two Threads" << endl;
    //sum(matrixPtr, 0, sizeX*sizeY, ref(lms));
//    for (int i=0; i<sizeX*sizeY; i++)
//        matrixSum += matrixPtr[i];

    int localSum;
    int threadNum;
    double startTime, finishTime;
    timer.start();
    startTime = omp_get_wtime();
#pragma omp parallel num_threads(2) private (localSum, threadNum) shared (matrixSum, matrixPtr, blocksize)
    {
        localSum = 0;
        threadNum = omp_get_thread_num();

        for (int i=threadNum * blocksize; i<(threadNum + 1) * blocksize; i++)
            localSum += matrixPtr[i];
#pragma omp atomic
        matrixSum += localSum;
#pragma omp critical
        {
            cout << "Thread " << threadNum << " : " << matrixSum << endl;
        }
    }
    finishTime = omp_get_wtime();

    long long time = timer.elapsed();
//    cout << "Matrix Sum Single Thread = " << matrixSum << endl;
//    cout << "Elapsed Time = " << time << " ms" << endl;
    threadResult res;
    res.countSum = matrixSum;
    res.resultTime = time;
    res.usedTreads = 2;
    res.timeForOMP = finishTime - startTime;
    return res;
}

threadResult ParallelMatrix::sumLogicThreads()
{
    QElapsedTimer timer;
    int matrixSum = 0;
    int *matrixPtr = matrix[0];
    int blocksize = sizeX*sizeY / logicThreads;
    cout << endl << "Logic Threads" << endl;
    //sum(matrixPtr, 0, sizeX*sizeY, ref(lms));
//    for (int i=0; i<sizeX*sizeY; i++)
//        matrixSum += matrixPtr[i];

    int localSum;
    int threadNum;
    double startTime, finishTime;
    timer.start();
    startTime = omp_get_wtime();
#pragma omp parallel num_threads(logicThreads) private (localSum, threadNum) shared (matrixSum, matrixPtr, blocksize)
    {
        localSum = 0;
        threadNum = omp_get_thread_num();

        for (int i=threadNum * blocksize; i<(threadNum + 1) * blocksize; i++)
            localSum += matrixPtr[i];
#pragma omp atomic
        matrixSum += localSum;
#pragma omp critical
        {
            cout << "Thread " << threadNum << " : " << matrixSum << endl;
        }
    }
    finishTime = omp_get_wtime();

    long long time = timer.elapsed();
//    cout << "Matrix Sum Single Thread = " << matrixSum << endl;
//    cout << "Elapsed Time = " << time << " ms" << endl;
    threadResult res;
    res.countSum = matrixSum;
    res.resultTime = time;
    res.usedTreads = logicThreads;
    res.timeForOMP = finishTime - startTime;
    return res;
}

threadResult ParallelMatrix::sum2LogicThreads()
{
    int localLogicThreads = 2*logicThreads;
    QElapsedTimer timer;
    int matrixSum = 0;
    int *matrixPtr = matrix[0];
    int blocksize = sizeX*sizeY / localLogicThreads;
    cout << endl << "2xLogic Threads" << endl;
    //sum(matrixPtr, 0, sizeX*sizeY, ref(lms));
//    for (int i=0; i<sizeX*sizeY; i++)
//        matrixSum += matrixPtr[i];

    int localSum;
    int threadNum;
    double startTime, finishTime;
    timer.start();
    startTime = omp_get_wtime();
#pragma omp parallel num_threads(localLogicThreads) private (localSum, threadNum) shared (matrixSum, matrixPtr, blocksize)
    {
        localSum = 0;
        threadNum = omp_get_thread_num();

        for (int i=threadNum * blocksize; i<(threadNum + 1) * blocksize; i++)
            localSum += matrixPtr[i];
#pragma omp atomic
        matrixSum += localSum;
#pragma omp critical
        {
            cout << "Thread " << threadNum << " : " << matrixSum << endl;
        }
    }
    finishTime = omp_get_wtime();

    long long time = timer.elapsed();
//    cout << "Matrix Sum Single Thread = " << matrixSum << endl;
//    cout << "Elapsed Time = " << time << " ms" << endl;
    threadResult res;
    res.countSum = matrixSum;
    res.resultTime = time;
    res.usedTreads = localLogicThreads;
    res.timeForOMP = finishTime - startTime;
    return res;
}
