//#ifndef FISH
//#define FISH

#include "coldblooded.hpp"

using namespace std;

class Fish : public ColdBlooded
{
private:
    string *ScaleType;
    int *numType;

public:
    Fish(string, int, string, bool, int, int);
    ~Fish();
    virtual string toString();
    virtual int type();
    virtual int getID();
    virtual Animal* child(string,int,string,bool);
    friend class Breeding;
};

Fish::Fish(string newName, int newId, string newColor, bool newBloodRh, int Thermophysiology, int scaleType) : ColdBlooded(newName, newId, newColor, newBloodRh, Thermophysiology)
{
    ScaleType = new string;
    numType = new int;
    *numType = scaleType;
    switch(scaleType)
    {
    case 1:
        {
            *ScaleType = "Placoid";
            break;
        }
    case 2:
        {
            *ScaleType = "Cosmoid";
            break;
        }
    case 3:
        {
            *ScaleType = "Ganoid";
            break;
        }
    case 4:
        {
            *ScaleType = "Cycloid and Ctenoid";
            break;
        }
    default:
        {
            *ScaleType = "Unknown";
            break;
        }
    }
}

Fish::~Fish()
{
    delete ScaleType;
}

string Fish::toString()
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
    text += " method to control its temperature, ";
    text += *ScaleType;
    text += " scales type) ";
    return (text);
}

int Fish::type()
{
    return (6);
}
int Fish::getID()
{
    return(*id);
}

Animal* Fish::child(string n, int i, string c, bool b)
{
    Animal *child = new Fish(n,i,c,b,*numTherm,*numType);
    return child;
}
//#endif // FISH
