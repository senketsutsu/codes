#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <math.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <queue>

using namespace std;

struct student {
    int index;
    string surname;
    string name;

    void print() // prints info about an individual student
    {
        student tmp=*this;
        cout<<tmp.index<<". "<<tmp.surname<<" "<<tmp.name<<endl;
        return;
    }
};

struct node {
    student data;
    node *left;
    node *right;
    node *parent;

    void print() // prints data about the student and his kids
    {
        student a=this->data;
        cout<<"Parent:"<<endl;
        a.print();
        cout<<"Left:"<<endl;
        if(this->left==NULL){cout<<"none"<<endl;}else{((* this->left).data).print();}
        cout<<"Right:"<<endl;
        if(this->right==NULL){cout<<"none"<<endl;}else{((* this->right).data).print();}
    }
};

node *root=NULL;

node * min_node(node * x) // returns data of the student with the smallest index
{
    node *now=x;
    while(now->left!=NULL)
    {
        now=now->left;
    }
    return(now);
}

void add_node(student elem) // adds student to the tree in the correct place
{
    node * now=root;
    node * newnode =new node;
    // root->data == (*root).data
    newnode->data=elem;
    newnode->left=NULL;
    newnode->right=NULL;

    if(root==NULL)
    {
        newnode->parent=NULL;
        root=newnode;
        return;
    }else
    {
        while(now!=NULL)
        {
            if((now->data).index<=(newnode->data).index)
            {
                if(now->right==NULL)
                {
                    newnode->parent=now;
                    now->right=newnode;
                    return;
                }else{now=now->right;}
            }
            if((now->data).index>(newnode->data).index)
            {
                if(now->left==NULL)
                {
                    newnode->parent=now;
                    now->left=newnode;
                    return;
                }else{now=now->left;}
            }
        }
    }

}

void del_tree(node *elem=root) // kills the whole tree
{
    if(elem->left!=NULL){del_tree(elem->left);}
    if(elem->right!=NULL){del_tree(elem->right);}
    delete elem;
    return;
}

student add_student(string line) // gets studet data from a line of text
{
    string x="";
    int y=0;
    student a;
    int i=0;
    while(line[i]!=' ')
    {
        y*=10;
        y+=(char(line[i]) -'0');
        i++;
    }
    i++;
    a.index=y;
    x="";
    while(line[i]!=' ')
    {
        x+=line[i];
        i++;
    }
    a.surname=x;
    i++;
    x="";
    x=line.substr(i);
    a.name=x;
    return(a);
}

void delet_deepest(node * elem, node * d_elem)
{
    queue<node *> q;
    q.push(elem);

    node * tmp;
    while(!q.empty())
    {
        tmp=q.front();
        q.pop();
        if(tmp==d_elem)
        {
            tmp=NULL;
            delete(d_elem);
            return;
        }
        if(tmp->right)
        {
            if(tmp->right==d_elem)
            {
                tmp->right=NULL;
                delete(d_elem);
                return;
            }
            else{q.push(tmp->right);}
        }

        if(tmp->left)
        {
            if(tmp->left==d_elem)
            {
                tmp->left=NULL;
                delete(d_elem);
                return;
            }
            else{q.push(tmp->left);}
        }
    }
}

node * del_node(node * elem,int target) // kills one node and fixes the rest of the tree
{
    if(!elem){return(elem);}
    if(target<(elem->data).index)
    {
        root->left=del_node(elem->left,target);
    }
    else if(target>(elem->data).index)
    {
        elem->right=del_node(elem->right,target);
    }
    else{
        if(elem->left==NULL && elem->right==NULL)
        {
            return(NULL);
        }
        else{
            if(elem->left==NULL)
            {
                node * tmp= elem->right;
                free(elem);
                return(tmp);
            }
            else{
                if(elem->right==NULL)
                {
                    node * tmp=elem->left;
                    free(elem);
                    return(tmp);
                }
            }
        }
        node * tmp=min_node(elem->right);
        (elem->data).index=(tmp->data).index;
        (elem->data).name=(elem->data).name;
        (elem->data).surname=(elem->data).surname;
        elem->right=del_node(elem->right,(tmp->data).index);
    }
    return(elem);
}

int myrand(int i){return(rand()%i);} // randomising function

string fix(string a) // formats the string into tittle and fixes the len of the world
{
    string b="";
    b+=toupper(a[0]);
    for(int i=1;i<a.length();i++)
    {
        b+=tolower(a[i]);
    }
    for(int i=b.length();i<12;i++)
    {
        b+=char('a'+(rand() %26));
    }
    a="";
    for(int i=0;i<12;i++)
    {
        a+=b[i];
    }
    return(a);
}

student * find_node(int target) //finds node with given index number
{
    node *now=root;
    bool found=false;
    bool stop=false;
    if(now==NULL){return(NULL);}
    while(now!= NULL && !stop)
    {
        if((now->data).index==target)
        {
            found=true;
            stop=true;
            return(&(now->data));
        }
        else{
            if((now->data).index>target)
            {
                now=now->left;
            }
            else{
                now=now->right;
            }
        }
    }
    return(NULL);
}

student max_student() // returns data of the student with the biggest index
{
    node *now=root;
    while(now->right!=NULL)
    {
        now=now->right;
    }
    return(now->data);
}

student min_student() // returns data of the student with the smallest index
{
    node *now=root;
    while(now->left!=NULL)
    {
        now=now->left;
    }
    return(now->data);
}



int main()
{
    // getting students list

    fstream students_data;
    string line;
    fstream ex2add;
    ex2add.open("BSTtime_all_elem_add.txt", ios::in|ios::app);
    fstream ex2del;
    ex2del.open("BSTtime_all_elem_del.txt", ios::in|ios::app);
    int n;
    vector<int> tab;
    bool stop=true;
    students_data.open("data_ex3.txt", ios::in|ios::out);
    vector<student> students_list;
    vector<int> list_of_students_indexes;
    students_data>>n;
    getline(students_data,line);
    for(int i=0;i<n;i++)
    {
        getline(students_data,line);
        //cout<<line<<endl;
        students_list.push_back(add_student(line));
        list_of_students_indexes.push_back(students_list[i].index);
        //cout<<i<<endl;
    }

    // shuffle
    n=800000;

    random_shuffle(students_list.begin(),students_list.end(),myrand);
    random_shuffle(list_of_students_indexes.begin(),list_of_students_indexes.end(),myrand);

    // add to the tree
    double k=0,l=0;

    clock_t start,endu;

    for(int j=0;j<=n-10000;j+=20000)
    {
        for(int m=0;m<10;m++)
        {

            random_shuffle(students_list.begin(),students_list.end(),myrand);
            for(int i=0;i<j;i++)
            {
                add_node(students_list[i]);
            }

            for(int i=0;i<j+10000;i++)
            {
                tab.push_back(students_list[i].index);
            }
            random_shuffle(tab.begin(),tab.end(),myrand);
            start=clock();

            for(int i=j;i<j+10000;i++)
            {
                add_node(students_list[i]);
            }

            endu=clock();
            k+=double(endu-start)/double(CLOCKS_PER_SEC);
            root=NULL;

            //start=clock();

            //for(int i=0;i<j+10000;i++)
            //{
            //    root=del_node(root,tab[i]);
            //}

            //endu=clock();
            //l+=double(endu-start)/double(CLOCKS_PER_SEC);

        }
        ex2add<<"add "<<(j)<<" "<<double(k/10)<<"s"<<endl;
        //ex2del<<"del "<<(j)<<" "<<double(l/10)<<"s"<<endl;
        k=0;l=0;
    }

    students_data.close();
    ex2add.close();
    return(0);
}

