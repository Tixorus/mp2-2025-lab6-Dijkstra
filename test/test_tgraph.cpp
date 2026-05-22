#include "tdheap.h"
#include "tdijkstra.h"
#include "tbinomialheap.h"
#include "tfibonacciheap.h"
#include "tgraph.h"

#include <gtest.h>

TEST(TGraph, can_create_graph_with_positive_size)
{
    ASSERT_NO_THROW(TGraph g(5));
}

TEST(TGraph, cant_create_graph_with_negative_size)
{
    ASSERT_ANY_THROW(TGraph g(-1));
}

TEST(TGraph, can_add_edge)
{
    TGraph g(2);
    ASSERT_NO_THROW(g.addEdge(0, 1, 5));
    EXPECT_EQ(g[0][0].to, 1);
    EXPECT_EQ(g[0][0].w, 5);
}

TEST(TGraph, cant_add_edge_with_negative_weight)
{
    TGraph g(2);
    ASSERT_ANY_THROW(g.addEdge(0, 1, -5));
}

TEST(TGraph, cant_add_edge_with_wrong_vertex)
{
    TGraph g(2);
    ASSERT_ANY_THROW(g.addEdge(0, 3, 5));
}

TEST(TGraph, can_check_connected_graph)
{
    TGraph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    EXPECT_EQ(g.isConnected(), 1);
}

TEST(TGraph, can_check_not_connected_graph)
{
    TGraph g(3);
    g.addEdge(0, 1, 1);
    EXPECT_EQ(g.isConnected(), 0);
}

TEST(TGraph, can_create_random_connected_graph)
{
    TGraph g = TGraph::randomGraph(10, 15);
    EXPECT_EQ(g.isConnected(), 1);
}

TEST(TDHeap, can_extract_min)
{
    TDHeap h(3);
    h.push(0, 5);
    h.push(1, 2);
    h.push(2, 7);
    EXPECT_EQ(h.extractMin(), 1);
}

TEST(TDHeap, can_decrease_key)
{
    TDHeap h(3);
    h.push(0, 5);
    h.push(1, 8);
    h.decreaseKey(1, 1);
    EXPECT_EQ(h.extractMin(), 1);
}

TEST(TBinomialHeap, can_extract_min)
{
    TBinomialHeap h(3);
    h.push(0, 5);
    h.push(1, 2);
    h.push(2, 7);
    EXPECT_EQ(h.extractMin(), 1);
}

TEST(TBinomialHeap, can_decrease_key)
{
    TBinomialHeap h(3);
    h.push(0, 5);
    h.push(1, 8);
    h.decreaseKey(1, 1);
    EXPECT_EQ(h.extractMin(), 1);
}

TEST(TFibonacciHeap, can_extract_min)
{
    TFibonacciHeap h(3);
    h.push(0, 5);
    h.push(1, 2);
    h.push(2, 7);
    EXPECT_EQ(h.extractMin(), 1);
}

TEST(TFibonacciHeap, can_decrease_key)
{
    TFibonacciHeap h(3);
    h.push(0, 5);
    h.push(1, 8);
    h.decreaseKey(1, 1);
    EXPECT_EQ(h.extractMin(), 1);
}

TEST(TDijkstra, can_find_shortest_distances_with_d_heap)
{
    TGraph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 10);
    g.addEdge(2, 3, 3);

    TDijkstraResult res = dijkstraDHeap(g, 0);

    EXPECT_EQ(res.dist[3], 6);
}

TEST(TDijkstra, can_find_shortest_distances_with_binomial_heap)
{
    TGraph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 10);
    g.addEdge(2, 3, 3);

    TDijkstraResult res = dijkstraBinomialHeap(g, 0);

    EXPECT_EQ(res.dist[3], 6);
}

TEST(TDijkstra, can_find_shortest_distances_with_fibonacci_heap)
{
    TGraph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 10);
    g.addEdge(2, 3, 3);

    TDijkstraResult res = dijkstraFibonacciHeap(g, 0);

    EXPECT_EQ(res.dist[3], 6);
}

TEST(TDijkstra, throws_when_graph_is_not_connected)
{
    TGraph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1);

    ASSERT_ANY_THROW(dijkstraDHeap(g, 0));
}

TEST(TDijkstra, can_get_path)
{
    TGraph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 10);
    g.addEdge(2, 3, 3);

    TDijkstraResult res = dijkstraDHeap(g, 0);
    vector<int> path = getPath(res, 3);

    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 2);
    EXPECT_EQ(path[3], 3);
}
