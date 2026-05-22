#ifndef __TGraph_H__
#define __TGraph_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TEdge
{
    int to;
    int w;

    TEdge(int _to = 0, int _w = 0);
};

class TGraph
{
    int vertexCount;
    vector<vector<TEdge>> data;
public:
    TGraph(int n = 1);

    int size() const;
    void addEdge(int from, int to, int w);
    const vector<TEdge>& operator[](int ind) const;

    bool hasNegativeEdges() const;
    bool isConnected() const;

    static TGraph randomGraph(int n, int m, int maxWeight = 20);
    void exportDot(const string& filename) const;

    friend ostream& operator<<(ostream& ostr, const TGraph& g);
};

#endif
