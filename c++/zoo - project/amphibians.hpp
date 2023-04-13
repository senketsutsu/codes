#include "coldblooded.hpp"

using namespace std;

class Amphibians : public ColdBlooded
{
private:
    string *Subtype;
    int *numSub;

public:
    Amphibians(string, int, string, bool, int, int);
    ~Amphibians();
    virtual string toString();
    virtual int type();
    virtual int getID();
    virtual Animal* child(string,int,string,bool);
    friend class Breeding;
};

Amphibians::Amphibians(string newName, int newId, string newColor, bool newBloodRh, int Thermophysiology, int newSubtype) : ColdBlooded(newName, newId, newColor, newBloodRh, Thermophysiology)
{
    Subtype = new string;
    numSub = new int;
    *numSub = newSubtype;
    switch(newSubtype)
    {
    case 1:
        {
            *Subtype = "Anura";
            break;
        }
    case 2:
        {
            *Subtype = "Caudata ";
            break;
        }
    case 3:
        {
            *Subtype = "Gymnophiona ";
            break;
        }
    default:
        {
            *Subtype = "Unknown";
            break;
        }
    }
}

Amphibians::~Amphibians()
{
    delete Subtype;
}

string Amphibians::toString()
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
    text += *Subtype;
    text += " order) ";
    return (text);
}

int Amphibians::type()
{
    return (8);
}

int Amphibians::getID()
{
    return(*id);
}

Animal* Amphibians::child(string n, int i, string c, bool b)
{
    Animal *child = new Amphibians(n,i,c,b,*numTherm,*numSub);
    return child;
}
