// AUTHOR:   Shunuo Chen
// FILENAME: lab5.cpp
// DATE:     11/06/2022
// PURPOSE:  This program will measure and graph the
//           runtimes of various sorting algorithms.
// INPUT:    Number of random numbers used to sort
// PROCESS:  generate random numbers to store in vector and sort them with
//           heap sort, insertion sort, merge sort, quick sort, and IntroSort
// OUTPUT:   display time consumed using these sort functions
#include <iostream>
#include <vector>
#include <time.h>
#include "Sort.h"

void runtimeOfSorts(int SIZE, int MAX_SIZE);
// test the run time of various sorts
// IN: SIZE and MAX_SIZE of the vector
// MODIFY: none
// OUT: the consuming time

using namespace std;
int main() {
    //initialize the SIZE of the vector
    const int SIZE = 40000;
    //initialize the maximum size of the vector
    const int MAX_SIZE = 20480000;

    //test the runtime of sorts with
    for (int i = SIZE; i <= MAX_SIZE ; i *=2 ) {
        runtimeOfSorts(i, MAX_SIZE);
    }
    return 0;
}

void runtimeOfSorts(int SIZE, int MAX_SIZE) {
    //make sure size of the vector is less than 20,480,000
    if (SIZE > MAX_SIZE) {
        return;
    }
    //create an instance of vector with long and initialize the size to
    //40000 with 0 of all elements
    vector<long> V (SIZE, 0);
    cout << "sorting "<< SIZE << " values...\n";

    //generate random number stored them in the vector
    generate(V.begin(), V.end(), rand);
    cout << "First generate: ";
    for (int i = 0; i < 4; i++) {
        cout << V[i] << " ";
    }
    //initialize clock time t
    clock_t t1 = clock();
    //test the quick sort
    quicksort(V.begin(), V.end());
    //get the quick sort time.
    t1 = clock() - t1;
    printf("It took me %d clocks (%.2f seconds) for Quicksort.\n", (int)t1,
           (float)(t1) / CLOCKS_PER_SEC);
    //initialize clock time t
    clock_t t2 = clock();

    generate(V.begin(), V.end(), rand);
    cout << "Second generate: ";
    for (int i = 0; i < 4; i++) {
        cout << V[i] << " ";
    }

    //test the quick sort
    heapsort(V.begin(), V.end());
    //get the quick sort time.
    t2 = clock() - t2;
    printf("It took me %d clocks (%.2f seconds) for Heapsort.\n", (int)t2,
           (float)(t2) / CLOCKS_PER_SEC);
    //initialize clock time t
    clock_t t3 = clock();
    generate(V.begin(), V.end(), rand);
    //test the quick sort
    mergesort(V.begin(), V.end());
    //get the quick sort time.
    t3 = clock() - t3;
    printf("It took me %d clocks (%.2f seconds) for Mergesort.\n", (int)t3,
           (float)(t3) / CLOCKS_PER_SEC);
    //initialize clock time t
    clock_t t4 = clock();
    //generate new random numbers
    generate(V.begin(), V.end(), rand);
    //test the quick sort
    sort(V.begin(), V.end());
    //get the quick sort time.
    t4 = clock() - t4;
    printf("It took me %d clocks (%.2f seconds) for STL's IntroSort.\n", (int)t4,
           (float)(t4) / CLOCKS_PER_SEC);

    //make sure the insertion sort does not sort more than 640000 numbers
    if (SIZE <= 640000) {
        clock_t t5 = clock();
        generate(V.begin(), V.end(), rand);
        //test the quick sort
        insertionSort(V.begin(), V.end());
        //get the quick sort time.
        t5 = clock() - t5;
        printf("It took me %d clocks (%.2f seconds) for Insertion Sort.\n\n",
               (int) t5, (float) (t5) / CLOCKS_PER_SEC);
    }
    //display the error message when the size is too big
    else {
        cout << "We do not test the size is lager than 640,000 for insertion"
                " sort\n\n";
    }
}