#ifndef WARMBLOODED
#define WARMBLOODED

#include "animal.hpp"

using namespace std;

class WarmBlooded : public Animal
{
protected:
    int *AvgBodyTemp;

public:
    WarmBlooded(string, int, string, bool, int);
    ~WarmBlooded();
    virtual string toString();
    virtual int type();
    virtual int getID();
    virtual Animal* child(string,int,string,bool);
    friend class Breeding;
};

WarmBlooded::WarmBlooded(string newName, int newId, string newColor, bool newBloodRh, int temp) : Animal(newName, newId, newColor, newBloodRh)
{
    AvgBodyTemp = new int;
    *AvgBodyTemp = temp;
}

WarmBlooded::~WarmBlooded()
{
    delete AvgBodyTemp;
}

string WarmBlooded::toString()
{//cout<<"jest";
    string text = "";
    text += to_string(*id);
    text += ". ";
    text += *name;
    text += " (";
    text += *color;
    text += " color, Rh";
    if (*bloodRh)
    {
        text += "+ blood type, ";
    }
    else
    {
        text += "- blood type, ";
    }
    text += "avg. body temp. ";
    text += to_string(*AvgBodyTemp);
    text += "*C) ";
    return (text);
}

int WarmBlooded::type()
{
    return (2);
}
int WarmBlooded::getID()
{
    return(*id);
}

Animal* WarmBlooded::child(string n, int i, string c, bool b)
{
    Animal *child = new WarmBlooded(n,i,c,b,*AvgBodyTemp);
    return child;
}

#endif // WARMBLOODED
