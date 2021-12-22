#include "rental_company.h"
#include "bike.h"

extern ifstream feeStream;

int electric_fee[2];
int lady_fee[2];
int road_fee[2];
// 0 represent discount fee
// 1 represent regular fee

int transfer_fee;
int reduced_rate;
int waiting_fee;

rental_company::rental_company(class map_info** map){
    string str;
    feeStream >> str;
    feeStream >> electric_fee[0] >> electric_fee[1];
    feeStream >> str;
    feeStream >> lady_fee[0] >> lady_fee[1];
    feeStream >> str;
    feeStream >> road_fee[0] >> road_fee[1];
    feeStream >> waiting_fee >> reduced_rate >> transfer_fee;
    this->station_info = (class station **)malloc(sizeof(class station) * (map_info::station_amount + 1));
    this->map = map;
    // this->station_info = new station()[map_info::station_amount + 1];
    this->user_info_manager = new user();
}

void rental_company::bikeAmountInit(ifstream& stationStream){
    while(!stationStream.eof()){
        int station_id;
        int electric_amount, lady_amount, road_amount;
        stationStream >> station_id >> electric_amount >> lady_amount >> road_amount;
        this->station_info[station_id] = new station(station_id, electric_amount, lady_amount, road_amount);
    }
}


station::station(int station_id, int electric_num, int lady_num, int road_num){

    this->electric_manager = new electric(electric_num, electric_fee[1], electric_fee[0]);
    this->lady_manager = new lady(lady_num, lady_fee[1], lady_fee[0]);
    this->road_manager = new road(road_num, road_fee[1], road_fee[0]);
    this->station_id = station_id;
    bikeRegistering();
    // this->electric_amount = elec;
    // this->lady_amount = lady;
    // this->road_amount = road;
}

void rental_company::showQuota(){
    for (int i = 1; i <= map_info::station_amount; i ++){
        cout << "station_id: " << i << endl;
        this->station_info[i]->electric_manager->printHeap();
        this->station_info[i]->lady_manager->printHeap();
        this->station_info[i]->road_manager->printHeap();
    }
}




void station::bikeRegistering(){
    for (int i = 0; i < this->electric_manager->quota; i++){
        int bikeId = this->station_id * 100 + i;
        this->electric_manager->insert(bikeId);
    }

    for (int i = 0; i < this->lady_manager->quota; i++){
        int bikeId = this->station_id * 100 + i;
        this->lady_manager->insert(bikeId);
    }

    for (int i = 0; i < this->road_manager->quota; i++){
        int bikeId = this->station_id * 100 + i;
        this->road_manager->insert(bikeId);
    }
}

string rental_company::rent_handling(rental_company *company, int stationId, string userId, string bikeType, int rentTime){
    if(rentTime < 0 || rentTime > 1440){
        return "reject";
        // request out of time is not acceptable
    }
    int bike_type = 0;
    if(bikeType == "electric")
        bike_type = 1;
    else if(bikeType == "lady")
        bike_type = 2;
    else if(bikeType == "road")
        bike_type = 3;
    
    switch(bike_type){
        case 1:
            if(company->station_info[stationId]->electric_manager->residual <= 0){
                cout << "electric not available now" << endl;
                return "reject";
            }
            else{
                int rentBikeId = company->station_info[stationId]->electric_manager->extractMin();
                company->user_info_manager->insert(stationId, userId, bikeType, rentTime);
            }
            break;
        case 2:
            if(company->station_info[stationId]->lady_manager->residual <= 0){
                cout << "lady not available now" << endl;
                return "reject";
            }
            else{
                int rentBikeId = company->station_info[stationId]->lady_manager->extractMin();
                company->user_info_manager->insert(stationId, userId, bikeType, rentTime);
            }
            break;
        case 3:
            if(company->station_info[stationId]->road_manager->residual <= 0){
                cout << "road not available now" << endl;
                return "reject";
            }
            else{
                int rentBikeId = company->station_info[stationId]->road_manager->extractMin();
                company->user_info_manager->insert(stationId, userId, bikeType, rentTime);
            }
            break;
    }
    company->user_info_manager->hTable->findUser(userId);
    return "accept";
}
