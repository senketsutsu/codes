#ifndef TRANSACTION
#define TRANSACTION

#include<iostream>
#include<string>
#include<ctime>

#include "Money.hpp"

class Transaction
{
private:
    string date; // the date of the transaction
    string money_buy; // name+" "+id of the money that we are buying
    string money_sell; // name+" +id of the money that we are selling

public:
    Transaction(Money, Money);
    ~Transaction();
    virtual void toString();
};

Transaction::Transaction(Money buy, Money sell)
{

    date = *(new string);
    money_buy = *(new string);
    money_sell = *(new string);


    money_buy = buy.toString();
    money_sell = sell.toString();

    // we are getting the current date and time to automatically add it to the transaction data
    time_t now = time(0);
    string dt = ctime(&now);
    date = dt;
}

Transaction::~Transaction()
{
    delete &date;
    delete &money_buy;
    delete &money_sell;
}

void Transaction::toString()
{
    cout<<"date: "<<date<<endl;
    cout<<"bought: "<<money_buy<<endl;
    cout<<"sold: "<<money_sell<<endl;
    //cout<<"----------------------------------------------------------"<<endl;
}

#endif // TRANSACTION
