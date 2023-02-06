#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class d_ray_maxheap
{
public:
    int n;                 // n_elements
    int d;                 // d_ray
    vector<int> arr = {0}; // arr[0] is not the element of the heap

    // randomly initialize arr and make it a d_ray_max_heap
    d_ray_maxheap(int i_n, int i_d)
    {
        n = i_n;
        d = i_d;
        srand((unsigned)time(NULL));
        for (int i = 1; i <= n; i++)
        {
            arr.push_back(rand() % 100);
        }
        build_maxheap();
    }

    // return i's parent node
    int i_parent(int i)
    {
        return (i - 2) / d + 1;
    }

    // return i's j-th child
    int i_child(int i, int j)
    {
        return d * (i - 1) + j + 1;
    }

    // key phase
    void maxHeapify(int p)
    {
        int size = arr.size() - 1;
        int largest = p;
        int child;
        for (int j = 1; j <= d; j++)
        {
            child = i_child(p, j);
            if (child <= size && arr[child] > arr[largest])
                largest = child;
            else if (child > size)
                break;
        }
        if (largest != p)
        {
            swap(arr[largest], arr[p]);
            maxHeapify(largest);
        }
    }

    // build a d_ray_max_heap
    void build_maxheap()
    {
        int size = arr.size() - 1;
        int begin = i_parent(size);
        for (int i = begin; i > 0; i--)
        {
            maxHeapify(i);
        }
    }

    int EXTRACT_MAX()
    {
        int size = arr.size() - 1;
        if (size < 1) // if size<1, that means arr only has arr[0], which is not the element of heap
        {
            cout << "heap underflow" << endl;
            return 0;
        }
        int max = arr[1];
        arr[1] = arr[size];
        arr.pop_back();
        maxHeapify(1);
        return max;
    }

    void INSERT(int x)
    {
        arr.push_back(x);
        int i = arr.size() - 1;
        int parent = i_parent(i);
        while (arr[i] > arr[parent])
        {
            swap(arr[i], arr[parent]);
            i = parent;
            parent = i_parent(parent);
        }
    }

    void INCREASE_KEY(int i, int k)
    {
        if (i >= arr.size())
            return;
        if (arr[i] > k)
            return;
        else
        {
            arr[i] = k;
            int parent = i_parent(i);
            while (arr[i] > arr[parent])
            {
                swap(arr[i], arr[parent]);
                i = parent;
                parent = i_parent(parent);
            }
        }
    }
};
int main()
{
    int n, d;
    cin >> n >> d;
    d_ray_maxheap Heap(n, d);
    for (int i = 1; i <= n; i++)
    {
        cout << Heap.arr[i] << " ";
    }
    cout << Heap.EXTRACT_MAX() << endl;
    Heap.INSERT(100);
    Heap.INCREASE_KEY(6, 100);
    for (int i = 1; i < Heap.arr.size(); i++)
    {
        cout << Heap.arr[i] << " ";
    }
    return 0;
}