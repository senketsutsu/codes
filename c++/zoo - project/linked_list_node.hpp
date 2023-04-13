#ifndef LINKED_LIST_NODE_HPP
#define LINKED_LIST_NODE_HPP

#include <string>
#include <iostream>
#include "animal.hpp"

using namespace std;

struct Linked_list_node
{
    Animal* data;
    Linked_list_node* next;

    Linked_list_node(Animal*);
    ~Linked_list_node();
};

Linked_list_node::Linked_list_node(Animal *newAnimal)
{
    data = newAnimal;
    next = NULL;
}

Linked_list_node::~Linked_list_node()
{
    delete data;
    delete next;
}



#endif // LINKED_LIST_NODE_HPP
