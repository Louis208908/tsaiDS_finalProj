#ifndef __renter_H
#define __renter_H

#include "bits/stdc++.h"

using namespace std;

class user{
public:
    user();
    void push(int stationId, string user_id, string bikeType, int rentTime);
};

class hashTable{
public:
    int hashFcn;
    class linked_List **user_id;
    hashTable(int hashFcn);
};

class linked_List{
    class linked_List *next;
    string user_id;
    int rentTime;
    string bikeType;
    linked_List();
    class linked_List *findUser(string user_id);
};

#endif
