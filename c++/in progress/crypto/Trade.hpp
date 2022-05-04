#ifndef TRADE
#define TRADE

#include <stdlib.h>
#include <ctime>


class Trade
{
private:
    float p_sell;
    float p_buy;
public:
    Trade(float, float);
    ~Trade();
    virtual bool trade(char);
};

Trade::Trade(float sell, float buy)
{
    p_sell = sell;
    p_buy = buy;
}

Trade::~Trade()
{
    delete &p_sell;
    delete &p_buy;
}

bool Trade::trade(char a)
    {
        srand (time(NULL));
        float x = (rand()%10)/10;
        if(a=='s')
        {
            return(x<p_sell);
        }
        if(a=='b')
        {
            return(x<p_buy);
        }
        return(false);
    }

#endif // TRADE

