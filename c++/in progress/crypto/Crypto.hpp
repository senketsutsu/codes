#ifndef CRYPTO
#define CRYPTO

#include "Money.hpp"

using namespace std;

class Crypto: public Money
{
private:
    string * user_id;
public:
    Crypto(string, int, float, string);
    ~Crypto();
    virtual void add(string);
    virtual void del();
};

Crypto::Crypto(string new_name, int new_id, float new_exchange_rate, string id) : Money( new_name,  new_id,  new_exchange_rate)
{
    user_id = new string;
    *user_id = id;
}
Crypto::~Crypto()
{
    delete user_id;
}
void Crypto::add(string id)
{
    *user_id = id;
}
void Crypto::del()
{
    *user_id = "none";
}

#endif // CRYPTO
