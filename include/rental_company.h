#ifndef __rental_company_H
#define __rental_company_H

#include "bits/stdc++.h"
#include "map.h"
#include "renter.h"
#include "bike.h"
#include <fstream>
#include <climits>
#include <cmath>


using namespace std;

class rental_company{


public:
    string most_expensive_type;
    int revenue;
    int total_rent_request;
    class map_info **map;
    rental_company(class map_info** map);
    class station **station_info;
    class user *user_info_manager;
    static int totalBikeInventory;
    void bikeAmountInit(ifstream &stationStream);
    void showQuota();
    static string rent_handling(rental_company *company, int stationId, string userId, string bikeType, int rentTime);
    static void return_handling(rental_company *company, int stationId, string userId, int returnTime);
    static int calculating_fee(rental_company *company, int rentStation, int returnStation, string bikeType);
};

class station{
    public:
        // friend class rental_company;
        // int electric_amount;
        // int lady_amount;
        // int road_amount;
        int station_id;
        class electric *electric_manager;
        class lady *lady_manager;
        class road *road_manager;
        int total_rent_amount;
        // class BIKE *electric_manager;
        // class BIKE *lady_manager;
        // class BIKE *road_manager;
        station(int station_id, int elec, int lady, int road);
        void bikeRegistering();
};





#endif
