#include <iostream>
#include "pi.h"

using namespace std;

int main()
{

    Pi pi = Pi();

    int parts=1000000000;
    int seeds=100000000;

    cout << "-------- integralSingleThread --------" << endl;
    pi.integralSingleThread(parts);

    cout << "-------- integralMultiThreadedReduction --------" << endl;
    pi.integralMultiThreadedReduction(parts);

    cout << "-------- integralMultiThreadedSequential --------" << endl;
    pi.integralMultiThreadedSequential(parts);

    cout << "-------- integralMultiThreadedNonSequential --------" << endl;
    pi.integralMultiThreadedNonSequential(parts);

    cout << "-------- moneteCarloSingleThread --------" << endl;
    pi.moneteCarloSingleThread(seeds);

    cout << "-------- moneteCarloMultiThreadReduction --------" << endl;
    pi.moneteCarloMultiThreadReduction(seeds);

    cout << "-------- moneteCarloMultiThread --------" << endl;
    pi.moneteCarloMultiThread(seeds);


    return 0;
}

// export OMP_NUM_THREADS=8
// g++ main.cpp pi.cpp -o test.o -fopenmp -lpthread -std=c++11
