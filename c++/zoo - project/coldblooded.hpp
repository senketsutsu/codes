#ifndef COLDBLOODED
#define COLDBLOODED

#include "animal.hpp"

using namespace std;

class ColdBlooded : public Animal
{
protected:
    string *AnimalsThermophysiology;
    int *numTherm;

public:
    ColdBlooded(string, int, string, bool, int);
    ~ColdBlooded();
    virtual string toString();
    virtual int type();
    virtual int getID();
    virtual Animal* child(string,int,string,bool);
    friend class Breeding;
};

ColdBlooded::ColdBlooded(string newName, int newId, string newColor, bool newBloodRh, int Thermophysiology) : Animal(newName, newId, newColor, newBloodRh)
{
    AnimalsThermophysiology = new string;
    numTherm = new int;
    *numTherm = Thermophysiology;

    switch(Thermophysiology)
    {
    case 1:
        {
            *AnimalsThermophysiology = "Ectothermy";
            break;
        }
    case 2:
        {
            *AnimalsThermophysiology = "Poikilothermy";
            break;
        }
    case 3:
        {
            *AnimalsThermophysiology = "Bradymetabolism";
            break;
        }
    default:
        {
            *AnimalsThermophysiology = "Unknown";
            break;
        }
    }
}

ColdBlooded::~ColdBlooded()
{
    delete AnimalsThermophysiology;
}

string ColdBlooded::toString()
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
    text += "uses ";
    text += *AnimalsThermophysiology;
    text += " method to control its temperature) ";
    return (text);
}

int ColdBlooded::type()
{
    return (5);
}
int ColdBlooded::getID()
{
    return(*id);
}

Animal* ColdBlooded::child(string n, int i, string c, bool b)
{
    Animal *child = new ColdBlooded(n,i,c,b,*numTherm);
    return child;
}

#endif // COLDBLOODED
