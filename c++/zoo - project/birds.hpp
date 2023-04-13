//#ifndef BIRDS
//#define BIRDS


//#include "warmblooded.hpp"

using namespace std;

class Bird : public WarmBlooded
{
private:
    int *wingspan;

public:
    Bird(string, int, string, bool, int, int);
    ~Bird();
    virtual string toString();
    virtual int type();
    virtual int getID();
    virtual Animal* child(string,int,string,bool);
    friend class Breeding;
};

Bird::Bird(string newName, int newId, string newColor, bool newBloodRh, int temp, int newWingspan) : WarmBlooded(newName, newId, newColor, newBloodRh, temp)
{
    wingspan = new int;
    *wingspan = newWingspan;
}

Bird::~Bird()
{
    delete wingspan;
}

string Bird::toString()
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
    text += "wingspan ";
    text += to_string(*wingspan);
    text += " cm) ";
    return (text);
}

int Bird::type()
{
    return (4);
}
int Bird::getID()
{
    return(*id);
}
Animal* Bird::child(string n, int i, string c, bool b)
{
    Animal *child = new Bird(n,i,c,b,*AvgBodyTemp,*wingspan);
    return child;
}

//#endif // BIRDS
