#include <iostream>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
int main()
{
    int n,s,w=0;
    cin>>n>>s;
    int h[n];
    cin>>h[0];
    w++;
    for(int i=1;i<n;i++)
    {
        cin>>h[i];
        if(fabs(h[i-1]-h[i])>=2*s)
        {
            if(fabs(h[i-1]-h[i])-2*s>0)
            {
                w=w+2;
                
            }else{w++;}
            
        }
        
    }
    w++;
    cout<<w;
    return 0;
}
