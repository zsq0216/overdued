# Lab3设计文档

### 如何在一个数组中表示d叉堆

* 若堆中有n个元素，则用数组下标的1~n表示相应元素，数组中的下标i对应堆中第i个节点。特别地，数组arr[0]不用于堆元素的储存。
* 元素也按照从上到下，从左到右的顺序在数组中排列
* 对于第i个元素：
  * 它的父节点为(i - 2) / d + 1.
  * 在不超过数组长度的前提下，它的第j个子节点为d*(i − 1) + j + 1.(1<=j<=d)
  * 以n=9,d=3为例：
![alt](1.1.png)

### 包含n个元素的d叉堆的高度是多少

$h=⌊\log_d{(d−1)n}⌋$


证明：
* 设堆的高度为h，元素个数可由等比数列求和得到：
  * 元素最少个数n(min)=$(1+d+d^2+……+d^{h-1})+1=(d^h+d-2)/(d-1)$
  * 元素最大个数n(max)=$1+d+d^2+……+d^h=(d^{h+1}-1)/(d-1)$
  * 解方程得$d^h+d-2\leq (d-1)*n \leq d^{h+1}-1 $
  * 由于d>=2,易得(d-1)*n位于区间[$d^h$,$d^{h+1}-1$]内，且区间内任意值有$⌊\log_d{(d−1)n}⌋=h$
  * 证毕

### EXTRACT_MAX的时间复杂度

* 先分析maxHeapify()的时间复杂度：
  ```C++
  void maxHeapify(int p)//p是当前节点
    {
        int size = arr.size() - 1;
        int largest = p;
        int child;
        for (int j = 1; j <= d; j++)//找到大于当前节点的最大子节点，比较d次
        {
            child = i_child(p, j);//求得子节点为d*(i − 1) + j + 1
            if (child <= size && arr[child] > arr[largest])
                largest = child;
            else if (child > size)
                break;
        }
        if (largest != p)
        {
            swap(arr[largest], arr[p]);
            maxHeapify(largest);//递归
        }
    }
    ```
* 每次递归调用maxHeapify()需要进行d次比较，递归的最大高度为堆的高度h
* 因此maxHeapify()的时间复杂度为$O(d* h)=O(d* ⌊\log_d{(d−1)n}⌋)=O(dlog_d{n})$
```C++
int EXTRACT_MAX()
    {
        int size = arr.size()-1;
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
```
* 对于EXTRACT_MAX()，除了调用maxHeapify(),其他的操作都是常数阶的。所以EXTRACT_MAX()的时间复杂度取决于maxHeapify,为$O(dlog_d{n})$
### INSERT的时间复杂度
```C++
void INSERT(int x)//参数x是被插入的值
    {
        arr.push_back(x);
        int i = arr.size()-1;
        int parent = i_parent(i);
        while (arr[i] > arr[parent])
        {
            swap(arr[i], arr[parent]);
            i=parent;
            parent = i_parent(parent);
        }
    }
```
* insert函数自下而上迭代，while执行次数最多为堆的高度h。除了while循环之外的操作都是常数阶的，所以INSERT的时间复杂度为$O(log_d{n})$

### INCREASE_KEY的时间复杂度
```C++
void INCREASE_KEY(int i, int k)//参数i是指定的元素，参数k是将元素的值改为k
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
                i=parent;
                parent = i_parent(parent);
            }
        }
    }
```
* while执行次数最多为堆的高度h。除了while循环之外的操作都是常数阶的，所以INCREASE_KEY的时间复杂度为$O(log_d{n})$
  
#### 代码说明：我将d_ray_maxheap封装成一个类，n、d、数组arr作为成员变量可以被成员函数直接调用，因此不用另外传参。
<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({ tex2jax: {inlineMath: [['$', '$']]}, messageStyle: "none" });
</script>