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
        station[input2]->station_adjacency[input] = true;
        int distance = 0;
        mapStream >> distance;
        station[input]->distance[input2] = distance;
        station[input2]->distance[input] = distance;
    }
}

void map_info::showMap(map_info **station){
    // cout << "station amount = " << map_info::station_amount << endl;
    for (int i = 1; i <= map_info::station_amount; i++){
        for (int j = 1; j <= map_info::station_amount; j++)
            printf("%3d ", station[i]->distance[j]);
        cout << endl;
    }
    
        
    
}


void map_info::findMinDistance(map_info **station) {
    bool visited[map_info::station_amount + 1];
    map_info **map = (map_info **)malloc(sizeof(map_info *) * (map_info::station_amount + 1));

    for (int i = 1; i <= map_info::station_amount; i++) 
        map[i] = (map_info *)malloc(sizeof(map_info) * (map_info::station_amount + 1));
    
    for (int i = 1; i <= map_info::station_amount; i++) {
        for (int j = 1; j <= map_info::station_amount; j++) 
            for (int k = 1; k <= map_info::station_amount; k++) 
                if (station[i]->distance[j] >station[i]->distance[k] + station[j]->distance[k])
                    station[i]->distance[j] = station[i]->distance[k] + station[k]->distance[j];
            
    }

}
