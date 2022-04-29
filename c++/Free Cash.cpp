#include<iostream>
#include<cmath>
 
using namespace std;
 
int main()
{
int n;
cin>>n;
int h[n],m[n],l[n+1];
int k=1;
cin>>h[0]>>m[0];l[0]=1;l[1]=1;
for(int i=1;i<n;i++)
{
l[i+1]=1;
cin>>h[i]>>m[i];
if((h[i]==h[i-1])&&(m[i]==m[i-1])){l[i]=l[i-1]+1;};
if(l[i]>k){k=l[i];};
}
cout<<k;
return(0);
}
