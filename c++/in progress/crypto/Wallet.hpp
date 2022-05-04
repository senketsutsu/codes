#ifndef WALLET
#define WALLET

#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<algorithm>

#include "Money.hpp"
#include "Transaction.hpp"


using namespace std;

template <class T>

class Wallet
{
private:
    string owners_id;  // PESEL or id number
    vector<T*> owned_money; // list of all owned currences
    // after thinking a lil bit i realise that i could have used map for this but then i would have to change also the market a lil bit
    vector<float> owned_amount;

public:
    Wallet(string);
    ~Wallet();
    float current_balance(); // returns the current balance
    void toString(); // prints owners id, current balance and a table of all currencies and their amount and current balance
    Wallet<T>& operator-=(T* a);
    Wallet& operator+=(T* a);
    vector<T*> avaliable_currences();
    virtual void set_balance(T*, float);
    virtual bool is_posible(T*,T*);
};

template <class T>
Wallet<T>::Wallet(string id)
{

    //owned_amount = new vector<float>;
    owners_id =*( new string);
    owners_id = id;
    //*owned_money = {};
    owned_amount = *(new vector<float>);
    owned_amount = {};
    owned_money = *(new vector<T*>);
    owned_money = {};
}

template <class T>
Wallet<T>::~Wallet()
{
    delete &owners_id;
    delete &owned_money;
    delete &owned_amount;
}

template <class T>
float Wallet<T>::current_balance()
{
    float temp=0;
    for(int i=0;i<owned_money.size();i++)
    {
        temp=temp+((owned_money[i]->exchange_ratev())*owned_amount[i]);
    }
    return(temp);
}

template <class T>
void Wallet<T>::toString()
{
    cout<<"\n\nOwner id: "<<owners_id<<"\n"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    for(int i=0;i<owned_money.size();i++)
    {
        owned_money[i]->toStringv();
        cout<<"Amount: "<<owned_amount[i]<<endl;
        cout<<"----------------------------------------------------------"<<endl;
    }
}

template <class T>
Wallet<T>& Wallet<T>::operator-=( T* a)
{
    for(int i=0;i<owned_amount.size();i++)
    {
        if(owned_money[i]==a)
        {
            a->del();
            owned_amount[i]-=1;
        }
    }
    this->owned_amount[0]+=(a->exchange_ratev());
    return(*this);
}

template <class T>
Wallet<T>& Wallet<T>::operator+=(T* a)
{
    int b=0;
    for(int i=0;i<owned_amount.size();i++)
    {
        if(owned_money[i]==a)
        {
            a->add(this->owners_id);
            this->owned_amount[i]+=1;
            b=1;
        }
    }
    if(b==0)
    {
        this->owned_money.push_back(a);
        this->owned_amount.push_back(1);
    }
    this->owned_amount[0]-=(a->exchange_ratev());
    return(*this);
}

template <class T>
vector<T*> Wallet<T>::avaliable_currences()
{
    return(owned_money);
}
template <class T>
void Wallet<T>::set_balance(T* a, float b)
{
    owned_money = {a};
    owned_amount = {b};
}
template <class T>
 bool Wallet<T>::is_posible(T* sell,T* buy)
{
    float a;
    for(int i=0;i<owned_amount.size();i++)
    {
        if(owned_money[i]==sell)
        {
            a = (sell->exchange_ratev())*(owned_amount[i]);
        }
    }
    float b;
    for(int i=0;i<owned_amount.size();i++)
    {
        if(owned_money[i]==buy)
        {
            b = (sell->exchange_ratev())*(owned_amount[i]);
        }
    }
    return(a>=b);
}

#endif // WALLET
