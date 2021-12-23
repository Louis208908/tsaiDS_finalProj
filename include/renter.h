#ifndef __renter_H
#define __renter_H

#include "bits/stdc++.h"


#define hashKey(data, hashFcn) ((data)% (hashFcn))

using namespace std;

class user{
public:
    class hashTable *hTable;
    user();
    void insert(int stationId, string user_id, string bikeType, int bikeId,int rentTime);
    class node *findUser(string user_id);
};

class hashTable{
public:
    int hashFcn;
    class node **user_info;
    hashTable(int hashFcn);
    
};

class node{
    public:
    class node *next;
    string user_id;
    int bikeId;
    int station_id;
    int rentTime;
    string bikeType;
    node(int stationId, string user_id, string bikeType, int bikeId,int rentTime);
    static node* insert(node* root,int stationId ,string user_id, string bikeType, int bikeId,int rentTime);
};

#endif
