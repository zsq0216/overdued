#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Student
{
    string key;
    string num;
    string major;
    string gender;
};

class hashtable
{
private:
    int m = 79;
    float sum = 0;
    Student T[79];

public:
    hashtable();
    ~hashtable();
    int gethashCode(string name);
    int func_1(int k);
    int func_2(int k);
    int doubHash(int k, int i);
    void display(Student x);
    Student HASH_SEARCH(string name);
    void HASH_INSERT(Student x);
    void HASH_DELETE(string name);
    float Evaluate();
};

hashtable::hashtable()
{
    for (int i = 0; i < m; ++i)
    {
        T[i].key = "";
        T[i].major = "";
        T[i].num = "";
        T[i].gender = "";
    }
}

hashtable::~hashtable()
{
}

int hashtable::gethashCode(string key)
{
    unsigned int seed = 131;
    unsigned int hash = 0;
    for (auto e : key)
    {
        hash = hash * seed + e;
    }
    return (hash & 0x7FFFFFFF);
}
int hashtable::func_1(int k)
{
    return k % m;
}
int hashtable::func_2(int k)
{
    return 1 + (k % (m - 2));
}
int hashtable::doubHash(int k, int i)
{
    return (func_1(k) + i * func_2(k)) % m;
}
Student hashtable::HASH_SEARCH(string name)
{
    int k = gethashCode(name);
    int i = 0;
    for (i; i < m; i++)
    {
        int j = doubHash(k, i);
        if (T[j].key == name)
        {
            // cout<<"times:"<<i+1<<"  ";
            // display(T[j]);
            sum += (i + 1);
            return T[j];
        }
        else if (T[j].key == "")
            break;
        else
            continue;
    }
    sum += (i + 1);
    cout << "Search Failure" << endl;
    return Student{"", "", "", ""};
}
void hashtable::HASH_INSERT(Student x)
{
    int k = gethashCode(x.key);
    for (int i = 0; i < m; i++)
    {
        int j = doubHash(k, i);
        if (T[j].key == "" || T[j].key == "DELETED")
        {
            T[j] = x;
            return;
        }
        else
            continue;
    }
    cout << "Insert Failure" << endl;
}
void hashtable::HASH_DELETE(string name)
{
    int k = gethashCode(name);
    for (int i = 0; i < m; i++)
    {
        int j = doubHash(k, i);
        if (T[j].key == name)
        {
            T[j].key = "DELETED";
            return;
        }
        else if (T[j].key == "")
            break;
        else
            continue;
    }
    cout << "Delete Failure" << endl;
}
void hashtable::display(Student x)
{
    cout << "name:" << x.key << "  ";
    cout << "number:" << x.num << "  ";
    cout << "major:" << x.major << "  ";
    cout << "gender:" << x.gender << endl;
}
float hashtable::Evaluate()
{
    ifstream readName;
    string temp;
    int count = 0;
    sum = 0;
    readName.open("name.txt");
    while (!readName.eof())
    {
        readName >> temp;
        HASH_SEARCH(temp);
        count++;
    }
    readName.close();
    cout << "ave=";
    return sum / count;
}
int main()
{
    hashtable t1;
    ifstream readIn;
    readIn.open("text.txt");
    Student temp;
    while (!readIn.eof())
    {
        readIn >> temp.num >> temp.key >> temp.major >> temp.gender;
        t1.HASH_INSERT(temp);
    }
    readIn.close();
    cout << t1.Evaluate();
    return 0;
}