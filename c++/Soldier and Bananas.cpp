#include <iostream>
 
using namespace std;
 
int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    int w=1;
    w=(1+c);
    w=w*c;
    w=w/2;
    w=w*a;
    w=w-b;
    if(w<0){w=0;}
    cout<<w;
 
    return 0;
}
