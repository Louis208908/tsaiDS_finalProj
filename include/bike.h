#ifndef __bike_H
#define __bike_H

#include "bits/stdc++.h"

using namespace std;

/**
 * @brief 
 * 
 */
class BIKE{
    public:
      BIKE(int amount);
        /**
         * @brief the maximum capacity of a certain type of bike aka heap capacity
         * 
         */
        int quota;
        /**
         * @brief the actual amount of bike inside storehouse aka heap_size
         * 
         */
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
