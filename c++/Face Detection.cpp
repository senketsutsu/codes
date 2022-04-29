#include <iostream>
#include <cmath>
#include <string>
 
using namespace std;
 
int main()
{
    int m,n;
    cin>>m>>n;
    string tab[m];
    int c[4]={0,0,0,0},w=0;
    for(int i=0;i<m;i++)
    {
        cin>>tab[i];
    }
    for(int i=0;i<m-1;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            c[0]=0;c[1]=0;c[2]=0;c[3]=0;
            if(tab[i][j]=='f'){c[0]++;}
            if(tab[i][j]=='a'){c[1]++;}
            if(tab[i][j]=='c'){c[2]++;}
            if(tab[i][j]=='e'){c[3]++;}
            if(tab[i][j+1]=='f'){c[0]++;}
            if(tab[i][j+1]=='a'){c[1]++;}
            if(tab[i][j+1]=='c'){c[2]++;}
            if(tab[i][j+1]=='e'){c[3]++;}
            if(tab[i+1][j]=='f'){c[0]++;}
            if(tab[i+1][j]=='a'){c[1]++;}
            if(tab[i+1][j]=='c'){c[2]++;}
            if(tab[i+1][j]=='e'){c[3]++;}
            if(tab[i+1][j+1]=='f'){c[0]++;}
            if(tab[i+1][j+1]=='a'){c[1]++;}
            if(tab[i+1][j+1]=='c'){c[2]++;}
            if(tab[i+1][j+1]=='e'){c[3]++;}
            if(c[0]*c[1]*c[2]*c[3]==1){w++;}
        }
    }
    cout<<w;
}
