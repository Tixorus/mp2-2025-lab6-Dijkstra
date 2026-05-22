#ifndef __TBinomialHeap_H__
#define __TBinomialHeap_H__

#include <vector>

using namespace std;

class TBinomialHeap
{
    struct TNode;

    TNode* root;
    vector<TNode*> pos;

    static void clear(TNode* v);
    static TNode* mergeRootLists(TNode* a, TNode* b);

    void link(TNode* y, TNode* z);
    void unite(TNode* other);
    void swapInfo(TNode* a, TNode* b);
public:
    TBinomialHeap(int n = 1);
    ~TBinomialHeap();

    bool empty() const;
    bool contains(int v) const;
    void push(int v, int dist);
    void decreaseKey(int v, int dist);
    int extractMin();
};

#endif
