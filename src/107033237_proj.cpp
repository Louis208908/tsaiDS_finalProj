// g++ -g *.cpp -o 107033237_proj -std=c++11

// #include "bits/stdc。++.h"
#include "stdio.h"
#include "stdlib.h"
// #include "dirent.h"
#include "../include/rental_company.h"
#include "time.h"

using namespace std;

#ifdef TEST
ifstream mapStream("../DS_testcase/open_basic2/test_case/map.txt", ifstream::in);
ifstream stationStream("../DS_testcase/open_basic2/test_case/station.txt", ifstream::in);
ifstream userStream("../DS_testcase/open_basic2/test_case/user.txt", ifstream::in);
ifstream feeStream("../DS_testcase/open_basic2/test_case/fee.txt", ifstream::in);
ofstream requestStream("../DS_testcase/open_basic1/test_case/request.txt", ofstream::out);
ofstream status("../output/part1_status.txt", ofstream::out);
ofstream response("../output/part1_response.txt", ofstream::out);
static ofstream checkStream("../DS_testcase/open_basic1/test_case/check.txt", ofstream::out);
#else
ifstream mapStream("../test_case/map.txt", ifstream::in);
ifstream stationStream("../test_case/station.txt", ifstream::in);
ifstream userStream("../test_case/user.txt", ifstream::in);
ifstream feeStream("../test_case/fee.txt", ifstream::in);
ofstream requestStream("../test_case/request.txt", ofstream::out);
ofstream status("./part1_status.txt", ofstream::out);
ofstream response("./part1_response.txt", ofstream::out);
static ofstream checkStream("../DS_testcase/open_basic1/test_case/check.txt", ofstream::out);
#endif

void fileRefresh();


int map_info::station_amount;
int rental_company::totalBikeInventory;

int main(void) {

    srand(time(0));
    clock_t start = clock();
    fileRefresh();
    map_info::findMaxId(mapStream);
    class map_info *station_info[map_info::station_amount + 1];
    map_info::buildMap(mapStream, station_info);
    map_info::findMinDistance(station_info);

    #ifdef TEST
    map_info::showMap(station_info);
    #endif

    rental_company *company = new rental_company(station_info);

    while(!userStream.eof()){
        string serviceType;
        int station_id;
        string user_id;
        int timeRent;
        int timeReturn;
        string bikeType;
        userStream >> serviceType;
        if (serviceType == "rent") {
            userStream >> station_id;
            userStream >> bikeType;
            userStream >> user_id;
            userStream >> timeRent;
            response << "rent " << station_id << " " << bikeType << " " << user_id << " " << timeRent << endl;
            string resp = rental_company::rent_handling(company, station_id, user_id, bikeType, timeRent);
            response << resp << endl;
        }
        else if(serviceType == "return"){
            userStream >> station_id;
            userStream >> user_id;
            userStream >> timeReturn;
            response << "return " << station_id << " " << user_id << " " << timeReturn << endl;
            rental_company::return_handling(company, station_id, user_id,timeReturn);

        }
    }
    
    company->showQuota();
    cout << endl
         << "------------------------------" << endl
         << "Revenue = " << company->revenue << endl
         << "------------------------------" << endl;

    status << endl
         << "------------------------------" << endl
         << "Revenue = " << company->revenue << endl
         << "------------------------------" << endl;

    status.close();
    response.close();
    feeStream.close();
    stationStream.close();
    requestStream.close();
    checkStream.close();
    userStream.close();
    mapStream.close();

    clock_t end = clock();
    cout << "Time cost: " << (double)(end - start) / CLOCKS_PER_SEC * 1000
         << "ms." << endl;
    
    return 0;
}




void fileRefresh(){
#ifndef TEST
    status << "";
    status.close();
    status.open("./part1_status.txt", ofstream::app);
    response << "";
    response.close();
    response.open("./part1_response.txt", ofstream::app);
#else
    status << "";
    status.close();
    status.open("../output/part1_status.txt", ofstream::app);
    response << "";
    response.close();
    response.open("../output/part1_response.txt", ofstream::app);
#endif
}
