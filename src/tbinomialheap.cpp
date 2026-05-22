#include "tbinomialheap.h"

#include <algorithm>

struct TBinomialHeap::TNode
{
    int vertex;
    int dist;
    int degree;
    TNode* parent;
    TNode* child;
    TNode* sibling;

    TNode(int v, int d) : vertex(v), dist(d), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

void TBinomialHeap::clear(TNode* v)
{
    if (v == nullptr) { return; }
    clear(v->child);
    clear(v->sibling);
    delete v;
}

TBinomialHeap::TNode* TBinomialHeap::mergeRootLists(TNode* a, TNode* b)
{
    if (a == nullptr) { return b; }
    if (b == nullptr) { return a; }

    TNode* head;
    TNode* tail;
    if (a->degree <= b->degree)
    {
        head = tail = a;
        a = a->sibling;
    }
    else
    {
        head = tail = b;
        b = b->sibling;
    }
    while (a != nullptr && b != nullptr)
    {
        if (a->degree <= b->degree)
        {
            tail->sibling = a;
            a = a->sibling;
        }
        else
        {
            tail->sibling = b;
            b = b->sibling;
        }
        tail = tail->sibling;
    }
    if (a != nullptr) { tail->sibling = a; }
    else { tail->sibling = b; }
    return head;
}

void TBinomialHeap::link(TNode* y, TNode* z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

void TBinomialHeap::unite(TNode* other)
{
    root = mergeRootLists(root, other);
    if (root == nullptr) { return; }

    TNode* prev = nullptr;
    TNode* x = root;
    TNode* next = x->sibling;
    while (next != nullptr)
    {
        if (x->degree != next->degree || (next->sibling != nullptr && next->sibling->degree == x->degree))
        {
            prev = x;
            x = next;
        }
        else if (x->dist <= next->dist)
        {
            x->sibling = next->sibling;
            link(next, x);
        }
        else
        {
            if (prev == nullptr) { root = next; }
            else { prev->sibling = next; }
            link(x, next);
            x = next;
        }
        next = x->sibling;
    }
}

void TBinomialHeap::swapInfo(TNode* a, TNode* b)
{
    swap(a->vertex, b->vertex);
    swap(a->dist, b->dist);
    pos[a->vertex] = a;
    pos[b->vertex] = b;
}

TBinomialHeap::TBinomialHeap(int n) : root(nullptr), pos(n, nullptr) {}

TBinomialHeap::~TBinomialHeap()
{
    clear(root);
}

bool TBinomialHeap::empty() const
{
    return root == nullptr;
}

bool TBinomialHeap::contains(int v) const
{
    return pos[v] != nullptr;
}

void TBinomialHeap::push(int v, int dist)
{
    if (contains(v))
    {
        decreaseKey(v, dist);
        return;
    }
    TNode* node = new TNode(v, dist);
    pos[v] = node;
    unite(node);
}

void TBinomialHeap::decreaseKey(int v, int dist)
{
    TNode* x = pos[v];
    if (x == nullptr || x->dist <= dist) { return; }
    x->dist = dist;
    while (x->parent != nullptr && x->dist < x->parent->dist)
    {
        swapInfo(x, x->parent);
        x = x->parent;
    }
}

int TBinomialHeap::extractMin()
{
    TNode* prevMin = nullptr;
    TNode* minNode = root;
    TNode* prev = nullptr;
    TNode* cur = root;
    while (cur != nullptr)
    {
        if (cur->dist < minNode->dist)
        {
            minNode = cur;
            prevMin = prev;
        }
        prev = cur;
        cur = cur->sibling;
    }
    if (prevMin == nullptr) { root = minNode->sibling; }
    else { prevMin->sibling = minNode->sibling; }

    TNode* child = minNode->child;
    TNode* rev = nullptr;
    while (child != nullptr)
    {
        TNode* next = child->sibling;
        child->parent = nullptr;
        child->sibling = rev;
        rev = child;
        child = next;
    }
    int res = minNode->vertex;
    pos[res] = nullptr;
    delete minNode;
    unite(rev);
    return res;
}
