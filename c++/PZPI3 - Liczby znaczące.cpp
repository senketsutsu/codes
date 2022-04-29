#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() 
{
    const int N = 1000000000;

    vector<int> powers;
    powers.reserve(sqrt(N));

    vector<bool> primes(100000);


    for (int i = 2; i <= sqrt(N); i++) 
    {
        if (!primes[i])
        {
            for (int j = i * i; j <= sqrt(N); j += i)
                primes[j] = true;
        }
    }

    for (int i = 2; i <= sqrt(N); i++)
    {
        if (!primes[i])
        {
            powers.push_back(i*i);
        }
    }


    int t;
    cin >> t;

    while (t--) 
    {
        int a, b;
        cin >> a >> b;
        int s = 0;
        for (int i = 0; i < powers.size(); i++) 
        {
            if (powers[i] > b)
                break;
            if (powers[i] >= a && powers[i] <= b)
                s++;
        }
        cout << s << endl;
    }
}
