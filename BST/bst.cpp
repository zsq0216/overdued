#include <iostream>
#include <fstream>
using namespace std;

struct node
{
    int key;
    int value;
    node *p;
    node *left;
    node *right;
    node()
    {
        left = nullptr;
        right = nullptr;
        p = nullptr;
        key = 0;
        value = 0;
    }
    node(int k, int v)
    {
        left = nullptr;
        right = nullptr;
        p = nullptr;
        key = k;
        value = v;
    }
    ~node() {}
};
class Tree
{
public:
    node *root;
    Tree()
    {
        root = nullptr;
    }
    Tree(node *x)
    {
        root = x;
    }
    ~Tree() {}
    int search_recursion(node *x, int k)
    {
        if (x == nullptr)
            return -1;
        else if (k == x->key)
            return x->value;
        else if (k < x->key)
            return search_recursion(x->left, k);
        else
            return search_recursion(x->right, k);
    }

    int search_iterative(node *x, int k)
    {
        while (x != nullptr)
        {
            if (k == x->key)
                return x->value;
            else if (k < x->key)
                x = x->left;
            else
                x = x->right;
        }
        return -1;
    }

    int minimum(node *x)
    {
        if (x == nullptr)
            return -1;
        while (x->left != nullptr)
            x = x->left;
        return x->value;
    }

    int maximum(node *x)
    {
        if (x == nullptr)
            return -1;
        while (x->right != nullptr)
            x = x->right;
        return x->value;
    }

    int successor(node *x) // the nearest bigger
    {
        if (x == nullptr)
            return -1;
        if (x->right != nullptr)
            return minimum(x->right);
        node *y = x->p;
        while (y != nullptr && x == y->right)
        {
            x = y;
            y = x->p;
        }
        if (y == nullptr)
            return -1;
        else
            return y->value;
    }

    int predecessor(node *x)
    {
        if (x == nullptr)
            return -1;
        if (x->left != nullptr)
            return maximum(x->left);
        node *y = x->p;
        while (y != nullptr && x == y->left)
        {
            x = y;
            y = x->p;
        }
        if (y == nullptr)
            return -1;
        else
            return y->value;
    }

    void insert(node *z)
    {
        if (root == nullptr)
        {
            root = z;
            return;
        }
        node *y = nullptr;
        node *x = root;
        while (x != nullptr)
        {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->p = y;
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }

    void Delete(node *z)
    {
        if(z==nullptr)return;

        node *y = nullptr;
        node *x = nullptr;
        if (z->left == nullptr || z->right == nullptr)
            y = z;
        else
            y = tree_successor(z);
        if (y->left != nullptr)
            x = y->left;
        else
            x = y->right;
        if (x != nullptr)
            x->p = y->p;
        if (y->p == nullptr)
            root = x;
        else if (y == y->p->left)
            y->p->left = x;
        else
            y->p->right = x;
        if (y != z)
        {
            z->key = y->key;
            z->value = y->value;
        }
    }

    void pre_traversal(node *T)
    {
        if (T != nullptr)
        {
            cout << T->value << " ";
            pre_traversal(T->left);
            pre_traversal(T->right);
        }
    }
    void in_traversal(node *T)
    {
        if (T != nullptr)
        {
            in_traversal(T->left);
            cout << T->value << " ";
            in_traversal(T->right);
        }
    }
    void post_traversal(node *T)
    {
        if (T != nullptr)
        {
            post_traversal(T->left);
            post_traversal(T->right);
            cout << T->value << " ";
        }
    }
    void traversal(node *T)
    {
        pre_traversal(T);
        cout << endl;
        in_traversal(T);
        cout << endl;
        post_traversal(T);
        cout << endl;
    }

    node *tree_minimum(node *x)
    {
        if (x == nullptr)
            return nullptr;
        while (x->left != nullptr)
            x = x->left;
        return x;
    }

    node *tree_successor(node *x)
    {
        if (x == nullptr)
            return nullptr;
        if (x->right != nullptr)
            return tree_minimum(x->right);
        node *y = x->p;
        while (y != nullptr && x == y->right)
        {
            x = y;
            y = x->p;
        }
        return y;
    }
};
int main()
{
    ifstream readIn;
    Tree T1;
    readIn.open("data.txt");
    while (!readIn.eof())
    {
        int k, v;
        readIn >> k >> v;
        node *x = new node(k, v);
        T1.insert(x);
    }
    readIn.close();
    T1.Delete(T1.root);
    T1.in_traversal(T1.root);
    return 0;
}