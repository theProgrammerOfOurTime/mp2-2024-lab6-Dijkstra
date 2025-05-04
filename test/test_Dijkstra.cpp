#include <gtest.h>
#include "Dijkstra.h"
#include "BinHeap.h"
#include "FibonacciHeap.h"
#include "myData.h"
#include <sstream>

template<class TypeWeights, class THeap>
class DijkstraInterface : public Dijkstra<TypeWeights, THeap>
{
public:
    using Dijkstra<TypeWeights, THeap>::Dijkstra;
    Vector<size_t>& getWayVector()
    {
        return this->way;
    }
    Graph<TypeWeights>* getGraph()
    {
        return this->g;
    }
};

TEST(DijkstraTest, ConstructorInitializesCorrectlyOnBinHeap)
{
    Graph<int> graph;
    std::istringstream input("3 3 0 1 5 0 2 8 1 2 1");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    graph.input();
    std::cin.rdbuf(old);
    DijkstraInterface<int, BinHeap<myPair>> dijkstra(&graph);
    EXPECT_EQ(dijkstra.getGraph(), &graph);
    EXPECT_EQ(dijkstra.getWayVector().length(), 3);
}

TEST(DijkstraTest, DijkstraComputesCorrectWeightsOnBinHeap)
{
    Graph<int> graph;
    std::istringstream input("3 3 0 1 5 0 2 8 1 2 1");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    graph.input();
    std::cin.rdbuf(old);
    DijkstraInterface<int, BinHeap<myPair>> dijkstra(&graph);

    Vector<int> weights = dijkstra.dijkstra(0);

    EXPECT_EQ(weights[0], 0); 
    EXPECT_EQ(weights[1], 5);
    EXPECT_EQ(weights[2], 6);
}

TEST(DijkstraTest, PathRestorationWorksOnBinHeap)
{
    Graph<int> graph;
    std::istringstream input("3 3 0 1 5 0 2 8 1 2 1");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    graph.input();
    std::cin.rdbuf(old);
    DijkstraInterface<int, BinHeap<myPair>> dijkstra(&graph);
    dijkstra.dijkstra(0);
    std::string path = dijkstra.getWay(2);
    EXPECT_TRUE(path == "2 1 0");
    auto& way = dijkstra.getWayVector();
    EXPECT_EQ(way[0], 0);
    EXPECT_EQ(way[1], 0);
    EXPECT_EQ(way[2], 1);
}

TEST(DijkstraTest, ThrowsOnInvalidStartVertexOnBinHeap)
{
    Graph<int> graph;
    std::istringstream input("3 3 0 1 5 0 2 8 1 2 1");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    graph.input();
    std::cin.rdbuf(old);
    DijkstraInterface<int, BinHeap<myPair>> dijkstra(&graph);

    ASSERT_ANY_THROW(dijkstra.dijkstra(-1));
    ASSERT_ANY_THROW(dijkstra.dijkstra(3));
}

TEST(DijkstraTest, ConstructorInitializesCorrectlyOnFibonacciHeap)
{
    Graph<int> graph;
    std::istringstream input("3 3 0 1 5 0 2 8 1 2 1");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    graph.input();
    std::cin.rdbuf(old);
    DijkstraInterface<int, FibonacciHeap<myPair>> dijkstra(&graph);
    EXPECT_EQ(dijkstra.getGraph(), &graph);
    EXPECT_EQ(dijkstra.getWayVector().length(), 3);
}

TEST(DijkstraTest, DijkstraComputesCorrectWeightsOnFibonacciHeap)
{
    Graph<int> graph;
    std::istringstream input("3 3 0 1 5 0 2 8 1 2 1");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    graph.input();
    std::cin.rdbuf(old);
    DijkstraInterface<int, FibonacciHeap<myPair>> dijkstra(&graph);

    Vector<int> weights = dijkstra.dijkstra(0);

    EXPECT_EQ(weights[0], 0);
    EXPECT_EQ(weights[1], 5);
    EXPECT_EQ(weights[2], 6);
}

TEST(DijkstraTest, PathRestorationWorksOnFibonacciHeap)
{
    Graph<int> graph;
    std::istringstream input("3 3 0 1 5 0 2 8 1 2 1");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    graph.input();
    std::cin.rdbuf(old);
    DijkstraInterface<int, FibonacciHeap<myPair>> dijkstra(&graph);
    dijkstra.dijkstra(0);
    std::string path = dijkstra.getWay(2);
    EXPECT_TRUE(path == "2 1 0");
    auto& way = dijkstra.getWayVector();
    EXPECT_EQ(way[0], 0);
    EXPECT_EQ(way[1], 0);
    EXPECT_EQ(way[2], 1);
}

TEST(DijkstraTest, ThrowsOnInvalidStartVertexOnFibonacciHeap)
{
    Graph<int> graph;
    std::istringstream input("3 3 0 1 5 0 2 8 1 2 1");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    graph.input();
    std::cin.rdbuf(old);
    DijkstraInterface<int, FibonacciHeap<myPair>> dijkstra(&graph);

    ASSERT_ANY_THROW(dijkstra.dijkstra(-1));
    ASSERT_ANY_THROW(dijkstra.dijkstra(3));
}