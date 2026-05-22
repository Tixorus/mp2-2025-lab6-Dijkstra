#include "tdijkstra.h"
#include "tdheap.h"
#include "tbinomialheap.h"
#include "tfibonacciheap.h"

#include <algorithm>
#include <chrono>
#include <stdexcept>

template<class THeap>
TDijkstraResult dijkstra(const TGraph& g, int start)
{
    if (start < 0 || start >= g.size()) { throw out_of_range("start vertex was out of range"); }
    if (!g.isConnected()) { throw invalid_argument("Graph should be connected"); }
    if (g.hasNegativeEdges()) { throw invalid_argument("Graph has negative edges"); }

    TDijkstraResult res;
    res.dist.assign(g.size(), INF_DIST);
    res.parent.assign(g.size(), -1);
    vector<int> used(g.size(), 0);
    THeap heap(g.size());

    auto startTime = chrono::high_resolution_clock::now();
    res.dist[start] = 0;
    heap.push(start, 0);
    while (!heap.empty())
    {
        int v = heap.extractMin();
        if (used[v]) { continue; }
        used[v] = 1;
        for (size_t i = 0; i < g[v].size(); i++)
        {
            int to = g[v][i].to;
            int w = g[v][i].w;
            if (res.dist[to] > res.dist[v] + w)
            {
                res.dist[to] = res.dist[v] + w;
                res.parent[to] = v;
                if (heap.contains(to)) { heap.decreaseKey(to, res.dist[to]); }
                else { heap.push(to, res.dist[to]); }
            }
        }
    }
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = endTime - startTime;
    auto duration_ms = chrono::duration_cast<chrono::milliseconds>(duration);
    res.time = (double)duration_ms.count();
    return res;
}

TDijkstraResult dijkstraDHeap(const TGraph& g, int start)
{
    return dijkstra<TDHeap>(g, start);
}

TDijkstraResult dijkstraBinomialHeap(const TGraph& g, int start)
{
    return dijkstra<TBinomialHeap>(g, start);
}

TDijkstraResult dijkstraFibonacciHeap(const TGraph& g, int start)
{
    return dijkstra<TFibonacciHeap>(g, start);
}

vector<int> getPath(const TDijkstraResult& res, int finish)
{
    if (finish < 0 || (size_t)finish >= res.dist.size()) { throw out_of_range("finish vertex was out of range"); }

    vector<int> path;
    if (res.dist[finish] == INF_DIST) { return path; }
    for (int v = finish; v != -1; v = res.parent[v])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}
