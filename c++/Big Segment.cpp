#include<iostream>
#include<cmath>
 
using namespace std;
 
int main()
{
int n;
cin>>n;
int r[n],l[n],w=0;
cin>>r[0]>>l[0];
int M=r[0],m=l[0];
for(int i=1;i<n;i++)
{
cin>>r[i]>>l[i];
if(r[i]<M){M=r[i];};
if(l[i]>m){m=l[i];};
}
for(int i=0;i<n;i++)
{
if((r[i]==M)&&(l[i]==m)){cout<<(i+1)<<endl;w=w+1;};
}
if(w==0){cout<<"-1";};
return(0);
}
