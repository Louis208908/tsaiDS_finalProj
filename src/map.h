#ifndef __map_H
#define __map_H

#include "bits/stdc++.h"

using namespace std;

typedef class map_info
{
    private:   
    public:
        friend class rental_commpany;
        int station_id;
        static int station_amount;
        bool* station_adjacency;
        int* distance;
        map_info(int id, int station_amount);
        static void buildMap(ifstream& mapStream, map_info **station);
        static void findMaxId(ifstream& mapStream);
        static void showMap(map_info **station);

}map;

#endif
