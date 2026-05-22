#include "tgraph.h"

#include <cstdlib>
#include <fstream>
#include <queue>
#include <stdexcept>

TEdge::TEdge(int _to, int _w) : to(_to), w(_w) {}

TGraph::TGraph(int n) : vertexCount(n), data(n)
{
    if (n <= 0) { throw invalid_argument("Graph size should be greater than zero"); }
}

int TGraph::size() const
{
    return vertexCount;
}

void TGraph::addEdge(int from, int to, int w)
{
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) { throw out_of_range("vertex was out of range"); }
    if (w < 0) { throw invalid_argument("edge weight should be non-negative"); }
    data[from].push_back(TEdge(to, w));
    data[to].push_back(TEdge(from, w));
}

const vector<TEdge>& TGraph::operator[](int ind) const
{
    return data[ind];
}

bool TGraph::hasNegativeEdges() const
{
    for (int i = 0; i < vertexCount; i++)
    {
        for (size_t j = 0; j < data[i].size(); j++)
        {
            if (data[i][j].w < 0) { return true; }
        }
    }
    return false;
}

bool TGraph::isConnected() const
{
    vector<int> used(vertexCount, 0);
    queue<int> q;
    used[0] = 1;
    q.push(0);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < data[v].size(); i++)
        {
            int to = data[v][i].to;
            if (!used[to])
            {
                used[to] = 1;
                q.push(to);
            }
        }
    }
    for (int i = 0; i < vertexCount; i++)
    {
        if (!used[i]) { return false; }
    }
    return true;
}

TGraph TGraph::randomGraph(int n, int m, int maxWeight)
{
    if (m < n - 1) { throw invalid_argument("Too few edges for connected graph"); }
    if (m > n * (n - 1) / 2) { throw invalid_argument("Too many edges"); }

    TGraph g(n);
    vector<vector<int>> used(n, vector<int>(n, 0));
    for (int i = 1; i < n; i++)
    {
        int to = rand() % i;
        int w = rand() % maxWeight + 1;
        g.addEdge(i, to, w);
        used[i][to] = used[to][i] = 1;
    }
    int cnt = n - 1;
    while (cnt < m)
    {
        int a = rand() % n;
        int b = rand() % n;
        if (a == b || used[a][b]) { continue; }
        int w = rand() % maxWeight + 1;
        g.addEdge(a, b, w);
        used[a][b] = used[b][a] = 1;
        cnt++;
    }
    return g;
}

void TGraph::exportDot(const string& filename) const
{
    ofstream fout(filename.c_str());
    if (!fout) { throw runtime_error("Cannot open dot file"); }

    fout << "graph G {\n";
    for (int i = 0; i < vertexCount; i++)
    {
        fout << "  " << i << ";\n";
    }

    for (int i = 0; i < vertexCount; i++)
    {
        for (size_t j = 0; j < data[i].size(); j++)
        {
            if (i < data[i][j].to)
            {
                fout << "  " << i << " -- " << data[i][j].to << " [label=\"" << data[i][j].w << "\"];\n";
            }
        }
    }

    fout << "}\n";
}

ostream& operator<<(ostream& ostr, const TGraph& g)
{
    for (int i = 0; i < g.vertexCount; i++)
    {
        ostr << i << ": ";
        for (size_t j = 0; j < g.data[i].size(); j++)
        {
            ostr << "(" << i << "->" << g.data[i][j].to << ", " << g.data[i][j].w << ")";
            if (j + 1 != g.data[i].size()) { ostr << ", "; }
        }
        ostr << '\n';
    }
    return ostr;
}
