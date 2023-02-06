#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum COLOR
{
    RED,
    BLACK
};

/***********************************
 *key:Word
 *pos:Part-Of-Speech
 *frq:Frequency
 ***********************************/
class RB_node
{
public:
    string key;
    char pos;
    string frq;
    RB_node *left;
    RB_node *right;
    RB_node *p;
    COLOR color;
    RB_node();
    RB_node(string k, char p, string f);
    ~RB_node();
};
class RB_TREE
{
private:
    RB_node *nil; // Children of all leaf nodes to save space
    void left_rotate(RB_node *x);
    void right_rotate(RB_node *x);
    void insert_fixup(RB_node *x);
    void delete_fixup(RB_node *x);
    RB_node *minimum(RB_node *x);
    void in_traversal(RB_node *x);
    RB_node *search(string k);

public:
    RB_node *root; // root node
    RB_TREE();
    ~RB_TREE();
    void Initialization(string filePath);
    void Insert(string filePath);
    void Insert(string k, char p, string f);
    void Delete(string k, char p, string f);
    void Delete(string filePath);
    void Update(string k, char p, string f);
    void Search(const string k);
    void Dump();
};
RB_node::RB_node()
{
    this->left = nullptr;
    this->right = nullptr;
    this->p = nullptr;
    this->color = RED;
}
RB_node::RB_node(string k, char p, string f)
{
    this->key = k;
    this->pos = p;
    this->frq = f;
    this->left = nullptr;
    this->right = nullptr;
    this->p = nullptr;
    this->color = RED;
}
RB_node::~RB_node() {}

RB_TREE::RB_TREE()
{
    nil = new RB_node();
    nil->left = root;
    nil->right = root;
    nil->p = root;
    nil->color = BLACK;
    root = nil;
}
RB_TREE::~RB_TREE() {}
void RB_TREE::Initialization(string filePath)
{
    Insert(filePath);
}
void RB_TREE::Insert(string filePath)
{
    ifstream readIn;
    readIn.open(filePath);
    string temp_k;
    char temp_p;
    string temp_f;
    char c[40];
    readIn.getline(c, 40);
    while (readIn >> temp_k >> temp_p >> temp_f)
        Insert(temp_k, temp_p, temp_f);
    readIn.close();
}
void RB_TREE::Delete(string filePath)
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
/***********************************************
 * Parameters refer to key, part of speech and frequency
 * RB_node*y point to the inserted node
 * RB_node*x is an index pointer, pointing to the current node
 * RB_node*z is the node we insert to the tree
 ************************************************/
void RB_TREE::Insert(string k, char p, string f)
{
    RB_node *y = nil;
    RB_node *x = root;
    while (x != nil)
    {
        y = x;
        if (k < x->key)
            x = x->left;
        else if (k > x->key)
            x = x->right;
        else
        {
            cout << "key " << k << " conflict" << endl;
            return;
        }
    }
    RB_node *z = new RB_node(k, p, f);
    z->left = nil;
    z->right = nil;
    z->p = y;
    if (y == nil)
        root = z;
    else if (k < y->key)
        y->left = z;
    else
        y->right = z;
    insert_fixup(z);
}
/***********************************
 *case1: father is black -> stop
 *case2: uncle is red -> change color
 *case3: father has the same side with me -> contrary side rotate
 *case4: different side -> pre_rotate & rotate
 ************************************/
void RB_TREE::insert_fixup(RB_node *z)
{
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            RB_node *uncle = z->p->p->right;
            if (uncle->color == RED) // case2
            {
                z->p->color = BLACK;
                uncle->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->right) // case4
                {
                    z = z->p;
                    left_rotate(z);
                }
                z->p->color = BLACK; // case3
                z->p->p->color = RED;
                right_rotate(z->p->p);
            }
        }
        else
        {
            RB_node *uncle = z->p->p->left;
            if (uncle->color == RED)
            {
                z->p->color = BLACK;
                uncle->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;
                    right_rotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(z->p->p);
            }
        }
    }
    root->color = BLACK;
}
void RB_TREE::left_rotate(RB_node *x)
{
    RB_node *y = x->right;
    x->right = y->left;
    if (y->left != nil)
        y->left->p = x;
    y->p = x->p;
    if (x->p == nil)
        root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void RB_TREE::right_rotate(RB_node *x)
{
    RB_node *y = x->left;
    x->left = y->right;
    if (y->right != nil)
        y->right->p = x;
    y->p = x->p;
    if (x->p == nil)
        root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->right = x;
    x->p = y;
}

RB_node *RB_TREE::search(string k)
{
    RB_node *x = root;
    while (x != nil)
    {
        if (k < x->key)
            x = x->left;
        else if (k > x->key)
            x = x->right;
        else
            break;
    }
    return x;
}
void RB_TREE::Search(string k)
{
    RB_node *x = search(k);
    if (x == nil)
    {
        cout << "key " << k << " missing" << endl;
        return;
    }
    else
        cout << k << "-(" << x->pos << "," << x->frq << ")" << endl;
}
void RB_TREE::Delete(string k,char p, string f)
{
    RB_node *z = search(k);
    if (z == nil)
    {
        cout << "key " << k << " missing" << endl;
        return;
    }
    RB_node *y = nil; // y point to the node to be deleted in fact
    RB_node *x = nil; // y's child who gonna substitude y
    if (z->left == nil || z->right == nil)
        y = z;
    else
        y = minimum(z->right);
    if (y->left != nil)
        x = y->left;
    else
        x = y->right;
    // if (x != nil) is not allowed here
    x->p = y->p;
    if (y->p == nil)
        root = x;
    else if (y == y->p->left)
        y->p->left = x; // got wrong initially, written as x=y.p.left
    else
        y->p->right = x;
    if (y != z)
    {
        z->key = y->key;
        z->pos = y->pos;
        z->frq = y->frq;
    }
    if (y->color == BLACK)
        delete_fixup(x);
    delete y;
}
/*
 *case1: x's sibling w is red -> convert to case2,3 or 4
 *case2: both of w's children are black -> change color and x=x->p, enter the new loop
 *case3: w's child, who has the same side with w, is black -> same_side_rotate orbitting w
 *case4: w's child, who has the same side with w, is red -> contrary_side_rotate orbitting w's parent
 */
void RB_TREE::delete_fixup(RB_node *x)
{
    RB_node *w = nil;
    while (x != root && x->color == BLACK)
    {
        if (x == x->p->left)
        {
            w = x->p->right;
            if (w->color == RED) // case1
            {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(x->p);
                w = x->p->right;                                     // this new w is definitely black
            }                                                        // transfer to other case
            if (w->left->color == BLACK && w->right->color == BLACK) // case2.....and mistake the w as x initially
            {
                w->color = RED;
                x = x->p; // enter a new loop,and the new node is x's parent
            }
            else
            {
                if (w->right->color == BLACK) // case3
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->p->right;    // now this w's right is definitely red
                }                       // convert case3 to case4
                w->color = x->p->color; // case4
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->p);
                x = root; // terminate the while loop
            }
        }
        else
        {
            w = x->p->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(x->p);
                w = x->p->left;
            }                                                        // transfer to other case
            if (w->right->color == BLACK && w->left->color == BLACK) // case2
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->left->color == BLACK) // case3
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->p->left;
                }                       // convert case3 to case4
                w->color = x->p->color; // case4
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->p);
                x = root; // terminate the while loop
            }
        }
    }
    x->color = BLACK;
}
void RB_TREE::Update(string k, char p, string f)
{
    RB_node *y = nil;
    RB_node *x = root;
    while (x != nil)
    {
        y = x;
        if (k < x->key)
            x = x->left;
        else if (k > x->key)
            x = x->right;
        else
        {
            x->key = k;
            x->pos = p;
            x->frq = f;
            return;
        }
    }
    RB_node *z = new RB_node(k, p, f);
    z->left = nil;
    z->right = nil;
    z->p = y;
    if (y == nil)
        root = z;
    else if (k < y->key)
        y->left = z;
    else
        y->right = z;
    insert_fixup(z);
}

RB_node *RB_TREE::minimum(RB_node *x)
{
    while (x->left != nil)
        x = x->left;
    return x;
}
void RB_TREE::Dump()
{
    in_traversal(root);
}
//
void RB_TREE::in_traversal(RB_node *x)
{
    if (x != nil)
    {
        in_traversal(x->left);
        cout << x->key << "-(" << x->pos << "," << x->frq << ")" << endl;
        in_traversal(x->right);
    }
}