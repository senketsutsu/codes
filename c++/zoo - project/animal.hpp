#ifndef ANIMAL
#define ANIMAL

using namespace std;

class Animal
{
protected:
    string *name;
    int *id;
    string *color;
    bool *bloodRh;

public:
    Animal(string, int, string, bool);
    ~Animal();
    // virtual void toStringv(); // to string but void
    virtual string toString();
    virtual int type();
    virtual int getID();
    virtual Animal* child(string,int,string,bool);
    friend class Breeding;
};

Animal::Animal(string newName, int newId, string newColor, bool newBloodRh)
{
    name = new string;
    id = new int;
    color = new string;
    bloodRh = new bool;

    *name = newName;
    *id = newId;
    *color = newColor;
    *bloodRh = newBloodRh;
}

Animal::~Animal()
{
    delete name;
    delete id;
    delete color;
    delete bloodRh;
}

string Animal::toString()
{
    //cout<<"jest";
    string text = "";
    text += to_string(*id);
    text += ". ";
    text += *name;
    text += " (";
    text += *color;
    text += " color, Rh";
    if (*bloodRh)
    {
        text += "+ blood type) ";
    }
    else
    {
        text += "- blood type) ";
    }
    return (text);
}

int Animal::type()
{
    return (1);
}

int Animal::getID()
{
    return(*id);
}

Animal* Animal::child(string n, int i, string c, bool b)
{
    Animal *child = new Animal(n,i,c,b);
    return child;
}

#endif // ANIMAL
