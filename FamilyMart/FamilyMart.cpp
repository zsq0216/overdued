#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <queue>
#include"FamilyMart.h"
using namespace std;

// Initialize the name, price and dealine of this commodity
Commodity::Commodity(string n, double p, int d) : m_name(n), m_price(p), m_deadline(d) {}

// Do nothing
Commodity::~Commodity()
{
}

// Sort by expiration time,the ones with early deadlines come first
bool Commodity::operator<(const Commodity &a) const
{
    return this->m_deadline > a.m_deadline;
}

// 122 if the sum of days from 2022.1.1 to 2022.5.2
// the original sales is 0
FamilyMart::FamilyMart() : m_today(122), m_turnover(0) {}

// using file name to construct FamilyMart
// and the other operations are the same with the above one
FamilyMart::FamilyMart(const std::string &cmmodity_file_name)
{
    m_today = 122;
    m_turnover = 0;
    purchase_file(cmmodity_file_name);
}

// using file name to add new commodities every morning
void FamilyMart::purchase_file(const std::string &cmmodity_file_name)
{
    ifstream readPurchase(cmmodity_file_name, ios::in);
    string buf;     // first line of the file
    string g_name;  // name
    double g_price; // price
    int g_day;      // life(days)
    string g_date;  // product_date
    if (!readPurchase.is_open())    // cannot open the file
    {
        cout << "fail to open the file" << endl;
        return;
    }
    getline(readPurchase, buf);     // Preprocess the first line of the file
    while (true)
    {
        if (readPurchase.eof())     // the end of the file
            break;
        if (!(readPurchase >> g_name >> g_price >> g_day >> g_date))
            continue;               // especially for the last line of the file

        Goods[g_name].push(Commodity(g_name, g_price, deadLine(g_day, g_date)));
    }
    readPurchase.close();
    pop_overdue_morning();          // remove expired commodities
}

// this is sell process
void FamilyMart::sell_file(const std::string &sell_file_name)
{
    ifstream readSell(sell_file_name, ios::in);
    string buf;         // first line of the file
    string g_name;      // commodity_name
    string g_discount;  // discount
    if (!readSell.is_open())    //cannot open the file
    {
        cout << "fail to open the file" << endl;
        return;
    }
    getline(readSell, buf);         // Preprocess the first line of the file
    while (true)
    {
        if (readSell.eof())         // the end of the file
            break;
        if (!(readSell >> g_name))
            continue;               // especially for the last line of the file
        getline(readSell, g_discount);

        // determines whether the commodity is in the map
        map<string, priority_queue<Commodity> >::iterator it = Goods.find(g_name);
        if (it == Goods.end())      // commodity is not in the map
            continue;
        if (!Goods[g_name].empty()) // sell only when available
        {
            m_turnover += Goods[g_name].top().m_price * readDiscount(g_discount);
            Goods[g_name].pop();
        }
        else
            continue;
    }
    readSell.close();
    pop_overdue_night();            // remove expired commodities
    ++m_today;                      // total number of days plus
}

// return a total sales, a turnover since the start of new FamilyMart
double FamilyMart::show_turnover()
{
    return m_turnover;
}

// remove expired commodities after purchase_file
void FamilyMart::pop_overdue_morning()
{
    map<string, priority_queue<Commodity> >::iterator it;
    for (it = Goods.begin(); it != Goods.end(); ++it)
    {
        while (it->second.top().m_deadline <= m_today)
        {
            if (it->second.empty())
                break;
            it->second.pop();
        }
    }
}

// remove expired commodities after the day is over
void FamilyMart::pop_overdue_night()
{
    map<string, priority_queue<Commodity> >::iterator it;
    for (it = Goods.begin(); it != Goods.end(); ++it)
    {
        while (it->second.top().m_deadline <= m_today + 1)
        {
            if (it->second.empty())
                break;
            it->second.pop();
        }
    }
}

// Gets an integer from the current position of the string
int FamilyMart::readInt(string &order, size_t &i)
{
    int s = 0;
    char ch = order[i++];
    while (ch > '9' || ch < '0')
    {
        if (i > order.size())
            return s;
        ch = order[i++];
    }
    while (ch >= '0' && ch <= '9')
    {
        if (i > order.size())
            return s;
        s = (s << 1) + (s << 3) + ch - '0';
        ch = order[i++];
    }
    return s;
}

// return the the number of days since 2022.1.1 of current date
int FamilyMart::sumDay(int year, int month, int date)
{
    // the number of days of every month
    // leap year is not in consideration
    int a[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int sum = date;
    for (int i = 1; i <= month - 1; i++)
    {
        sum += a[i];
    }
    sum += (year - 2022) * 365;
    return sum;
}

// return the deadline of this commodity
int FamilyMart::deadLine(int day, string goods_date)
{
    int overdate = day;
    size_t i = 0;
    int year = readInt(goods_date, i);
    int month = readInt(goods_date, i);
    int date = readInt(goods_date, i);
    overdate += sumDay(year, month, date);
    return overdate;
}

// gets a discount figure.If not, return 1
double FamilyMart::readDiscount(string &order)
{
    int i = 0;          // index
    double ans = 1;     // decimal digits
    double res = 0;     // total decimal
    char ch = order[i++];
    while (ch != '.')
    {
        if (i > order.size())
            return ans;
        ch = order[i++];
    }
    ch = order[i++];    // value in each decimal digits
    while (ch >= '0' && ch <= '9')
    {
        if (i > order.size())
            break;
        ans /= 10;
        res += ans * (ch - '0');
        ch = order[i++];
    }
    return res;
}