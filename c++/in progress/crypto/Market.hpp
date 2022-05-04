#ifndef MARKET
#define MARKET

#include <iostream>
#include <stdlib.h>
#include <ctime>

#include "Money.hpp"
#include "Wallet.hpp"
#include "Trade.hpp"
#include "Ore.hpp"
#include "Crypto.hpp"
#include "Transaction.hpp"
using namespace std;

class Market
{
private:
    vector<Money*> avaliable_currence;
    Wallet<Money>* wallet_main;
    Money* base_coin;
    Trade* trading;
public:
    Market(string);
    ~Market();
    Money* base_currency(); // return base coin
    virtual void set_balance(float); // set starting balance to the wallet
    virtual void toString();
    virtual void add_currences(int); // add a number of currencies to the market (avaliable_currence)
    virtual void trader(); //run trade() in a loop until the wallet becomes empty

};

Market::Market(string id)
{
    // create the base coin and add it to the avaliable_currences
    srand (time(NULL));

    base_coin = new Money("base",(avaliable_currence.size() +1), 1);
    avaliable_currence = {};
    avaliable_currence.push_back(base_coin);
    // create the wallet using the id and the base coin
    wallet_main = new Wallet<Money>(id);
}

Market::~Market()
{
    //delete &avaliable_currence;
    delete wallet_main;
    delete base_coin;
}

Money* Market::base_currency()
{
    return(base_coin);
}

void Market::set_balance(float a)
{
    wallet_main->set_balance(base_coin, a);
    wallet_main->toString();
}

void Market::toString()
{
    cout<<"\n----------------------------------------------------------"<<endl;
    for(int i=0;i<avaliable_currence.size();i++)
    {
        avaliable_currence[i]->toStringv();
        //cout<<"Amount: "<<avaliable_currence[i]<<endl;
        cout<<"----------------------------------------------------------"<<endl;
    }
}

void Market::add_currences(int n)
{
    srand (time(NULL));
    int x;
    for(int i=0; i<n;i++)
    {
        x = (rand()%3);
        Money* temp2;
        switch(x)
        {
        case 0:
            temp2 = new Money("money",(avaliable_currence.size() +1),(0.1+ float(rand()%50)/10));
            break;
        case 1:
            temp2 = new Ore("ore",(avaliable_currence.size() +1),1);
            break;
        case 2:
            temp2 = new Crypto("crypto",(avaliable_currence.size() +1),(0.1+ float(rand()%50)/10),"none");
            break;
        }

        avaliable_currence.push_back(temp2);

    }
}

void Market::trader()
{
    float a,b;
    cout<<"Enter two numbers separated by space (both <=1): ";
    cin>>a>>b;
    cout<<"\n*** To make this program convergent the numbers are going to be assign so that pSell > pBuy is true ***"<<endl;
    trading = new Trade(max(a,b),min(a,b));
    cout<<"\n----------------------------------------------------------"<<endl;
    cout<<"*** TRADING ***"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    float balance = wallet_main->current_balance();
    vector<Money*> wallet_cur = wallet_main->avaliable_currences();
    srand (time(NULL));
    int x,y;
    x=0;
    y=0;
    Transaction * temp1;
    while(balance>0)
    {
        balance = wallet_main->current_balance();

        for(int i=1;i<avaliable_currence.size();i++)
        {
            wallet_cur = wallet_main->avaliable_currences();
            cout<<i<<endl;

            if(trading->trade('s')) // can we sell?
            {
                if(wallet_main->is_posible( wallet_cur[i%wallet_cur.size()],base_coin))// is it possible to make this transaction?
                {
                    cout<<i<<"s1"<<endl;
                    (*wallet_main)+=wallet_cur[i%wallet_cur.size()];
                    cout<<i<<"s2"<<endl;
                    temp1= new Transaction(*base_coin,*wallet_cur[i%wallet_cur.size()]);
                    cout<<i<<"s3"<<endl;
                    temp1->toString();
                    cout<<i<<"s4"<<endl;
                }


            }
            cout<<i<<endl;
            if(trading->trade('b')) // can we sell?
            {

                if(wallet_main->is_posible(base_coin, avaliable_currence[i])) // is it possible to make this transaction?
                {
                    cout<<i<<"b"<<endl;
                    (*wallet_main)-=avaliable_currence[i];
                    temp1= new Transaction(*avaliable_currence[i],*base_coin);
                    temp1->toString();
                    cout<<i<<"b"<<endl;
                }

            }
            cout<<i<<endl;
        }


    }

}

#endif // MARKET
