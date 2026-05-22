#ifndef __TFibonacciHeap_H__
#define __TFibonacciHeap_H__

#include <vector>

using namespace std;

class TFibonacciHeap
{
    struct TNode;

    TNode* mn;
    int cnt;
    vector<TNode*> pos;

    void addToRoot(TNode* x);
    void removeFromList(TNode* x);
    void link(TNode* y, TNode* x);
    void consolidate();
    void cut(TNode* x, TNode* y);
    void cascadingCut(TNode* y);
    static void collect(TNode* v, vector<TNode*>& nodes);
public:
    TFibonacciHeap(int n = 1);
    ~TFibonacciHeap();

    bool empty() const;
    bool contains(int v) const;
    void push(int v, int dist);
    void decreaseKey(int v, int dist);
    int extractMin();
};

#endif
