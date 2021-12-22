#include "bike.h"

#define swap(a, b) \
    (a) ^= (b);    \
    (b) ^= (a);    \
    (a) ^= (b);

#define parentNode(i) (((i)-1) / 2)
#define leftChild(i) ((2 * (i)) + 1)
#define rightChild(i) ((2 * (i)) + 2)

electric::electric(int amount)
{
    this->quota = amount;
    this->residual = 0;
    this->storehouse = (int *)malloc(sizeof(int) * amount);
}

lady::lady(int amount)
{
    this->quota = amount;
    this->residual = 0;
    this->storehouse = (int *)malloc(sizeof(int) * amount);
}

road::road(int amount)
{
    this->quota = amount;
    this->residual = 0;
    this->storehouse = (int *)malloc(sizeof(int) * amount);
}

void electric::insert(int key)
{
    if (this->residual == this->quota)
    {
        cout << "can't store more electric!" << endl;
        return;
    }

    this->residual++;
    int nowPosition = this->residual - 1;
    this->storehouse[nowPosition] = key;

    while (!(nowPosition) && this->storehouse[parentNode(nowPosition)] > this->storehouse[nowPosition])
    {
        swap(this->storehouse[parentNode(nowPosition)], this->storehouse[nowPosition]);
        nowPosition = parentNode(nowPosition);
    }
}

void lady::insert(int key)
{
    if (this->residual == this->quota)
    {
        cout << "can't store more lady!" << endl;
        return;
    }

    this->residual++;
    int nowPosition = this->residual - 1;
    this->storehouse[nowPosition] = key;

    while (!(nowPosition) && this->storehouse[parentNode(nowPosition)] > this->storehouse[nowPosition])
    {
        swap(this->storehouse[parentNode(nowPosition)], this->storehouse[nowPosition]);
        nowPosition = parentNode(nowPosition);
    }
}

void road::insert(int key)
{
    if (this->residual == this->quota)
    {
        cout << "can't store more road!" << endl;
        return;
    }

    this->residual++;
    int nowPosition = this->residual - 1;
    this->storehouse[nowPosition] = key;

    while (!(nowPosition) && this->storehouse[parentNode(nowPosition)] > this->storehouse[nowPosition])
    {
        swap(this->storehouse[parentNode(nowPosition)], this->storehouse[nowPosition]);
        nowPosition = parentNode(nowPosition);
    }
}

void electric::printHeap()
{
    cout << "Amount of electric: " << this->residual << endl;
    int amount = this->residual;
    for (int i = 0; i < amount; i++)
    {
        // cout << this->extractMin() << " ";
        this->extractMin();
        cout << this->residual << " ";
    }
    cout << endl;
}

int electric::extractMin()
{
    if (this->residual <= 0)
    {
        cout << "electric storehouse empty!" << endl;
        return 0;
    }

    int min = this->storehouse[0];
    this->storehouse[0] = this->storehouse[this->residual - 1];
    this->residual--;

    this->heapify(0);
    return min;
}

void electric::heapify(int index)
{
    int l = leftChild(index);
    int r = rightChild(index);

    int min = index;
    if (l < this->residual && this->storehouse[l] < this->storehouse[min])
        min = l;
    if (r < this->residual && this->storehouse[r] < this->storehouse[min])
        min = r;
    if (min != index)
    {
        swap(this->storehouse[min], this->storehouse[index]);
        this->heapify(min);
    }
}

void lady::printHeap()
{
    cout << "Amount of lady: " << this->residual << endl;
    int amount = this->residual;
    for (int i = 0; i < amount; i++)
    {
        // cout << this->extractMin() << " ";
        this->extractMin();
        cout << this->residual << " ";
    }
    cout << endl;
}

int lady::extractMin()
{
    if (this->residual <= 0)
    {
        cout << "lady storehouse empty!" << endl;
        return 0;
    }

    int min = this->storehouse[0];
    this->storehouse[0] = this->storehouse[this->residual - 1];
    this->residual--;

    this->heapify(0);
    return min;
}

void lady::heapify(int index)
{
    int l = leftChild(index);
    int r = rightChild(index);

    int min = index;
    if (l < this->residual && this->storehouse[l] < this->storehouse[min])
        min = l;
    if (r < this->residual && this->storehouse[r] < this->storehouse[min])
        min = r;

    if (min != index)
    {
        swap(this->storehouse[min], this->storehouse[index]);
        this->heapify(min);
    }
}

void road::printHeap()
{
    cout << "Amount of road: " << this->residual << endl;
    int amount = this->residual;
    for (int i = 0; i < amount; i++)
    {
        // cout << this->extractMin() << " ";
        this->extractMin();
        cout << this->residual << " ";
    }
    cout << endl;
}

int road::extractMin()
{
    if (this->residual <= 0)
    {
        cout << "road storehouse empty!" << endl;
        return 0;
    }

    int min = this->storehouse[0];
    this->storehouse[0] = this->storehouse[this->residual - 1];
    this->residual--;

    this->heapify(0);
    return min;
}

void road::heapify(int index)
{
    int l = leftChild(index);
    int r = rightChild(index);

    int min = index;
    if (l < this->residual && this->storehouse[l] < this->storehouse[min])
        min = l;
    if (r < this->residual && this->storehouse[r] < this->storehouse[min])
        min = r;

    if (min != index)
    {
        swap(this->storehouse[min], this->storehouse[index]);
        this->heapify(min);
    }
}
