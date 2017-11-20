#include <chrono>
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <limits.h>
#include <random>
#include <ctime>
#include <algorithm>

#define swap(a,b) {int tmp = a; a = b; b = tmp;}


using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point start, finish;
duration<double> dtime;

void turnOffScientificNotation(){
    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
    cout.precision(10);
}


void turnOffScientificNotationWithPrecision2(){
    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
    cout.precision(2);
}

void oddEvenSort(int dataSize, int tab[]) {
    bool changed = true;
    
    while(changed){
        
        changed = false;
        
        for(int i=1; i<dataSize-1; i+=2){
            if(tab[i] > tab[i+1] ) {
                swap(tab[i], tab[i+1]);
                changed = true;
            }
        }
        
        for(int i=0; i<dataSize-1; i+=2){
            if(tab[i] > tab[i+1] ) {
                swap(tab[i], tab[i+1]);
                changed = true;
            }
        }
    }
}

void oddEvenSortParallel(int dataSize, int tab[]){
    int changes;
    
    while(changes){
        
        #pragma omp parallel
        {
            changes = 0;
            #pragma omp for reduction(+:changes)
            for(int i = 0; i < dataSize - 1; i = i + 2) {
                if(tab[i] > tab[i+1] ) {
                    swap(tab[i], tab[i+1]);
                    changes++;
                }
            }
            #pragma omp for reduction(+:changes)
            for(int i = 1; i < dataSize - 1; i = i + 2) {
                if( tab[i] > tab[i+1] ) {
                    swap(tab[i], tab[i+1]);
                    changes++;
                }
            }
        }
    }
}

int qsPartition(int tab[], int low, int high){
    int i = low, j = high+1;
    int pivot = tab[low];
    
    while(1) {
        while (tab[++i] < pivot)
            if(i==high)
                break;
        while (tab[--j] > pivot)
            if(j==low)
                break;
        
        if(i >= j)
            break;
        
        swap(tab[i], tab[j]);
    }
    swap(tab[low], tab[j]);
    return j;
}

void quickSort(int tab[], int low, int high){
    if (high <= low)
        return;
    
    int pivot = qsPartition(tab, low, high);

    quickSort(tab, low, pivot-1);
    quickSort(tab, pivot+1, high);
}

void quickSortParallel(int tab[], int low, int high){
    
    if (high <= low)
        return;
    
    int pivot = qsPartition(tab, low, high);
 
    #pragma omp parallel sections
    {   
        #pragma omp section
        quickSort(tab, low, pivot-1);
        #pragma omp section
        quickSort(tab, pivot+1, high);
    }
}

int main() {
	
    int dataSize = 100000, tab[dataSize], tab_copy[dataSize];
    double t_oddeven, t_oddevenParallel, t_quick, t_quickParallel;
    
    srand(time(NULL));
    
    for(int i=0; i< dataSize; i++){
        tab[i] = rand() % 10000;
    }
    
    int min = tab[0];
    int max = tab[0];
    for(int i=0; i< dataSize; i++){
        if (min > tab[i])
            min=tab[i];
        if (max < tab[i])
            max=tab[i];
    }
    
    cout << "Min / Max: " << min << " / " << max << endl;
    cout << "Data size: " << dataSize << endl << endl;
    
    turnOffScientificNotation();

    // #######################################################################
    
    cout << "-------- oddEvenSort --------" << endl;
    copy_n(tab, dataSize, tab_copy);
    start = high_resolution_clock::now();
    
    oddEvenSort(dataSize, tab_copy);
    
    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);
    cout << "Min / Max: " << tab_copy[0] << "  "  << tab_copy[dataSize-1] << endl;
    t_oddeven = dtime.count();
    cout << "Time elapsed: " << t_oddeven << endl << endl;
    
    // #######################################################################
    
    cout << "-------- oddEvenSortParallel --------" << endl;
    copy_n(tab, dataSize, tab_copy);
    start = high_resolution_clock::now();
    
    oddEvenSortParallel(dataSize, tab_copy);
    
    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);
    cout << "Min / Max: " << tab_copy[0] << "  "  << tab_copy[dataSize-1] << endl;
    t_oddevenParallel = dtime.count();
    cout << "Time elapsed: " << t_oddevenParallel << endl << endl;

    // #######################################################################
    
    cout << "-------- quickSort --------" << endl;
    copy_n(tab, dataSize, tab_copy);
    start = high_resolution_clock::now();
    
    quickSort(tab_copy, 0, dataSize-1);
    
    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);
    cout << "Min / Max: " << tab_copy[0] << "  "  << tab_copy[dataSize-1] << endl;
    t_quick = dtime.count();
    cout << "Time elapsed: " << t_quick << endl << endl;
   
    // #######################################################################
    
    cout << "-------- quickSortParallel --------" << endl;
    copy_n(tab, dataSize, tab_copy);
    start = high_resolution_clock::now();
    
    quickSortParallel(tab_copy, 0, dataSize-1);
    
    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);
    cout << "Min / Max: " << tab_copy[0] << "  "  << tab_copy[dataSize-1] << endl;
    t_quickParallel = dtime.count();
    cout << "Time elapsed: " << t_quickParallel << endl << endl;
    
    // #######################################################################
    
    turnOffScientificNotationWithPrecision2();
    
    cout << "----------------------------------------------------------\n\n";
    
    cout << "odd-even sort: parallel " << (t_oddeven/t_oddevenParallel) << " times faster than sequential" << endl;
    cout << "quick sort: parallel " << (t_quick/t_quickParallel) << " times faster than sequential" << endl;
    
    return 0;
}
