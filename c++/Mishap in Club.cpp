#include<iostream>
#include<cmath>
#include<string>
 
 
using namespace std;
 
int main()
{
string a;
cin>>a;
int p=0,m=0,w=0;
for(int i=0;i<a.size();i++)
{
if(a[i]=='+'){w++;}else{w--;};
if(w>m){m=w;};
if(w<p){p=w;};
}
 
cout<<(m-p);
 
}
