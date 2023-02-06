#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>
#define MAX 1000000
#include<vector>
using namespace std;
using namespace chrono;

void insertSort(vector<int> & arr,int len)
{
    if(len==0&&len==1)return;
    for(int i=1;i<len;++i)
    {
        int key=arr[i];
        int j=i-1;
        while(arr[j]>key&&j>=0)
        {
            arr[j+1]=arr[j];
            --j;
        }
        arr[j+1]=key;
    }
    return;
}
int main()
{
    vector<int> arr;
    ifstream readIn;
    readIn.open("data.txt");
    int temp;
    int max=MAX;
    while(max--)
    {
        readIn>>temp;
        arr.push_back(temp);
    }
    typedef high_resolution_clock Clock;
    auto start=Clock::now();
	insertSort(arr,MAX);
    auto end=Clock::now();
    /*for(int i=0;i<MAX;++i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<MAX-1;++i)
    {
        if(arr[i]>arr[i+1])cout<<i;
    }*/
    cout<<endl<<duration_cast<nanoseconds>(end-start).count()/1e+9;
    return 0;
}

