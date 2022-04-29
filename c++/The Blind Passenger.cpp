#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
void mi(int a)
{
    if(a==1){cout<<"poor conductor"<<endl;}
    else{
    cout<<(((a-2)/5)+1)<<" ";
    
        if(a%10==1||a%10==2||a%10==6||a%10==7){cout<<"W ";}else{if(a%10==5||a%10==8){cout<<"M ";}else{cout<<"A ";}}
        if(a%10==1||a%10==2||a%10==3||a%10==0){cout<<"L"<<endl;}else{cout<<"R"<<endl;}
        
}}

int main() {
    int ile;
    cin>>ile;
    int a[ile];
    for(int i=0;i<ile;i=i+1)
    {
        cin>>a[i];
    }
    for(int i=0;i<ile;i=i+1)
    {
        mi(a[i]);
    }
    
    return 0;
}
