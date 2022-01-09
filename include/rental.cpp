#include "rental_company.h"
#include "bike.h"

extern ifstream feeStream;
extern ofstream status;
extern ifstream stationStream;
extern ofstream response;

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

    this->most_expensive_type = electric_fee[1] > lady_fee[1] ? (electric_fee[1] > road_fee[1]? "electric" : "road") : (lady_fee[1] > road_fee[1] ? "lady" : "road");
    this->station_info = (class station **)malloc(sizeof(class station) * (map_info::station_amount + 1));
    this->map = map;
    this->bikeAmountInit(stationStream);
    this->user_info_manager = new user();
    this->revenue = 0;
    this->total_rent_request = 0;

    #ifdef DEBUG
    cout << "-------------------------" << endl
         << "       Show Price        " << endl
         << "-------------------------" << endl;
    cout <<  "  Reg "<< electric_fee[1] << ", discount "<< electric_fee[0] << endl;
    cout <<  "  Reg "<< lady_fee[1] << ", discount "<< lady_fee[0] << endl;
    cout <<  "  Reg "<< road_fee[1] << ", discount "<< road_fee[0] << endl<< endl << endl;
    #endif
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
    this->total_rent_amount ++;
    bikeRegistering();

}

void rental_company::showQuota(){
    int bikeCount = 0;
    
    for (int i = 1; i <= map_info::station_amount; i ++){
        // cout << "station_id: " << i << endl;
        bikeCount += this->station_info[i]->electric_manager->residual;
        bikeCount += this->station_info[i]->lady_manager->residual;
        bikeCount += this->station_info[i]->road_manager->residual;
        cout  << i <<": " << endl;
        cout << "electric: " ;
        status << i << ": " << endl
               << "electric: ";
        this->station_info[i]->electric_manager->printHeap();
        cout << "lady: " ;
        status << "lady: ";
        this->station_info[i]->lady_manager->printHeap();
        cout << "road: " ;
        status << "road: ";
        this->station_info[i]->road_manager->printHeap();
    }
    #ifdef DEBUG
    cout << "After a day, total bike amount = " << bikeCount << endl;
    #endif
}






void station::bikeRegistering(){
    static int bikeCount = 0;

    for (int i = 0; i < this->electric_manager->quota; i++){
        int bikeId = this->station_id * 100 + i;
        this->electric_manager->insert(bikeId);
    }
    bikeCount += this->electric_manager->quota;
    this->electric_manager->quota = 100 * map_info::station_amount;
    for (int i = 0; i < this->lady_manager->quota; i++){
        int bikeId = this->station_id * 100 + i;
        this->lady_manager->insert(bikeId);
    }
    bikeCount += this->lady_manager->quota;
    this->lady_manager->quota = 100 * map_info::station_amount;
    for (int i = 0; i < this->road_manager->quota; i++){
        int bikeId = this->station_id * 100 + i;
        this->road_manager->insert(bikeId);
    }
    bikeCount += this->road_manager->quota;
    this->road_manager->quota = 100 * map_info::station_amount;
    // after initializing we expand the quota to the possible maximun number of the whole world
    // allowing all bikes to returne to the same station

    if (this->station_id == map_info::station_amount)
    {
      rental_company::totalBikeInventory = bikeCount;
      bikeCount = 0;
    }
        
}

string rental_company::rent_handling(rental_company *company, int stationId, string userId, string bikeType, int rentTime, int policyLevel){
    if(rentTime < 0 || rentTime > 1440){
        return "reject";
        // request out of time is not acceptable
    }
    company->total_rent_request ++;
    company->station_info[stationId]->total_rent_amount++;

    // find out the popularity of a certain station, as an reference of changing bike type
    double station_access_rate =
        (float)company->station_info[stationId]->total_rent_amount / (8 * company->total_rent_request);
    int inventoryBuffer = (int)ceil(round(rental_company::totalBikeInventory * station_access_rate)) % 10;
    // cout << inventoryBuffer << endl;
    
    // after a borrow request get, increase the record no matter bike shortage or not
    int bike_type = 0;
    if(bikeType == "electric")
        bike_type = 1;
    else if(bikeType == "lady")
        bike_type = 2;
    else if(bikeType == "road")
        bike_type = 3;

    string policy = "normal";

    switch(bike_type){
    case 1:
            company->station_info[stationId]->electric_manager->rent_amount++;
            company->station_info[stationId]->electric_manager->request_rate =
                (float)company->station_info[stationId] ->electric_manager->rent_amount / company->station_info[stationId]->total_rent_amount;
            if (company->station_info[stationId]->electric_manager->residual <= 0)
            {
              if (policyLevel != 2)
                    return "reject";
                policy = "reject";

                if (company->most_expensive_type == "electric")
                  return "reject";
                int changeToWhichType = 0;
                string leastUsedType =
				lady_fee[0] < road_fee[0] ? "road" : "lady";

				int rentBikeId = 0;
				if (leastUsedType == "road"){
					if (company->station_info[stationId] ->road_manager->residual <= inventoryBuffer)
						return "reject";
					rentBikeId = company->station_info[stationId]->road_manager->extractMin();
				}
				else
				{
				if (company->station_info[stationId]->lady_manager->residual <= inventoryBuffer)
						return "reject";
					rentBikeId = company->station_info[stationId]->lady_manager->extractMin();
				}

				policy = "change";
				company->user_info_manager->insert(stationId, userId, leastUsedType, rentBikeId, rentTime, policy);
				return "change to " + leastUsedType;                  
	


                return "reject";
            }
            else{
                int rentBikeId = company->station_info[stationId]->electric_manager->extractMin();
                company->user_info_manager->insert(stationId, userId, bikeType, rentBikeId, rentTime, policy);
            }
            break;
    case 2:
            company->station_info[stationId]->lady_manager->rent_amount++;
            company->station_info[stationId]->lady_manager->request_rate =
                (float)company->station_info[stationId] ->lady_manager->rent_amount / company->station_info[stationId]->total_rent_amount;
            if (company->station_info[stationId]->lady_manager->residual <= 0)
            {
                if (policyLevel != 2)
                    return "reject";
                policy = "reject";

                if (company->most_expensive_type == "lady")
                  return "reject";

                int changeToWhichType = 0;

				string leastUsedType =
					electric_fee[0] < road_fee[0] ? "road" : "electric";

				int rentBikeId = 0;
				if (leastUsedType == "road") {
					if (company->station_info[stationId]->road_manager->residual <= inventoryBuffer)
							return "reject";
					rentBikeId = company->station_info[stationId]->road_manager->extractMin();
				}
				else {
					if (company->station_info[stationId] ->electric_manager->residual <= inventoryBuffer)
						return "reject";
					rentBikeId = company->station_info[stationId]->electric_manager->extractMin();
				}

				policy = "change";
				company->user_info_manager->insert(stationId, userId, leastUsedType, rentBikeId, rentTime, policy);
				return "change to " + leastUsedType; 

                
                // company->user_info_manager->insert(stationId, userId, bikeType,rentTime, policy);
                return "reject";
            }
            else{
                int rentBikeId = company->station_info[stationId]->lady_manager->extractMin();
                company->user_info_manager->insert(stationId, userId, bikeType, rentBikeId, rentTime, policy);
            }
            break;
        case 3:
            if (company->station_info[stationId]->road_manager->residual <= 0){
                if (policyLevel != 2)
                    return "reject";
              	policy = "reject";
                if (company->most_expensive_type == "road")
                  return "reject";
                int changeToWhichType = 0;
                string leastUsedType =
                    lady_fee[0] < electric_fee[0] ? "electric" : "lady";


				int rentBikeId = 0;
				if (leastUsedType == "lady") {
					if (company->station_info[stationId] ->lady_manager->residual <= inventoryBuffer)
						return "reject";
					rentBikeId = company->station_info[stationId]->lady_manager->extractMin();
				}
				else {
					if (company->station_info[stationId]->electric_manager->residual <= inventoryBuffer)
						return "reject";
					rentBikeId = company->station_info[stationId]->electric_manager->extractMin();
				}

				policy = "change";
				company->user_info_manager->insert(stationId, userId, leastUsedType, rentBikeId, rentTime, policy);
				return "change to " + leastUsedType;                  


                // company->user_info_manager->insert(stationId, userId, bikeType,rentTime, policy);
                return "reject";
            }
            else{
                int rentBikeId = company->station_info[stationId]->road_manager->extractMin();
                company->user_info_manager->insert(stationId, userId, bikeType, rentBikeId,rentTime, policy);
            }
            break;
    }
    company->user_info_manager->findUser(userId);
    return "accept";
}

void rental_company::return_handling(rental_company * company, int stationId, string userId, int returnTime){
    int user_id = stoi(userId);
    node *user = company->user_info_manager->findUser(userId);
    if (user == nullptr) 
      return ;
    if(returnTime - user->rentTime > 1440 || returnTime - user->rentTime < 0){
        cout << "invalid return" << endl;
        return;
    }
    
    int bike_type;
    if(user->bikeType == "electric")
        bike_type = 1;
    else if(user->bikeType == "lady")
        bike_type = 2;
    else
        bike_type = 3;

    int bigger_stationId = user->station_id > stationId ? user->station_id : stationId;
    int smaller_stationId = user->station_id < stationId ? user->station_id : stationId;

    int shortest_distance = company->map[smaller_stationId]->distance[bigger_stationId];
    int actual_distance = returnTime - user->rentTime;

    switch(bike_type){
        case 1:
            company->station_info[stationId]->electric_manager->insert(user->bikeId);
            
            if (actual_distance > shortest_distance) {
                if (user->policy == "change")
                    actual_distance *= reduced_rate;
                

                company->revenue += actual_distance * company->station_info[stationId]->electric_manager->regular_fee;
                // cout << "No discount :< \n";
            }
            else {
              if (user->policy == "change")
                    actual_distance *= reduced_rate;
              company->revenue +=
                  actual_distance * company->station_info[stationId] ->electric_manager->discount_fee;
            }
            break;
        case 2:
            company->station_info[stationId]->lady_manager->insert(user->bikeId);
            if (actual_distance > shortest_distance) {
                if (user->policy == "change")
                    actual_distance *= reduced_rate;
                company->revenue += actual_distance * company->station_info[stationId]->lady_manager->regular_fee;
            }
            else {
            	if (user->policy == "change")
                	actual_distance *= reduced_rate;
              	company->revenue += actual_distance * company->station_info[stationId] ->lady_manager->discount_fee;
            }
            break;
        case 3:
            company->station_info[stationId]->road_manager->insert(user->bikeId);
            if (actual_distance > shortest_distance) {
                if (user->policy == "change")
                    actual_distance *= reduced_rate;
                
                company->revenue += actual_distance * company->station_info[stationId]->road_manager->regular_fee;
            }
            else {
              if (user->policy == "change")
                    actual_distance *= reduced_rate;
              company->revenue +=
                  actual_distance * company->station_info[stationId] ->road_manager->discount_fee;
            }
            break;
    }
}
