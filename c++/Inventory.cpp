#include <iostream>
#include <cmath>
 
 
using namespace std;
 
int main()
{
   int i,x=1,n=100000;
   cin>>i;
   int tab[n+1];int ta[i],t[n+1];
   for(int j=0;j<=n;j++)
   {
      tab[j]=0;
      t[j]=0;
   }
   for(int j=0;j<i;j++)
   {
      cin>>ta[j];
      tab[ta[j]]++;
   }
   int k[i];
   while(tab[x]!=0){x++;}
   for(int j=0;j<i;j++)
   {
      while(tab[x]!=0){x++;}
      if(t[ta[j]]==0&&ta[j]<=i){k[j]=ta[j];t[ta[j]]=1;}else{k[j]=x;tab[x]=1;}
    }
    for(int j=0;j<i;j++)
    {cout<<k[j]<<" ";}
 
return(0);
}
