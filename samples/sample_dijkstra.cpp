#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <vector>
#include "tdijkstra.h"
#include "tgraph.h"

using namespace std;

void printPath(const vector<int>& path)
{
    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i + 1 != path.size()) { cout << " -> "; }
    }
    cout << endl;
}

int main()
{
    srand((unsigned int)time(0));

    cout << "Dijkstra algorithm" << endl;
    cout << "1 - manual input, 2 - random graph" << endl;

    int type;
    cin >> type;

    int n, m;
    cout << "Enter vertices and edges count: ";
    cin >> n >> m;

    TGraph g(n);
    if (type == 1)
    {
        cout << "Enter edges: from, to, weight" << endl;
        for (int i = 0; i < m; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;
            g.addEdge(a, b, w);
        }
    }
    else
    {
        g = TGraph::randomGraph(n, m);
    }

    cout << "Graph:" << endl << g << endl;
    g.exportDot("graph.dot");
    cout << "Graph visualization saved to graph.dot" << endl;

    int start;
    cout << "Enter start vertex: ";
    cin >> start;

    TDijkstraResult dHeapRes;
    TDijkstraResult binRes;
    TDijkstraResult fibRes;
    try
    {
        dHeapRes = dijkstraDHeap(g, start);
        binRes = dijkstraBinomialHeap(g, start);
        fibRes = dijkstraFibonacciHeap(g, start);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        return 0;
    }

    cout << "D-heap time: " << dHeapRes.time << endl;
    cout << "Binomial heap time: " << binRes.time << endl;
    cout << "Fibonacci heap time: " << fibRes.time << endl;

    while (true)
    {
        int finish;
        cout << "Enter finish vertex (-1 to exit): ";
        cin >> finish;
        if (finish == -1) { break; }

        vector<int> path = getPath(dHeapRes, finish);
        cout << "Cost: " << dHeapRes.dist[finish] << endl;
        cout << "Path: ";
        printPath(path);
    }

    return 0;
}
