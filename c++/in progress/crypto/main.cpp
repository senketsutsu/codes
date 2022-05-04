#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Market.hpp"


using namespace std;


int main()
{
    // log in to get the id which we use to create the market and the wallet
    string id;
    cout<<"\n\n\n\t\t*** MARKET ***\n\n  *please enter your ID to enter the market*\n   *the ID is unique for the wallet owner*\n\n\nID: ";
    cin>>id;

    // clear the screen
    system("CLS");

    // create market in which we create our main wallet and our base coin
    Market* main_market = new Market(id);

    // set the initial wallet balance and show current wallet balance
    int temp = 0;
    cout<<"\n*** Now we will set the initial wallet balance ***";
    while(temp <= 0)
    {
        cout<<"\n\n\nEnter the amount of base money: ";
        cin>>temp;
        if(temp <= 0)
        {
            cout<<"!!! error wrong balance !!!\n     please try again"<<endl;
        }
    }
    system("CLS");
    cout<<"Current wallet balance:"<<endl;
    main_market->set_balance(temp);

    // wait till anything is entered
    string temp1;
    cout<<"         *** Enter anything to go to the next step ***"<<endl;
    cin>>temp1;
    system("CLS");

    // how many currences do we want? (create a vector)
    temp=0;
    cout<<"\n*** Now new currences will enter the market ***";
    while(temp <= 0)
    {
        cout<<"\n\n\nEnter how many new currences should it be: ";
        cin>>temp;
        if(temp <= 0)
        {
            cout<<"!!! error wrong number !!!\n     please try again"<<endl;
        }
    }
    main_market->add_currences(temp);
    cout<<"\n\n\n\n\nDo you want to see them? [y/n] ";
    cin>>temp1;
    if(temp1=="y")
    {
        main_market->toString();
    }
    cout<<"         *** Enter anything to go to the next step ***"<<endl;
    cin>>temp1;
    // start the trading process
    system("CLS");
    main_market->trader();

    return(0);
}
