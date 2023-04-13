#include "coldblooded.hpp"

using namespace std;

class Reptiles : public ColdBlooded
{
private:
    string *Subclass;
    int *numClass;

public:
    Reptiles(string, int, string, bool, int, int);
    ~Reptiles();
    virtual string toString();
    virtual int type();
    virtual int getID();
    virtual Animal* child(string,int,string,bool);
    friend class Breeding;
};

Reptiles::Reptiles(string newName, int newId, string newColor, bool newBloodRh, int Thermophysiology, int newSubclass) : ColdBlooded(newName, newId, newColor, newBloodRh, Thermophysiology)
{
    Subclass = new string;
    numClass = new int;
    *numClass = newSubclass;
    switch(newSubclass)
    {
    case 1:
        {
            *Subclass = "Anapsida";
            break;
        }
    case 2:
        {
            *Subclass = "Synapsida ";
            break;
        }
    case 3:
        {
            *Subclass = "Euryapsida ";
            break;
        }
    case 4:
        {
            *Subclass = "Diapsida";
            break;
        }
    default:
        {
            *Subclass = "Unknown";
            break;
        }
    }
}

Reptiles::~Reptiles()
{
    delete Subclass;
}

string Reptiles::toString()
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
    text += *Subclass;
    text += " subclass of reptiles) ";
    return (text);
}

int Reptiles::type()
{
    return (7);
}

int Reptiles::getID()
{
    return(*id);
}

Animal* Reptiles::child(string n, int i, string c, bool b)
{
    Animal *child = new Reptiles(n,i,c,b,*numTherm,*numClass);
    return child;
}
