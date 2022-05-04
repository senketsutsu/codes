#ifndef MONEY
#define MONEY

#include <string>
#include <iostream>


using namespace std;

class Money
{
protected:
    string* name;
    int* id;
    float* exchange_rate;

public:
    Money(string, int, float);
    ~Money();
    virtual void toStringv(); // to string but void
    virtual string toString();
    virtual void add(string);
    virtual void del();
    virtual float exchange_ratev();


};

Money::Money(string new_name, int new_id, float new_exchange_rate)
{
    name = new string;
    id = new int;
    exchange_rate = new float;

    *name = new_name;
    *id = new_id;
    *exchange_rate = new_exchange_rate;
}

Money::~Money(){
    delete name;
    delete id;
    delete exchange_rate;
}

void Money::toStringv()
{
    cout<<"Name: "<<*name<<"\nId: "<<*id<<"\nExchange rate: "<<*exchange_rate<<endl;
}

string Money::toString()
{
    return( (*name)+to_string(*id));
}
void Money::add(string id)
{
    cout<<" ";
}
void Money::del()
{
    cout<<" ";
}

float Money::exchange_ratev()
{
    return(*exchange_rate);
}

#endif // MONEY
