#include "tdheap.h"

#include <stdexcept>

void TDHeap::swapNodes(int a, int b)
{
    swap(heap[a], heap[b]);
    pos[heap[a].second] = a;
    pos[heap[b].second] = b;
}

void TDHeap::siftUp(int v)
{
    while (v > 0)
    {
        int p = (v - 1) / d;
        if (heap[p].first <= heap[v].first) { break; }
        swapNodes(p, v);
        v = p;
    }
}

void TDHeap::siftDown(int v)
{
    while (true)
    {
        int best = v;
        for (int i = 1; i <= d; i++)
        {
            int son = v * d + i;
            if ((size_t)son < heap.size() && heap[son].first < heap[best].first) { best = son; }
        }
        if (best == v) { break; }
        swapNodes(best, v);
        v = best;
    }
}

TDHeap::TDHeap(int n, int _d) : d(_d), pos(n, -1)
{
    if (d < 2) { throw invalid_argument("d should be greater than one"); }
}

bool TDHeap::empty() const
{
    return heap.empty();
}

bool TDHeap::contains(int v) const
{
    return pos[v] != -1;
}

void TDHeap::push(int v, int dist)
{
    if (contains(v))
    {
        decreaseKey(v, dist);
        return;
    }
    heap.push_back(make_pair(dist, v));
    pos[v] = (int)heap.size() - 1;
    siftUp(pos[v]);
}

void TDHeap::decreaseKey(int v, int dist)
{
    int p = pos[v];
    if (p == -1 || heap[p].first <= dist) { return; }
    heap[p].first = dist;
    siftUp(p);
}

int TDHeap::extractMin()
{
    int res = heap[0].second;
    pos[res] = -1;
    if (heap.size() == 1)
    {
        heap.pop_back();
        return res;
    }
    heap[0] = heap.back();
    pos[heap[0].second] = 0;
    heap.pop_back();
    siftDown(0);
    return res;
}
