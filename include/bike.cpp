#include "bike.h"
#include "rental_company.h"

#define swap(a, b) \
    (a) ^= (b);    \
    (b) ^= (a);    \
    (a) ^= (b);


#define parentNode(i) (((i) - 1) / 2)
#define leftChild(i) ((2 * (i)) + 1)
#define rightChild(i) ((2 * (i)) + 2)

BIKE::BIKE(int amount){
    this->quota = amount;
    this->residual = 0;
    this->storehouse = (int *)malloc(sizeof(int) * 100 * map_info::station_amount);
}

void BIKE::insert(int key){
    if(this->residual == this->quota){
        cout << "can't store any more !" << endl;
        return;
    }

    this->residual++;
    int nowPosition = this->residual - 1;
    this->storehouse[nowPosition] = key;
    
    while( !(nowPosition) && this->storehouse[parentNode(nowPosition)] > this->storehouse[nowPosition]){
        swap(this->storehouse[parentNode(nowPosition)], this->storehouse[nowPosition]);
        nowPosition = parentNode(nowPosition);
    }
}

void BIKE::printHeap(){
    cout << "Amount: " << this->residual << endl;
    int amount = this->residual;
    for (int i = 0; i < amount; i++){
        cout << this->extractMin() << " ";
        // this->extractMin();
        // cout << this->residual << " ";
    }
    cout << endl;
}

int BIKE::extractMin(){
    if(this->residual <= 0){
        cout << "storehouse empty!" << endl;
        return NULL ;
    }

    int min = this->storehouse[0];
    this->storehouse[0] = this->storehouse[this->residual- 1];
    this->residual--;

    this->heapify(0);
    return min;
}

void BIKE::heapify(int index){
    int l = leftChild(index);
    int r = rightChild(index);

    int min = index;
    if(l < this->residual && this->storehouse[l] < this->storehouse[min])
        min = l;
    if(r < this->residual && this->storehouse[r] < this->storehouse[min])
        min = r;
    if(min != index){
        swap(this->storehouse[min], this->storehouse[index]);
        this->heapify(min);
    }
}

electric::electric(int amount, int regular, int discount) : BIKE(amount){
    this->regular_fee = regular;
    this->discount_fee = discount;
};
lady::lady(int amount, int regular, int discount) : BIKE(amount){
    this->regular_fee = regular;
    this->discount_fee = discount;
};
road::road(int amount, int regular, int discount) : BIKE(amount){
    this->regular_fee = regular;
    this->discount_fee = discount;
};


