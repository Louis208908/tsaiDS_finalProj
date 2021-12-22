#include "renter.h"
#include "rental_company.h"

extern ofstream requestStream;

static ofstream checkStream("../DS_testcase/open_basic1/test_case/check2.txt", ofstream::out);

node* node::insert(node *root, string user_id, string bikeType, int rentTime){
    if(root == nullptr)
        return new node(user_id, bikeType, rentTime);
    root->next = insert(root->next, user_id, bikeType, rentTime);
    return root;
}

node::node(string user_id, string bikeType, int rentTime){
    this->bikeType = bikeType;
    this->rentTime = rentTime;
    this->user_id = user_id;
    this->next = nullptr;
}

hashTable::hashTable(int hashFcn){
    this->user_info = (class node **)malloc(sizeof(class node *) * hashFcn);
    this->hashFcn = hashFcn;
    for (int i = 0; i < hashFcn; i ++){
        this->user_info[i] = nullptr;
    }
}

node* hashTable::findUser(string user_id){
    int id = stoi(user_id);
    int key = id % this->hashFcn;
    node *current = this->user_info[key];

    while(current != nullptr && current->user_id != user_id){
        current = current->next;
    }
    if(current->user_id == user_id){

        cout << current->user_id << " " << current->bikeType << " " << current->rentTime << endl;
        checkStream << current->user_id << " " << current->bikeType << " " << current->rentTime << endl;
        return current;
    }
    else
        return nullptr;
}


user::user(){
    this->hTable = new hashTable(map_info::station_amount);
}

void user::insert(int stationId, string user_id, string bikeType, int rentTime){
    int userId = stoi(user_id);
    int key = hashKey(userId, this->hTable->hashFcn);
    this->hTable->user_info[key] = node::insert(this->hTable->user_info[key], user_id, bikeType, rentTime);
}



