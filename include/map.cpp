#include "map.h"



map_info::map_info(int id, int amount){
    this->station_id = id;
    map_info::station_amount = amount - 1;
    // cout << "station amount = " << map_info::station_amount << endl;
    // station_adjacency = new bool[station_amount];
    station_adjacency = (bool *)malloc(sizeof(bool) * amount);
    distance = (int *)malloc(sizeof(int) * amount);

    for (int i = 1; i < amount; i++){
        if(this->station_id != i){
            this->station_adjacency[i] = false;
        }
        this->distance[i] = 0;
    }
}

void map_info::findMaxId(ifstream& mapStream){
    int maxId = -INT_MAX;
    while (!mapStream.eof())
    {
        // string str;
        int input = 0;
        mapStream >> input;
        if (input > maxId)
            maxId = input;
        mapStream >> input;
        if (input > maxId)
            maxId = input;
        mapStream >> input;
        // cout << str << endl;
        // dataCount++;
    }

    map_info::station_amount =  maxId;
    mapStream.clear();
    mapStream.seekg(0);
}

void map_info::buildMap(ifstream& mapStream, map_info **station){
    for (int i = 1; i <= map_info::station_amount; i++)
        station[i] = new map_info(i, map_info::station_amount + 1);

    while (!mapStream.eof()){
        // string str;
        int input = 0;
        mapStream >> input;
        int input2 = 0;
        mapStream >> input2;
        station[input]->station_adjacency[input2] = true;
        int distance = 0;
        mapStream >> distance;
        station[input]->distance[input2] = distance;
    }
}

void map_info::showMap(map_info **station){
    cout << "station amount = " << map_info::station_amount << endl;
    for (int i = 1; i <= map_info::station_amount; i++){
        for (int j = i; j <= map_info::station_amount; j++){
            if (station[i]->station_adjacency[j])
                cout << i << " " << j << ", distance = " << station[i]->distance[j] << endl;
        }
    }
}
