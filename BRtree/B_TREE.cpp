#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#define MINDEGREE 2

using namespace std;

/***********************************
 *word:
 *key:Word
 *pos:Part-Of-Speech
 *frq:Frequency
 ***********************************/
struct word
{
    string key;
    char pos;
    string frq;
    word(){};
    word(string k, char p, string f) : key(k), pos(p), frq(f) {}
};

class B_Tree
{
private:
    struct B_Node
    {
        vector<word> nodeKey;
        vector<B_Node *> nodeChild;
        // key.size() demonstrate the size of node
        //(nodeChild)p.empty()==1 demonstrate p is a leaf-node
    };
    using nodePlace = pair<B_Node *, int>;// the place of the target element
    int t; // minimum degree

private:
    void SplitChild(B_Node *x, const int i);
    void Insert_notfull(B_Node *x, const string k, const char p, const string f);
    nodePlace search(B_Node *x, const string k);
    nodePlace predecessor(B_Node *x, int i);
    nodePlace successor(B_Node *x, int i);
    B_Node *minimum(B_Node *p);
    B_Node *maximum(B_Node *p);
    void combine(B_Node *x, B_Node *y, nodePlace z);
    void Delete(B_Node *x, const string k);
    void in_traversal(B_Node *p);

public:
    B_Node *root;
    B_Tree() : root(new B_Node), t(MINDEGREE) {}
    ~B_Tree() { delete root; }
    void Initialization(string filePath);
    void Insert(const string k, const char p, const string f);
    void Insert(string filePath);
    void Delete(const string k, const char p, const string f) { Delete(root, k); }
    void Delete(string filePath);
    void Update(const string k, const char p, const string f);
    void Search(const string k);
    void Dump() { in_traversal(root); }
};

void B_Tree::Initialization(string filePath)
{
    Insert(filePath);
}
void B_Tree::Insert(string filePath)
{
    ifstream readIn;
    readIn.open(filePath);
    string temp_k;
    char temp_p;
    string temp_f;
    char c[40];
    readIn.getline(c, 40);
    while (readIn >> temp_k >> temp_p >> temp_f)
    {
        Insert(temp_k, temp_p, temp_f);
    }
    readIn.close();
}


void B_Tree::Insert(const string k, const char p, const string f)
{
    B_Node *r = root;
    if (r->nodeKey.size() == 2 * t - 1)
    {
        B_Node *s = new B_Node;
        root = s;
        s->nodeChild.push_back(r);
        SplitChild(s, 0);
        Insert_notfull(s, k, p, f);
    }
    else
        Insert_notfull(r, k, p, f);
}

void B_Tree::Update(const string k, const char p, const string f)
{
    nodePlace x = search(root, k);
    if (x.first == nullptr)
        Insert(k, p, f);
    else
    {
        B_Node *y = x.first;
        int i = x.second;
        y->nodeKey[i].key = k;
        y->nodeKey[i].pos = p;
        y->nodeKey[i].frq = f;
    }
}
void B_Tree::Delete(string filePath)
{
    ifstream readIn;
    readIn.open(filePath);
    string temp_k;
    char temp_p;
    string temp_f;
    char c[40];
    readIn.getline(c, 40);
    while (readIn >> temp_k >> temp_p >> temp_f)
        Delete(temp_k,temp_p,temp_f);
    readIn.close();
}

void B_Tree::SplitChild(B_Node *x, const int i)
{
    B_Node *y = x->nodeChild[i];
    B_Node *z = new B_Node;

    for (int j = 0; j < t - 1; ++j)
        z->nodeKey.push_back(y->nodeKey[j + t]);

    if (!y->nodeChild.empty())
    {
        for (int j = 0; j < t; ++j)
            z->nodeChild.push_back(y->nodeChild[j + t]);
        for (int j = 0; j < t; ++j)
            y->nodeChild.pop_back();
    }

    x->nodeKey.insert(x->nodeKey.begin() + i, y->nodeKey[t - 1]);
    x->nodeChild.insert(x->nodeChild.begin() + i + 1, z);
    for (int j = 0; j < t; ++j)
        y->nodeKey.pop_back();
}
//想非满的结点中递归插入关键字
void B_Tree::Insert_notfull(B_Node *x, const string k, const char p, const string f)
{
    int i = x->nodeKey.size() - 1;
    while (i >= 0 && k < x->nodeKey[i].key)
        --i;
    if (i >= 0 && k == x->nodeKey[i].key)
    {
        cout << "key " << k << " conflict" << endl;
        return;
    }
    if (x->nodeChild.empty())
    {
        word temp(k, p, f);
        x->nodeKey.insert(x->nodeKey.begin() + i + 1, temp);
    }
    else
    {
        ++i;
        if (x->nodeChild[i]->nodeKey.size() == 2 * t - 1)
        {
            SplitChild(x, i);
            if (k > x->nodeKey[i].key)
                ++i;
            else if (k >= x->nodeKey[i].key)
            {
                cout << "key " << k << " conflict" << endl;
                return;
            }
        }
        Insert_notfull(x->nodeChild[i], k, p, f);
    }
}

//返回关键字位置
B_Tree::nodePlace B_Tree::search(B_Node *x, const string k)
{
    int i = 0;
    while (i < x->nodeKey.size() && k > x->nodeKey[i].key)
        ++i;
    if (i < x->nodeKey.size() && k == x->nodeKey[i].key)
        return make_pair(x, i);
    else if (x->nodeChild.empty())
        return make_pair(nullptr, 0);
    else
        return search(x->nodeChild[i], k);
}

//不返回，输出。
void B_Tree::Search(const string k)
{
    nodePlace x = search(root, k);
    if (x.first == nullptr)
    {
        cout << "key " << k << " missing" << endl;
        return;
    }
    else
    {
        B_Node *y = x.first;
        int i = x.second;
        cout << k << "-(" << y->nodeKey[i].pos << "," << y->nodeKey[i].frq << ")" << endl;
    }
}
//返回最小结点
B_Tree::B_Node *B_Tree::minimum(B_Node *p)
{
    while (!p->nodeChild.empty())
        p = p->nodeChild[0];
    return p;
}

//返回最大结点
B_Tree::B_Node *B_Tree::maximum(B_Node *p)
{
    while (!p->nodeChild.empty())
        p = p->nodeChild[p->nodeChild.size() - 1];
    return p;
}

//返回前驱关键字的位置
B_Tree::nodePlace B_Tree::predecessor(B_Node *x, int i)
{
    x = maximum(x->nodeChild[i]);
    return make_pair(x, x->nodeKey.size() - 1);
}

//返回后继关键字的位置
B_Tree::nodePlace B_Tree::successor(B_Node *x, int i)
{
    x = minimum(x->nodeChild[i + 1]);
    return make_pair(x, 0);
}

void B_Tree::combine(B_Node *x, B_Node *y, nodePlace z)
{
    //把父节点下拉，不是借兄弟
    // x is z's left, y is z's right
    x->nodeKey.push_back(z.first->nodeKey[z.second]);
    for (int i = 0; i < t - 1; ++i)
        x->nodeKey.push_back(y->nodeKey[i]);
    if (!x->nodeChild.empty())
        for (int i = 0; i < t; ++i)
        {
            x->nodeChild.push_back(y->nodeChild[i]);
        }
    delete y;

    z.first->nodeKey.erase(z.first->nodeKey.begin() + z.second);
    z.first->nodeChild.erase(z.first->nodeChild.begin() + z.second + 1);
    if (z.first->nodeKey.empty())
    {
        root = z.first->nodeChild[z.second];
        delete z.first;
    }
}
//递归删除关键字。递归调用前会保障结点不会太小
void B_Tree::Delete(B_Node *x, const string k)
{ 
    int i = 0;
    while (i < x->nodeKey.size() && x->nodeKey[i].key < k)
        ++i;
    if (i < x->nodeKey.size() && x->nodeKey[i].key == k)
    {
        if (x->nodeChild.empty()) 
            x->nodeKey.erase(x->nodeKey.begin() + i);
        else
        {
            if (x->nodeChild[i]->nodeKey.size() >= t) //左孩子富，找前驱
            {
                nodePlace pre = predecessor(x, i);
                x->nodeKey[i] = pre.first->nodeKey[pre.second];
                Delete(x->nodeChild[i], x->nodeKey[i].key);
            }
            else if (x->nodeChild[i + 1]->nodeKey.size() >= t)//右孩子富，找后继
            {
                nodePlace suc = successor(x, i);
                x->nodeKey[i] = suc.first->nodeKey[suc.second];
                Delete(x->nodeChild[i + 1], x->nodeKey[i].key);
            }
            else//都不富，整合
            {
                combine(x->nodeChild[i], x->nodeChild[i + 1], make_pair(x, i));
                Delete(x->nodeChild[i], k);
            }
        }
    }
    else
    {
        if (x->nodeChild.empty())
        {
            cout << "key " << k << " missing" << endl;
            return;
        }
        else if (x->nodeChild[i]->nodeKey.size() != t - 1)
            Delete(x->nodeChild[i], k);
        else
        {
            B_Node *y, *z;
            if (i > 0 && x->nodeChild[i - 1]->nodeKey.size() != t - 1)//左水右调
            {
                y = x->nodeChild[i - 1];
                z = x->nodeChild[i];
                z->nodeKey.insert(z->nodeKey.begin(), x->nodeKey[i - 1]);
                if (!y->nodeChild.empty())
                {
                    z->nodeChild.insert(z->nodeChild.begin(), y->nodeChild.back());
                    y->nodeChild.pop_back();
                }
                x->nodeKey[i - 1] = y->nodeKey.back();
                y->nodeKey.pop_back();
                Delete(z, k);
            }
            else if (i < x->nodeChild.size() - 1 && x->nodeChild[i + 1]->nodeKey.size() != t - 1)//右水左调
            {
                y = x->nodeChild[i + 1];
                z = x->nodeChild[i];
                z->nodeKey.push_back(x->nodeKey[i]);
                if (!y->nodeChild.empty())
                {
                    z->nodeChild.push_back(y->nodeChild[0]);
                    y->nodeChild.erase(y->nodeChild.begin());
                }
                x->nodeKey[i] = y->nodeKey[0];
                y->nodeKey.erase(y->nodeKey.begin());
                Delete(z, k);
            }
            else if (i > 0)//向左整合
            {
                y = x->nodeChild[i - 1];
                z = x->nodeChild[i];
                combine(y, z, make_pair(x, i - 1));
                Delete(y, k);
            }
            else if (i < x->nodeChild.size() - 1)//向右整合
            {
                y = x->nodeChild[i];
                z = x->nodeChild[i + 1];
                combine(y, z, make_pair(x, i));
                Delete(y, k);
            }
        }
    }
}

void B_Tree::in_traversal(B_Node *p)
{
    int i;
    if (!p->nodeChild.empty())
    {
        for (i = 0; i < p->nodeKey.size(); ++i)
        {
            in_traversal(p->nodeChild[i]);
            cout << p->nodeKey[i].key << "-(" << p->nodeKey[i].pos << "," << p->nodeKey[i].frq << ")" << endl;
        }
        in_traversal(p->nodeChild[i]);
    }
    else
    {
        for (i = 0; i < p->nodeKey.size(); ++i)
            cout << p->nodeKey[i].key << "-(" << p->nodeKey[i].pos << "," << p->nodeKey[i].frq << ")" << endl;
    }
}