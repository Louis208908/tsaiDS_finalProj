// g++ -g *.cpp -o 107033237_proj -std=c++11

#include "bits/stdc++.h"
#include "stdio.h"
#include "stdlib.h"
#include "dirent.h"
#include "rental_company.h"

using namespace std;

ifstream mapStream("../DS_testcase/open_basic1/test_case/map.txt", ifstream::in);
ifstream stationStream("../DS_testcase/open_basic1/test_case/station.txt", ifstream::in);
ifstream userStream("../DS_testcase/open_basic1/test_case/user.txt", ifstream::in);
ifstream feeStream("../DS_testcase/open_basic1/test_case/fee.txt", ifstream::in);
ofstream requestStream("../DS_testcase/open_basic1/test_case/request.txt", ofstream::out);
static ofstream checkStream("../DS_testcase/open_basic1/test_case/check.txt", ofstream::out);

void findFiles(string path)
{
    DIR *dir = NULL;
    struct dirent *entry;
    int fileAmount = 0;
    if ((dir = opendir(&path[0])) == NULL)
    {
        printf("opendir failed!");
        return;
    }
    else
    {
        while (entry = readdir(dir))
        {
            cout << entry->d_name << endl;
            // if (strstr(entry->d_name, ".csv") != NULL)
            //     fileAmount++;
        }
        closedir(dir);
    }
}

int map_info::station_amount;

int main(void)
{



    map_info::findMaxId(mapStream);
    class map_info *station_info[map_info::station_amount + 1];
    map_info::buildMap(mapStream, station_info);
    // map_info::showMap(station_info);

    rental_company *company = new rental_company(station_info);
    company->bikeAmountInit(stationStream);

    while(!userStream.eof()){
        string serviceType;
        int station_id;
        string user_id;
        int timeRent;
        int timeReturn;
        string bikeType;
        userStream >> serviceType;
        if(serviceType == "rent"){
            // cout << "renting bike" << endl;
            userStream >> station_id;
            userStream >> bikeType;
            userStream >> user_id;
            userStream >> timeRent;
            // cout << stoi(user_id) << endl;
            // cout << station_id << " " << bikeType << " " << user_id << " " << timeRent << "." << endl;
            requestStream << "rent "<< station_id << " " << bikeType << " " << user_id << " " << timeRent <<  endl;
            checkStream << user_id << " " << bikeType << " " << timeRent << endl;
            requestStream << rental_company::rent_handling(company, station_id, user_id, bikeType, timeRent) << endl;
        }
        else if(serviceType == "return"){
            requestStream << endl;
            // cout << "returning bike" << endl;
            userStream >> station_id;
            userStream >> user_id;
            userStream >> timeReturn;
            
            
        }
    }
    // map_info::showMap(company->map);
    company->showQuota();
    // company->showQuota();

    return 0;
}
