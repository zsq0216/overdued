# Lab5 报告文档
## 实验思路
### 树的节点node设计
* 成员变量：
  * int类型的key和value
  * node*类型的p,left,right
* 初始化：
  * 无参，则key,value初始化为0，指针指向nullptr
  * 有参(k,v)，则key=k,value=v,指针指向nullptr
### 二叉查找树Tree的设计
**成员变量：**
* 根节点node *root
**构造函数：**
* 无参，则root指向nullptr
* 有参(node *x),则根节点root设置为x
**成员函数：**
* int search_recursion(node *x, int k)
  * 功能：递归查找 x 为根的子树中 key 值为 k 的，元素的 value，没有则返回-1
  * 利用二叉搜索树的性质，若k小于当前x的key值，调用search_recursion(x->left, k)走左子树；若大于，调用search_recursion(x->right, k)走右子树；若相等，则已找到返回当前节点的value。
  * 若递归调用的x为空，则说明该子树中没有目标值，返回-1.
* int search_iterative(node *x, int k)
  * 功能：迭代查找 x 为根的子树中 key 值为 k 的，元素的 value，没有则返回-1
  * 在循环中通过改变指针的指向决定搜索左子树或是右子树。循环结束的标志为指针为空：若在循环结束前就搜索到，当即返回；若循环结束仍为搜索到，则说明子树中不存在目标值，返回-1.
* int minimum(node *x)
  * 迭代查找 x 为根的子树中 key 值最小的元素的 v
  * 走左子树走到底。只要树不为空，则不存在没有最小值的情况；若子树为空则返回-1.
* node *tree_minimum(node *x)
  * 迭代查找 x 为根的子树中 key 值最小的节点。该函数服务于Delete函数。
* int maximum(node *x)
  * 迭代查找 x 为根的子树中 key 值最大的元素的 v
  * 做法和minimum对称
* int successor(node *x)
  * 迭代查找比 x 的 key 值大的最小的 key 值的元素的 value。(后继)
  * 若x存在右子树，后继就是右子树的key值最小的节点
  * 若x不存在右子树，后继是往父节点回溯路径上第一个由左向右的拐点.若不存在就返回-1.
  * 若x本身就是nullptr，更谈不上后继
* node *tree_successor(node *x)
  * 迭代查找比 x 的 key 值大的最小的 key 值的节点。该函数服务于Delete函数。
* int predecessor(node *x)
  * 迭代查找比 x 的 key 值小的最大的 key 值的元素的 value。(后继)
  * 做法和successor对称
* void insert(node *z)
  * 在树中插入一个新节点 z。
  * 因为root是树的成员变量，所以不用传参T
  * 如果树是空的，则z即为根节点
  * 如果非空，插入到合适的叶节点
  * 需要双指针——一个记录当前节点，一个记录当前节点的父节点，便于插入后建立父子关系。
* void Delete(node *z)
  * 在树中删除节点 z
  * 如果z就是叶节点，直接断开父子关系
  * 因为root是树的成员变量，所以不用传参T
  * 如果z有一个子节点，将z的子节点与z的父节点连接
  * 如果z有两个子节点，找到z的后继节点，删除该后继节点，再将z的key,value改成后继的key,value.原理是这种情况下，z的后继节点至多有一个子节点
* void pre_traversal(node *T)
  * 递归方法前序遍历
* void in_traversal(node *T)
  * 递归方法中序遍历
* void post_traversal(node *T)
  * 递归方法后序遍历
* void traversal(node *T)
  * 将以上三个函数整合在一起
## 实验过程
* 自行创建了一个data.txt，读入文件中的数据，用new的方法为节点分配空间，用文件中的数据初始化节点，将节点插入到Tree类型的T1中
* 用打印返回值的方式检查int function；用中序遍历打印所有节点的方式检查void function

## 实验结果
  可以在满足功能的同时保证二叉查找树的性质