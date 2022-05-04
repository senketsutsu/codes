#ifndef ORE
#define ORE

#include "Money.hpp"

using namespace std;

class Ore: public Money
{
private:
    int* amount; // it has limited amount, if the available amount is small the price goes higher and othervise
public:
    Ore(string,int, float); //set amount as 2137
    ~Ore();
    void add(string);
    void del();
};

Ore::Ore(string new_name, int new_id, float new_exchange_rate) : Money( new_name,  new_id,  new_exchange_rate)
{
    amount = new int;
    *amount = 2137;
    //*exchange_rate = 1/(*amount);
}

Ore::~Ore()
{
    delete amount;
}

void Ore::add(string id)
{
    *exchange_rate = 2137/(*amount -1);
    *amount+=1;
}

void Ore::del()
{
    *exchange_rate = 2137/(*amount +1);
    *amount-=1;
}
#endif // ORE
