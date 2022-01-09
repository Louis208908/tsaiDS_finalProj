#ifndef __renter_H
#define __renter_H

// #include "bits/stdc++.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <string>
#include <iostream>
#include <fstream>
#include <climits>

/**
 * @brief  defining our hashFunction
 * 
 */
#define hashKey(data, hashFcn) ((data)% (hashFcn))

using namespace std;

/**
 * @brief the data structure to save  user rent data by using hash \
 *          giving us suffucient speed to find rent history 
 * 
 */
class user{
public:
    class hashTable *hTable;
    user();
    /**
     * @brief  insert a new renting data into our hashTable
     * 
     * @param stationId  the stationId user request
     * @param user_id   user_id
     * @param bikeType  "electruc" "lady" or "road"  given to user, ***might differ fromm request due to policies***
     * @param bikeId  a certain bikeId will be extracted from heap after bikeType is decided
     * @param rentTime  the actual time when user get their bike, ***might differ from request due to policies***
     * @param policy   treatment to user while the required bikeType is unavailable
     */
    void insert(int stationId, string user_id, string bikeType, int bikeId,int rentTime, string policy);

    /**
     * @brief  find the user renting data
     * 
     * @param user_id  find the renting data stored inside hash by a certain userId
     * @return node*   return the user data stored inside hash, including \
     *                  1. userId \
     *                  2. from whichStation\
     *                  3. renting time\
     *                  4. bikeType\
     *                  5. bikeId\
     *                  6. treatment of the user request Ex. wait, change Type\
     */
    class node *findUser(string user_id);
};


/**
 * @brief hashTable is implemmenting by an array of linkedList \
 *        user_info is the head pointer of this array \
 *        user_info[] means the head pointer of the linkedList\
 *        when collision occurs, open-chaining is our solution
 */
class hashTable{
public:
    int hashFcn;
    class node **user_info;
    hashTable(int hashFcn);
    
};

/**
 * @brief  node is the class for implementing linkedList, storing the renting data
 * 
 */
class node{
    public:
        string policy;
        // use to record whether he/she is treated with special operation
        // Ex. wait, change bikeType
        class node *next;
        string user_id;
        int bikeId;
        int station_id;
        int rentTime;
        string bikeType;
        node(int stationId, string user_id, string bikeType, int bikeId, int rentTime, string policy);
        static node *insert(node *root, int stationId, string user_id, string bikeType, int bikeId, int rentTime, string policy);
};

#endif
