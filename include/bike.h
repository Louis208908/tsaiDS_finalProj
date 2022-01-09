#ifndef __bike_H
#define __bike_H

#include "bits/stdc++.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <string>
#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

class BIKE{
    public:
        BIKE(int amount);
        int quota;
        int residual;
        
        /**
         * @brief the actual space where the bikeID has been stored
         * 
         */
        int *storehouse;
        int regular_fee;
        int discount_fee;


        /**
         * @brief use to record how many bike of a certain type has been rent
         * 
         */
        int rent_amount;
        /**
         * @brief use to find out the using rate of a certain type of bike
         * 
         */
        float request_rate;
        void insert(int key);
        void heapify(int index);
        int extractMin();
        void printHeap();
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
