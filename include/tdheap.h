#ifndef __TDHeap_H__
#define __TDHeap_H__

#include <utility>
#include <vector>

using namespace std;

const int D_HEAP_SIZE = 3;

class TDHeap
{
    int d;
    vector<pair<int, int>> heap;
    vector<int> pos;

    void swapNodes(int a, int b);
    void siftUp(int v);
    void siftDown(int v);
public:
    TDHeap(int n = 1, int _d = D_HEAP_SIZE);

    bool empty() const;
    bool contains(int v) const;
    void push(int v, int dist);
    void decreaseKey(int v, int dist);
    int extractMin();
};

#endif
