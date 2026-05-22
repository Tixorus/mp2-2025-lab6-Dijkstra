#include "tfibonacciheap.h"

#include <algorithm>

struct TFibonacciHeap::TNode
{
    int vertex;
    int dist;
    int degree;
    bool mark;
    TNode* parent;
    TNode* child;
    TNode* left;
    TNode* right;

    TNode(int v, int d) : vertex(v), dist(d), degree(0), mark(false), parent(nullptr), child(nullptr), left(this), right(this) {}
};

void TFibonacciHeap::addToRoot(TNode* x)
{
    x->parent = nullptr;
    x->mark = false;
    if (mn == nullptr)
    {
        x->left = x->right = x;
        mn = x;
        return;
    }
    x->left = mn;
    x->right = mn->right;
    mn->right->left = x;
    mn->right = x;
    if (x->dist < mn->dist) { mn = x; }
}

void TFibonacciHeap::removeFromList(TNode* x)
{
    x->left->right = x->right;
    x->right->left = x->left;
    x->left = x->right = x;
}

void TFibonacciHeap::link(TNode* y, TNode* x)
{
    removeFromList(y);
    y->parent = x;
    y->mark = false;
    if (x->child == nullptr)
    {
        x->child = y;
        y->left = y->right = y;
    }
    else
    {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
}

void TFibonacciHeap::consolidate()
{
    vector<TNode*> a(64, nullptr);
    vector<TNode*> roots;
    TNode* cur = mn;
    if (cur == nullptr) { return; }
    do
    {
        roots.push_back(cur);
        cur = cur->right;
    } while (cur != mn);

    for (size_t i = 0; i < roots.size(); i++)
    {
        TNode* x = roots[i];
        int d = x->degree;
        while (a[d] != nullptr)
        {
            TNode* y = a[d];
            if (x->dist > y->dist) { swap(x, y); }
            link(y, x);
            a[d] = nullptr;
            d++;
        }
        a[d] = x;
    }

    mn = nullptr;
    for (size_t i = 0; i < a.size(); i++)
    {
        if (a[i] != nullptr)
        {
            a[i]->left = a[i]->right = a[i];
            addToRoot(a[i]);
        }
    }
}

void TFibonacciHeap::cut(TNode* x, TNode* y)
{
    if (y->child == x)
    {
        if (x->right == x) { y->child = nullptr; }
        else { y->child = x->right; }
    }
    removeFromList(x);
    y->degree--;
    addToRoot(x);
}

void TFibonacciHeap::cascadingCut(TNode* y)
{
    TNode* z = y->parent;
    if (z != nullptr)
    {
        if (!y->mark) { y->mark = true; }
        else
        {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

void TFibonacciHeap::collect(TNode* v, vector<TNode*>& nodes)
{
    if (v == nullptr) { return; }
    TNode* cur = v;
    do
    {
        nodes.push_back(cur);
        collect(cur->child, nodes);
        cur = cur->right;
    } while (cur != v);
}

TFibonacciHeap::TFibonacciHeap(int n) : mn(nullptr), cnt(0), pos(n, nullptr) {}

TFibonacciHeap::~TFibonacciHeap()
{
    vector<TNode*> nodes;
    collect(mn, nodes);
    for (size_t i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
}

bool TFibonacciHeap::empty() const
{
    return cnt == 0;
}

bool TFibonacciHeap::contains(int v) const
{
    return pos[v] != nullptr;
}

void TFibonacciHeap::push(int v, int dist)
{
    if (contains(v))
    {
        decreaseKey(v, dist);
        return;
    }
    TNode* x = new TNode(v, dist);
    pos[v] = x;
    addToRoot(x);
    cnt++;
}

void TFibonacciHeap::decreaseKey(int v, int dist)
{
    TNode* x = pos[v];
    if (x == nullptr || x->dist <= dist) { return; }
    x->dist = dist;
    TNode* y = x->parent;
    if (y != nullptr && x->dist < y->dist)
    {
        cut(x, y);
        cascadingCut(y);
    }
    if (x->dist < mn->dist) { mn = x; }
}

int TFibonacciHeap::extractMin()
{
    TNode* z = mn;
    if (z->child != nullptr)
    {
        vector<TNode*> sons;
        TNode* cur = z->child;
        do
        {
            sons.push_back(cur);
            cur = cur->right;
        } while (cur != z->child);
        for (size_t i = 0; i < sons.size(); i++)
        {
            removeFromList(sons[i]);
            addToRoot(sons[i]);
        }
        z->child = nullptr;
    }

    int res = z->vertex;
    pos[res] = nullptr;
    if (z->right == z) { mn = nullptr; }
    else
    {
        mn = z->right;
        removeFromList(z);
        consolidate();
    }
    cnt--;
    delete z;
    return res;
}
