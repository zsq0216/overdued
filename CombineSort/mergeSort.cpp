#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#define MAX 10000000
using namespace std;
using namespace chrono;

void merge(vector<int> &arr, int left, int right)
{
    int mid = (left + right) / 2;
    int i = left, j = mid + 1, k = 0;
    vector<int> temp(right - left + 1);
    while (i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];
    for (int i = left; i <= right; ++i)
    {
        arr[i] = temp[i - left];
    }
}
void mergeSort(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, right);
}

int main()
{
    vector<int> arr;
    ifstream readIn;
    readIn.open("data.txt");
    int temp;
    int max = MAX;
    while (max--)
    {
        readIn >> temp;
        arr.push_back(temp);
    }
    typedef high_resolution_clock Clock;
    auto start = Clock::now();
    mergeSort(arr, 0, MAX - 1);
    auto end = Clock::now();

    /*for(int i=0;i<MAX;++i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;*/
    for (int i = 0; i < MAX - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
            cout << i;
    }
    cout << endl
         << duration_cast<nanoseconds>(end - start).count() / 1e+9 ;
    return 0;
};
