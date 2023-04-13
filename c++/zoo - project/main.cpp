#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "zoo.hpp"
#include "linked_list_node.hpp"
#include "breeding.hpp"

using namespace std;

string random_name()
{
    //srand (time(NULL));
    int len=rand()%14;
    string a[14]={"Abigail" , "Ace" , "Amos" , "Augie" , "Barkley" , "Ben" , "Gus" , "Heidi" , "Hunter" , "Jamie" , "Jetta" , "Misty" , "Pearl" , "Silver"};

    return(a[len]);
}

int main()
{
    cin.clear();
    srand (time(NULL));

    Linked_list_node *root = new Linked_list_node(NULL);
    cout << "Enter the name of your Zoo: ";
    string zooName;
    cin >> zooName;
    Zoo<Animal> *OurZoo = new Zoo<Animal>(zooName, root);
    bool keepGoing = true;
    int option = 0;
    int option2 = 0;
    int option3 = 0;
    string names[14]={"Abigail" , "Ace" , "Amos" , "Augie" , "Barkley" , "Ben" , "Gus" , "Heidi" , "Hunter" , "Jamie" , "Jetta" , "Misty" , "Pearl" , "Silver"};
    string colors[12]={"red","orange","yellow","green","cyan","blue","violet","black","gray","white","purple","brown"};
    system("CLS");

    do
    {
        system("CLS");
        //---------------------------------------------------------------------------------------------------------------- MENU

        cout << "--- " << zooName << " ZOO ---\n\n\n"
             << endl;
        cout << " 1) Add animals \n 2) Breed animals\n 3) List all animals\n 4) Del animal\n 5) Breed\n 6) Exit\n"
             << endl;
        option = 0;
        cout << " Choose action: ";
        cin >> option;
        switch (option)
        {
        case 1:
            {
                system("CLS");
                cout << " 1) Add 1 animal \n 2) Add n random Animals\n (other) Exit\n"
                     << endl;
                option2 = 0;
                cout << " Choose action: ";
                cin >> option2;
                switch (option2)
                {
                case 1:
                {
                    cout << " 1) Animal\n\t 2) Warm-blooded\n\t\t 3) Mammal\n\t\t 4) Bird\n\t 5) Cold-blooded\n\t\t 6) Fish\n\t\t 7) Reptile\n\t\t 8) Amphibian" << endl;
                    option3 = 0;
                    cout << " Choose option: ";
                    cin >> option3;
                    Animal *newOne;
                    string *name = new string;
                    cout << "\n\n Name: ";
                    cin >> (*name);
                    string *color = new string;
                    cout << " Color: ";
                    cin >> (*color);
                    bool *rh = new bool;
                    cout << " Rh blood group (0 for - and 1 for +): ";
                    cin >> (*rh);
                    switch (option3)
                    {
                    case 1:
                    {
                        newOne = new Animal(*name, ((OurZoo->getNumAnimal())), *color, *rh);
                        (*OurZoo) += newOne;
                        delete name;
                        delete color;
                        delete rh;
                        break;
                    }

                    case 2:
                    {
                        int *bodyTemp = new int;
                        cout << " Average body temp. (*C): ";
                        cin >> (*bodyTemp);
                        newOne = new WarmBlooded(*name, ((OurZoo->getNumAnimal())), *color, *rh, *bodyTemp);
                        (*OurZoo) += newOne;
                        delete name;
                        delete color;
                        delete rh;
                        delete bodyTemp;
                        break;
                    }

                    case 3:
                    {
                        int *bodyTemp = new int;
                        cout << " Average body temp. (*C): ";
                        cin >> (*bodyTemp);
                        int *LenMilkFeeded = new int;
                        cout << " Len. of time for feeding offspring with milk (days): ";
                        cin >> (*LenMilkFeeded);
                        newOne = new Mammal(*name, ((OurZoo->getNumAnimal())), *color, *rh, *bodyTemp, *LenMilkFeeded);
                        (*OurZoo) += newOne;
                        delete name;
                        delete color;
                        delete rh;
                        delete bodyTemp;
                        delete LenMilkFeeded;
                        break;
                    }
                    case 4:
                    {
                        int *bodyTemp = new int;
                        cout << " Average body temp. (*C): ";
                        cin >> (*bodyTemp);
                        int *wingspan = new int;
                        cout << " Wingspan (cm): ";
                        cin >> (*wingspan);
                        newOne = new Bird(*name, ((OurZoo->getNumAnimal())), *color, *rh, *bodyTemp, *wingspan);
                        (*OurZoo) += newOne;
                        delete name;
                        delete color;
                        delete rh;
                        delete bodyTemp;
                        delete wingspan;
                        break;
                    }
                    case 5:
                    {
                        int *bodyTerm = new int;
                        cout << "\n Determine  animal's thermophysiology:\n\t 1) Ectothermy, controlling body temperature through external processes, such as by basking in the sun \n\t 2) Poikilothermy, the ability of an organism to function over a wide internal temperature range\n\t 3) Bradymetabolism, the ability to greatly alter metabolic rate in response to need; for example, animals that hibernate \n\t 4) Unknown\n\n";
                        cout<<" Enter the number: ";
                        cin >> (*bodyTerm);
                        newOne = new ColdBlooded(*name, ((OurZoo->getNumAnimal())), *color, *rh, *bodyTerm);
                        (*OurZoo) += newOne;
                        delete name;
                        delete color;
                        delete rh;
                        delete bodyTerm;
                        break;

                    }
                    case 6:
                    {
                        int *bodyTerm = new int;
                        cout << "\n Determine  animal's thermophysiology:\n\t 1) Ectothermy, controlling body temperature through external processes, such as by basking in the sun \n\t 2) Poikilothermy, the ability of an organism to function over a wide internal temperature range\n\t 3) Bradymetabolism, the ability to greatly alter metabolic rate in response to need; for example, animals that hibernate \n\t 4) Unknown\n\n";
                        cout<<" Enter the number: ";
                        cin >> (*bodyTerm);
                        int *scale = new int;
                        cout << "\n Scales type:\n\t 1) Placoid (sharks and rays) \n\t 2) Cosmoid (lungfishes and some fossil fishes) \n\t 3) Ganoid (bichirs , Bowfin, paddlefishes, gars, sturgeons) \n\t 4) Cycloid and Ctenoid (most bony fishes)\n\t 5) Unknown\n\n";
                        cout<<" Enter the number: ";
                        cin >> (*scale);
                        newOne = new Fish(*name, ((OurZoo->getNumAnimal())), *color, *rh, *bodyTerm, *scale);
                        (*OurZoo) += newOne;
                        delete name;
                        delete color;
                        delete rh;
                        delete bodyTerm;
                        delete scale;
                        break;
                    }
                    case 7:
                    {
                        int *bodyTerm = new int;
                        cout << "\n Determine  animal's thermophysiology:\n\t 1) Ectothermy, controlling body temperature through external processes, such as by basking in the sun \n\t 2) Poikilothermy, the ability of an organism to function over a wide internal temperature range\n\t 3) Bradymetabolism, the ability to greatly alter metabolic rate in response to need; for example, animals that hibernate \n\t 4) Unknown\n\n";
                        cout<<" Enter the number: ";
                        cin >> (*bodyTerm);
                        int *subclasses  = new int;
                        cout << "\n Subclass based on the number and position of temporal fenestrae:\n\t 1) Anapsida - no fenestrae \n\t 2) Synapsida - one low fenestra  \n\t 3) Euryapsida - one high fenestra \n\t 4) Diapsida - two fenestrae\n\t 5) Unknown\n\n";
                        cout<<" Enter the number: ";
                        cin >> (*subclasses );
                        newOne = new Fish(*name, ((OurZoo->getNumAnimal())), *color, *rh, *bodyTerm, *subclasses );
                        (*OurZoo) += newOne;
                        delete name;
                        delete color;
                        delete rh;
                        delete bodyTerm;
                        delete subclasses ;
                        break;
                    }
                    case 8:
                    {
                        int *bodyTerm = new int;
                        cout << "\n Determine  animal's thermophysiology:\n\t 1) Ectothermy, controlling body temperature through external processes, such as by basking in the sun \n\t 2) Poikilothermy, the ability of an organism to function over a wide internal temperature range\n\t 3) Bradymetabolism, the ability to greatly alter metabolic rate in response to need; for example, animals that hibernate \n\t 4) Unknown\n\n";
                        cout<<" Enter the number: ";
                        cin >> (*bodyTerm);
                        int *type = new int;
                        cout << "\n Scales type:\n\t 1) Anura (no tail) \n\t 2) Caudata (tail) \n\t 3) Gymnophiona (snake/worm -like) \n\t 4) Unknown\n\n";
                        cout<<" Enter the number: ";
                        cin >> (*type);
                        newOne = new Fish(*name, ((OurZoo->getNumAnimal())), *color, *rh, *bodyTerm, *type);
                        (*OurZoo) += newOne;
                        delete name;
                        delete color;
                        delete rh;
                        delete bodyTerm;
                        delete type;
                        break;
                    }
                    }
                    break;
                }
                case 2:
                {
                    cout << "\n\n The max number of animals in the ZOO is 100 !" << endl;
                    cout << " Currently there are " << (OurZoo->getNumAnimal()) << " so there are " << (100 - (OurZoo->getNumAnimal())) << " free spots in the ZOO." << endl;
                    cout << "\n\n n: ";
                    int *n = new int;
                    cin >> (*n);

                    for(int i=0;i<*n;i++)
                    {
                        int index = 0;
                        index = rand()%8;
                        Animal *newAnimal;

                        switch(index)
                        {
                        case 0:
                            {
                                newAnimal = new Animal(names[rand()%14],((OurZoo->getNumAnimal())),colors[rand()%12],rand()%2);
                                (*OurZoo) += newAnimal;
                                break;
                            }
                        case 1:
                            {
                                newAnimal = new WarmBlooded(names[rand()%14],((OurZoo->getNumAnimal())),colors[rand()%12],rand()%2,rand()%100);
                                (*OurZoo) += newAnimal;
                                break;
                            }
                        case 2:
                            {
                                newAnimal = new Mammal(names[rand()%14],((OurZoo->getNumAnimal())),colors[rand()%12],rand()%2,rand()%100,1+(rand()%365));
                                (*OurZoo) += newAnimal;
                                break;
                            }
                        case 3:
                            {
                                newAnimal = new Bird(names[rand()%14],((OurZoo->getNumAnimal())),colors[rand()%12],rand()%2,rand()%100,1+(rand()%200));
                                (*OurZoo) += newAnimal;
                                break;
                            }
                        case 4:
                            {
                                newAnimal = new ColdBlooded(names[rand()%14],((OurZoo->getNumAnimal())),colors[rand()%12],rand()%2, rand()%4);
                                (*OurZoo) += newAnimal;
                                break;
                            }
                        case 5:
                            {
                                newAnimal = new Fish(names[rand()%14],((OurZoo->getNumAnimal())),colors[rand()%12],rand()%2,rand()%4,rand()%5);
                                (*OurZoo) += newAnimal;
                                break;
                            }
                        case 6:
                            {
                                newAnimal = new Reptiles(names[rand()%14],((OurZoo->getNumAnimal())),colors[rand()%12],rand()%2,rand()%4,rand()%4);
                                (*OurZoo) += newAnimal;
                                break;
                            }
                        case 7:
                            {
                                newAnimal = new Amphibians(names[rand()%14],((OurZoo->getNumAnimal())),colors[rand()%12],rand()%2,rand()%4,rand()%4);
                                (*OurZoo) += newAnimal;
                                break;
                            }

                        }
                    }


                    delete n;
                    break;
                }
                }
                break;
            }


        case 2:
            {
                system("CLS");
                break;
            }

        case 3:
            {
                system("CLS");
                OurZoo->toStringv();
                cout << " --- ENTER ANY NUMBER TO GO BACK TO MENU ---" << endl;
                cin >> option3;
                break;
            }
        case 4:
            {
                cout<<"Enter animals id: ";
                int *id = new int;
                cin>>*id;
                (*OurZoo) -= *id;
                break;
            }
        case 5:
            {
                cout<<"If you want to reach the size 100 of the zoo then pBreed > pExtinct"<<endl;
                cout<<"Breed probability: ";
                float * b = new float;
                cin>>*b;
                cout<<"Extinct probability: ";
                float * e = new float;
                cin>>*e;

                Linked_list_node *current = OurZoo->getRoot();
                Linked_list_node *next;
                Breeding *BreedOrDie = new Breeding(*b,*e);

                // breed one
                //BreedOrDie->breed(OurZoo,OurZoo->getRoot(),OurZoo->getRoot());


                while(OurZoo->getNumOfAnimals()<100)
                {
                    //cout<<OurZoo->getNumOfAnimals()<<endl;
                    if(OurZoo->getNumOfAnimals()<1)
                    {
                        break;
                    }

                    if(current->next != NULL)
                    {
                        next = current->next;
                    }
                    else{
                        next = OurZoo->getRoot();
                    }

                    BreedOrDie->breed(OurZoo,current,OurZoo->getRoot());
                    current = next;
                }


                cout << " --- ENTER ANY NUMBER TO GO BACK TO MENU ---" << endl;
                cin >> option3;
                delete b;
                delete e;
                break;
            }
        case 6:
            {
                keepGoing = false;
                break;
            }

        }
    } while (keepGoing);

    delete OurZoo;


    return (0);
}
