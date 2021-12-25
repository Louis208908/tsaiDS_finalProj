#include "renter.h"
#include "rental_company.h"

extern ofstream requestStream;

static ofstream checkStream("../DS_testcase/open_basic1/test_case/check2.txt", ofstream::out);

node *node::insert(node *root, int stationId, string user_id, string bikeType, int bikeId, int rentTime, string policy)
{
    if (root == nullptr)
        return new node(stationId, user_id, bikeType, bikeId, rentTime, policy);
    root->next = insert(root->next, stationId, user_id, bikeType, bikeId, rentTime, policy);
    return root;
}

node::node(int stationId, string user_id, string bikeType, int bikeId, int rentTime, string policy)
{
    this->policy = policy;
    this->bikeType = bikeType;
    this->rentTime = rentTime;
    this->user_id = user_id;
    this->bikeId = bikeId;
    this->station_id = stationId;
    this->next = nullptr;
}

hashTable::hashTable(int hashFcn)
{
    this->user_info = (class node **)malloc(sizeof(class node *) * hashFcn);
    this->hashFcn = hashFcn;
    for (int i = 0; i < hashFcn; i++)
    {
        this->user_info[i] = nullptr;
    }
}

node *user::findUser(string user_id)
{
    int id = stoi(user_id);
    int key = id % this->hTable->hashFcn;
    node *current = this->hTable->user_info[key];

    while (current != nullptr && current->user_id != user_id)
    {
        current = current->next;
    }
    if (current->user_id == user_id)
    {

        // cout << current->user_id << " " << current->bikeType << " " << current->rentTime << endl;
        // checkStream << current->user_id << " " << current->bikeType << " " << current->rentTime << endl;
        return current;
    }
    else
        return nullptr;
}

user::user()
{
    this->hTable = new hashTable(map_info::station_amount);
}

void user::insert(int stationId, string user_id, string bikeType, int bikeId, int rentTime, string policy)
{
    int userId = stoi(user_id);
    int key = hashKey(userId, this->hTable->hashFcn);
    this->hTable->user_info[key] = node::insert(this->hTable->user_info[key], stationId, user_id, bikeType, bikeId, rentTime, policy);
}
