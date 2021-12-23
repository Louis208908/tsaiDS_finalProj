#ifndef __bike_H
#define __bike_H

#include "bits/stdc++.h"

using namespace std;

class BIKE{
    public:
        BIKE(int amount);
        int quota;
        int residual;
        int *storehouse;
        int regular_fee;
        int discount_fee;
        void insert(int key);
        void heapify(int index);
        int extractMin();
        void printHeap();
        void printHeapToFile();
};

class electric: public BIKE{

public:
    electric(int amount, int regular, int discount);
};

class lady : public BIKE{

public:
    lady(int amount, int regular, int discount);
};

class road : public BIKE{

public:
    road(int amount, int regular, int discount);
};

#endif
