#include<iostream>
#include<string>
using namespace std;

class Commodity
{
public:
    const string m_name;
    const double m_price;
    const int m_deadline;

    Commodity(string n,double p,int d);
    ~Commodity();
    bool operator < (const Commodity & a)const;
};

Commodity::Commodity(string n,double p,int d):m_name(n),m_price(p),m_deadline(d){}


Commodity::~Commodity()
{
}
bool Commodity::operator < (const Commodity & a)const
{
    return this->m_deadline > a.m_deadline;
}
