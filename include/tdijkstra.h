#ifndef __TDijkstra_H__
#define __TDijkstra_H__

#include <vector>
#include "tgraph.h"

using namespace std;

const int INF_DIST = 1000000000;

struct TDijkstraResult
{
    vector<int> dist;
    vector<int> parent;
    double time;
};

TDijkstraResult dijkstraDHeap(const TGraph& g, int start);
TDijkstraResult dijkstraBinomialHeap(const TGraph& g, int start);
TDijkstraResult dijkstraFibonacciHeap(const TGraph& g, int start);

vector<int> getPath(const TDijkstraResult& res, int finish);

#endif
