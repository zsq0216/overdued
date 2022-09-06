#ifndef FAMILYMART_H
#define FAMILYMART_H
#include <string>
#include <map>
#include <queue>
#include "Commodity.h"
// TODO
//  you need to modify this file
//  you need to finish this class, but don't change the definition of the existing functions below.

class FamilyMart
{
public:
    FamilyMart(); // no commodity

    // using file name to construct FamilyMart
    // the format of the file is the same as purchase.txt
    FamilyMart(const std::string &cmmodity_file_name);

    // using file name to add new commodities every morning, the format of the file is the same as purchase.txt
    void purchase_file(const std::string &cmmodity_file_name);

    // the same as above, this is sell process
    void sell_file(const std::string &sell_file_name);

    // return a total sales, a turnover since the start of new FamilyMart.
    double show_turnover();

private:
    // storage of current commodities
    std::map<std::string, std::priority_queue<Commodity> > Goods;
   
    // total number of days since 2022.1.1
    int m_today;

    // total number of income since the start of new FamilyMart
    double m_turnover;

    // remove expired commodities after purchase_file
    void pop_overdue_morning();

    // remove expired commodities after the day is over
    void pop_overdue_night();

    // Gets an integer from the current position of the string
    int readInt(std::string &order, size_t &i);

    // return the the number of days since 2022.1.1 of current date
    int sumDay(int year, int month, int date);

    // return the deadline of this commodity
    int deadLine(int day, std::string goods_date);

    // gets a discount figure.If not, return 1
    double readDiscount(std::string &order);
};
#endif // FAMILYMART_H