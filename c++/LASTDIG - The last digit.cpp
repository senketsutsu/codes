#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int idk(int n, long long p, int m){
    if(p == 0) return 1;
    if(p & 1)
        return (n % m * idk((n*n) % m, p / 2, m) % m) % m;
    return idk((n*n) % m, p / 2, m) % m;
}

int main(){
    int t; cin>>t;
    for(int i=0; i<t; i++){
        int a; long long b;
        cin>>a>>b;
        cout<<idk(a, b, 10)<<endl;
    }
    return 0;
}
