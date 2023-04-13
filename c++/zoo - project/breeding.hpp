#ifndef BREEDING
#define BREEDING

using namespace std;

class Breeding
{
protected:
    float *pBreed;
    float *pExtinct;

public:
    Breeding(float, float);
    ~Breeding();
    virtual void breed(Zoo<Animal> *, Linked_list_node *, Linked_list_node *);
    virtual Linked_list_node* findMate(Linked_list_node *, Linked_list_node *);
};

Breeding::Breeding(float Breed, float Extinct)
{
    pBreed = new float;
    pExtinct = new float;

    *pBreed = Breed;
    *pExtinct = Extinct;
}

Breeding::~Breeding()
{
    delete pBreed;
    delete pExtinct;
}

void Breeding::breed(Zoo<Animal> *where, Linked_list_node *OurMate, Linked_list_node *root)
{
    int random_number = 0;

    // czy jest puste
    if (root->data == NULL)
    {
        cout<<"The zoo is empty"<<endl;
        return;
    }

    // jezeli sa conajmniej dwa animals to breed
    if(where->getNumOfAnimals()>=2)
    {
        random_number = rand()%100;
        if(random_number<=int(*pBreed *100))
        {
            cout<<"\n-------------------------\nParents:"<<endl;
            cout<<OurMate->data->toString()<<endl;

            Linked_list_node *Mate = findMate(OurMate,root);
            cout<<Mate->data->toString()<<endl;

            Animal *child;
            string name = *(Mate->data->name);
            name[0] = (* OurMate->data->name)[0];

            child = Mate->data->child(name , where->getNumAnimal() , *(OurMate->data->color) , *(OurMate->data->bloodRh));

            cout<<"Child: \n"<<child->toString()<<endl;
            (*where) += child;
        }
    }

     random_number = rand()%100;

    if(random_number<=int(*pExtinct *100))
    {
        cout<<"\n-------------------------\n[*] "<<OurMate->data->toString()<<endl;
        (*where) -= OurMate->data->getID();
    }

    return;

}

Linked_list_node* Breeding::findMate(Linked_list_node *OurMate, Linked_list_node *root)
{
    Linked_list_node *current = OurMate;
    int n = rand()%100;

    for(int i=0;i<n;i++)
    {
        if(current->next == NULL)
        {
            current = root;
        }
        else{
            current = current->next;
        }
        if(current->data->getID() == OurMate->data->getID())
        {
            if(current->next != NULL)
            {
                current = current->next;
            }
            else{
                current = root;
            }
        }

    }
    if(current->data->getID() == OurMate->data->getID())
    {
        if(current->next != NULL)
        {
            current = current->next;
        }
        else{
            current = root;
        }
    }
    return(current);
}

#endif // BREEDING

