#include<iostream>
#include<fstream>
#include <cstdlib>
#include<ctime>
#define MAX 1600
using namespace std;

int main()
{
    ofstream out;
    out.open("data.txt");
    long long max=MAX;
    srand((unsigned)time(NULL));
    while(max--)
    {
        out<<rand()%20-10<<" ";
    }
    return 0;
}
