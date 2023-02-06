#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#define MAX 100
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

void combineSort(vector<int> &arr, int left, int right, int k)
{
    if (right - left < k)
    {
        for (int i = left + 1; i <=right; ++i)
        {
            int key = arr[i];
            int j = i - 1;
            while (arr[j] > key && j >= left) // got wrong here initially
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
        return;
    }
    else
    {
        int mid = (left + right) / 2;
        combineSort(arr, left, mid + 1, k);      // in insertSort,the right boundary is not availib
        combineSort(arr, mid + 1, right + 1, k); // so if "right"but not "right + 1",the arr[right] will be ignored
        merge(arr, left, right);
    }
}
void selectK(vector<int> arr)
{
    typedef high_resolution_clock Clock;
    for (int k = 2; k < 10; ++k)
    {
        vector<int>temp=arr;
        auto start = Clock::now();
        combineSort(temp, 0, MAX, k);
        auto end = Clock::now();
        cout << endl
             << duration_cast<nanoseconds>(end - start).count() / 1e+9 << 's';
    }
}
int main()
{
    vector<int> arr;
    ifstream readIn;
    readIn.open("data.txt");
    int temp;
    while (!readIn.eof())
    {
        readIn >> temp;
        arr.push_back(temp);
    }
    //cout << "done" << endl;
    selectK(arr);
    typedef high_resolution_clock Clock;
    auto start = Clock::now();
    combineSort(arr, 0, MAX, 3);
    auto end = Clock::now();
    cout << endl
         << duration_cast<nanoseconds>(end - start).count() / 1e+9 << 's';
    return 0;
}
