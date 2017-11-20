#include <chrono>
#include <iostream>
#include <omp.h>
#include <math.h>
#include <limits.h>
#include <random>
#include "pi.h"

#define RAND_MIN -(RAND_MAX-1000)

using namespace std;
using namespace std::chrono;

Pi::Pi() {}
Pi::~Pi() {}

high_resolution_clock::time_point start, finish;
duration<double> dtime;

double function(double x) {
    return 1.0 / (1 + x * x);
}

void Pi::integralSingleThread(int parts = 100000) {

    // pi = 4*integral[0; 1] (1 / (1 + x^2))

    start = high_resolution_clock::now();

    double dx = 1.0/parts;
    double area = 0;

    for(int i=0; i<parts; i++) {
        area += function( i * dx ) * dx;
    }

    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);

    cout << "Parts: " << parts << endl;
    cout << "Pi: " << area*4 << endl;
    cout << "Time elapsed: " << dtime.count() << endl << endl;

}

void Pi::integralMultiThreadedReduction(int parts = 100000) {

    // pi = 4*integral[0; 1] (1 / (1 + x^2))

    start = high_resolution_clock::now();

    double dx = 1.0/parts;
    double area = 0;

    #pragma omp parallel for reduction(+:area)
    for(unsigned int i=0; i<parts; i++) {
        area += function( i * dx ) * dx;
    }

    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);

    cout << "Parts: " << parts << endl;
    cout << "Pi: " << area*4 << endl;
    cout << "Time elapsed: " << dtime.count() << endl << endl;

}

void Pi::integralMultiThreadedNonSequential(int parts) {

    start = high_resolution_clock::now();

    double dx = 1.0/parts;
    double area = 0;

    const int threadMax = omp_get_max_threads();
    double array[threadMax];

    for (int i = 0; i< threadMax; i++) {
        array[i] = 0;
    }

    #pragma omp parallel
    {
        int threadNum = omp_get_thread_num();
		int max_t = omp_get_max_threads();
        for (int i = threadNum; i < parts; i += max_t) {
            array[threadNum] += function(i * dx) * dx;
        }
    }

    for (int i = 0; i< threadMax; i++) {
        area += array[i];
    }

    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);

    cout << "Parts: " << parts << endl;
    cout << "Pi: " << area*4 << endl;
    cout << "Time elapsed: " << dtime.count() << endl << endl;
}

void Pi::integralMultiThreadedSequential(int parts) {

    start = high_resolution_clock::now();

    double dx = 1.0/parts;
    double area = 0;

    const int threadMax = omp_get_max_threads();
    double array[threadMax];

    for (unsigned int i = 0; i< threadMax; i++) {
        array[i] = 0;
    }

    #pragma omp parallel
    {
        int threadNum = omp_get_thread_num();
        for (int i = threadNum * parts/threadMax; i < (threadNum+1)*parts/threadMax; i++) {
            array[omp_get_thread_num()] += function(i * dx) * dx;
        }
    }


    for (int i = 0; i< threadMax; i++) {
        area += array[i];
    }

    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);

    cout << "Parts: " << parts << endl;
    cout << "Pi: " << area*4 << endl;
    cout << "Time elapsed: " << dtime.count() << endl << endl;
}

void Pi::moneteCarloSingleThread(int seeds = 1000000) {

    start = high_resolution_clock::now();

    double x, y;
    int seedsInCircle = 0;
    for(unsigned int i=0; i< seeds; i++){
        x = rand() / (double)RAND_MAX;
        y = rand() / (double)RAND_MIN;
        if (x*x + y*y < 1) {
            seedsInCircle++;
        }
    }

    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);

    cout << "Seeds: " << seeds << endl;
    cout << "Pi: " << (double)seedsInCircle/seeds * 4 << endl;
    cout << "Time elapsed: " << dtime.count() << endl << endl;
}

void Pi::moneteCarloMultiThreadReduction(int seeds = 1000000) {

    start = high_resolution_clock::now();

    double x, y;
    int seedsInCircle = 0;

    #pragma omp parallel for reduction(+:seedsInCircle)
    for(unsigned int i=0; i< seeds; i++){
        x = rand() / (double)RAND_MAX;
        y = rand() / (double)RAND_MIN;
        if (x*x + y*y < 1) {
            seedsInCircle++;
        }
    }

    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);

    cout << "Seeds: " << seeds << endl;
    cout << "Pi: " << (double)seedsInCircle/(double)seeds * 4 << endl;
    cout << "Time elapsed: " << dtime.count() << endl << endl;
}

void Pi::moneteCarloMultiThread(int seeds = 1000000) {

    start = high_resolution_clock::now();

    double x, y;
    int seedsInCircle = 0;
    const int maxThreads = omp_get_max_threads();
    int array[maxThreads];

    for (int i = 0; i< maxThreads; i++) {
        array[i] = 0;
    }

    #pragma omp parallel
    {
        for (int i = 0; i < seeds/maxThreads; i++) {
            double x = rand()/(double)RAND_MAX;
            double y = rand()/(double)RAND_MAX;

            if (x*x + y*y < 1) {
                array[omp_get_thread_num()]++;
            }
        }
    }

    for (int i = 0; i< maxThreads; i++) {
        seedsInCircle += array[i];
    }

    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);

    cout << "Seeds: " << seeds << endl;
    cout << "Pi: " << (double)seedsInCircle/(double)seeds * 4 << endl;
    cout << "Time elapsed: " << dtime.count() << endl << endl;
}

