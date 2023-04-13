//#ifndef MAMMALS
//#define MAMMALS


//#include "warmblooded.hpp"

using namespace std;

class Mammal : public WarmBlooded
{
private:
    int *LenMilkFeeded;

public:
    Mammal(string, int, string, bool, int, int);
    ~Mammal();
    virtual string toString();
    virtual int type();
    virtual int getID();
    virtual Animal* child(string,int,string,bool);
    friend class Breeding;
};

Mammal::Mammal(string newName, int newId, string newColor, bool newBloodRh, int temp, int Length_of_time_for_feeding_offspring_with_milk) : WarmBlooded(newName, newId, newColor, newBloodRh, temp)
{
    LenMilkFeeded = new int;
    *LenMilkFeeded = Length_of_time_for_feeding_offspring_with_milk;
}

Mammal::~Mammal()
{
    delete LenMilkFeeded;
}

string Mammal::toString()
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
    text += "*C, ";
    text += "len. of time for feeding offspring with milk ";
    text += to_string(*LenMilkFeeded);
    text += ") ";
    return (text);
}

int Mammal::type()
{
    return (3);
}
int Mammal::getID()
{
    return(*id);
}

Animal* Mammal::child(string n, int i, string c, bool b)
{
    Animal *child = new Mammal(n,i,c,b,*AvgBodyTemp,*LenMilkFeeded);
    return child;
}

//#endif // MAMMALS
