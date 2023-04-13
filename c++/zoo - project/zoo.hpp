#ifndef ZOO
#define ZOO

#include <string>
#include <iostream>
#include "linked_list_node.hpp"
#include "animal.hpp"
#include "warmblooded.hpp"
#include "mammals.hpp"
#include "birds.hpp"
#include "coldblooded.hpp"
#include "fish.hpp"
#include "reptiles.hpp"
#include "amphibians.hpp"

using namespace std;

template <class T> class Zoo
{
protected:
    string *name;
    int *number_of_animals;
    Linked_list_node *root;
    int *last_ani_num;

public:
    Zoo<T>(string, Linked_list_node *);
    ~Zoo<T>();
    Zoo<T> &operator+=(T *);
    Zoo<T> &operator-=(int);
    virtual int getNumAnimal();
    virtual int getNumOfAnimals();
    virtual void toStringv(); // to string but void
    virtual Linked_list_node* getRoot();
    // virtual string toString();
    // virtual void add(Animal);
};

template <class T> Zoo<T>::Zoo(string Name, Linked_list_node *Root)
{
    name = new string;
    *name = Name;

    root = Root;

    number_of_animals = new int;
    *number_of_animals = 0;
    last_ani_num = new int;
    *last_ani_num = 0;
}

template <class T> Zoo<T>::~Zoo()
{
    delete name;
    delete number_of_animals;
    delete root;
}

template <class T> Zoo<T> &Zoo<T>::operator+=(T *x)
{
    *(this->number_of_animals) += 1;
    *(this->last_ani_num) += 1;

    Linked_list_node *current = this->root;
    if (root->data == NULL)
    {
        this->root = new Linked_list_node(x);
        return (*this);
    }
    while ((*current).next != NULL)
    {
        current = (*current).next;
    }
    (*current).next = new Linked_list_node(x);
    return (*this);
}

template <class T> Zoo<T> &Zoo<T>::operator-=(int x)
{
    Linked_list_node *current = this->root;
    if (this->root->data == NULL)
    {
        return (*this);
    }
    if (this->root->data->getID() == x)
    {
        this->root = this->root->next;
        *(this->number_of_animals) -= 1;
        return (*this);
    }
    Linked_list_node *before = current;

    while (((*current).next != NULL))
    {
        before = current;
        current = (*current).next;
        if(current->data->getID() == x)
        {
            break;
        }

    }
    if(current->data->getID() == x)
    {

        before->next = current->next;
        *(this->number_of_animals) -= 1;
        //delete current;
    }

    return (*this);
}

template <class T> int Zoo<T>::getNumAnimal()
{
    /*
    int n = 1;
    if(this->root->data == NULL)
    {
        return(0);
    }
    Linked_list_node *current = root;
    while ((*current).next != NULL)
    {
        current = (*current).next;
        n++;
    }
    return(n);
    */
    return(*last_ani_num);
}

template <class T> int Zoo<T>::getNumOfAnimals()
{
    return ((*number_of_animals));
}


template <class T> void Zoo<T>::toStringv()
{
    Linked_list_node *current = root;

    if(current->data == NULL)
    {
        return;
    }

    cout << current->data->toString() << endl;

    while ((*current).next != NULL)
    {
        current = current->next;
        cout <<(*current).data->toString() << endl;

    }

    return;
}

template <class T> Linked_list_node* Zoo<T>::getRoot()
{
    return(root);
}

#endif // ZOO
