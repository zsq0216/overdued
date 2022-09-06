#ifndef COMMODITY_H
#define COMMODITY_H
#include <string>

// class Commodity
class Commodity
{
public:
    // name of this commodity
    std::string m_name;

    // price of this commodity
    double m_price;

    // deadline of this commodity
    int m_deadline;

    // Initialize the name, price and dealine of this commodity
    Commodity(std::string n, double p, int d);

    // Do nothing
    ~Commodity();

    // Sort by expiration time
    bool operator < (const Commodity &a) const;
};
#endif