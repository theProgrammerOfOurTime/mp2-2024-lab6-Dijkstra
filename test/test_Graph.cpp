#include <gtest.h>
#include "graph.h"
#include <sstream>

template<class T>
class GraphInterface : public Graph<T>
{
public:
    void SetUp()
    {
        this->vertexes_number = 3;
        this->edges_number = 2;
        this->infinity = 9;
        this->adjList.resize(3);
        this->adjList[0].push_back({ 1, 5 });
        this->adjList[1].push_back({ 0, 5 });
        this->adjList[1].push_back({ 2, 3 });
        this->adjList[2].push_back({ 1, 3 });
    }
    GraphInterface()
    {
        SetUp();
    }  
    int& getVertexesNumber()
    { 
        return this->vertexes_number; 
    }
    int& getEdgesNumber() 
    { 
        return this->edges_number;
    }
    T& getInfinity()
    { 
        return this->infinity;
    }
    Vector<Vector<std::pair<int32_t, T>>>& getAdjList() 
    { 
        return this->adjList;
    }
    bool callCheckSinglyConnected() const
    { 
        return this->checkSinglyConnected();
    }
    void callDFS(int32_t stV, Vector<bool>& used) const 
    { 
        this->DFS(stV, used);
        return;
    }
};

GraphInterface<int> test;

TEST(Graph, canCreateGraph)
{
    ASSERT_NO_THROW(Graph<int>());
}

TEST(Graph, PrivateFieldsAccess)
{
    test.SetUp();
    EXPECT_EQ(test.getVertexesNumber(), 3);
    EXPECT_EQ(test.getEdgesNumber(), 2);
    EXPECT_EQ(test.getInfinity(), 9);
    EXPECT_EQ(test.getAdjList().length(), 3);
}

TEST(Graph, DFSTest)
{
    Vector<bool> used(3, false);
    test.callDFS(0, used);

    EXPECT_TRUE(used[0]);
    EXPECT_TRUE(used[1]);
    EXPECT_TRUE(used[2]);
}

TEST(Graph, ConnectivityTest)
{
    EXPECT_TRUE(test.callCheckSinglyConnected());

    test.getAdjList()[1].resize(1);
    test.getAdjList()[2].clear();

    EXPECT_FALSE(test.callCheckSinglyConnected());
}

TEST(Graph, InputTest)
{
    std::istringstream input("3 2 0 1 5 1 2 3");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());
    
    test.input();
    std::cin.rdbuf(old);

    EXPECT_EQ(test.getVertexesNumber(), 3);
    EXPECT_EQ(test.getEdgesNumber(), 2);
    EXPECT_EQ(test.getAdjList()[0][0].first, 1);
    EXPECT_EQ(test.getAdjList()[0][0].second, 5);
}

TEST(Graph, GenerationTest1)
{
    std::istringstream input("4 5");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());

    test.generationGragh();
    std::cin.rdbuf(old);

    EXPECT_EQ(test.getVertexesNumber(), 4);
    EXPECT_EQ(test.getEdgesNumber(), 5);
    EXPECT_TRUE(test.callCheckSinglyConnected());
}

TEST(Graph, GenerationTest2)
{
    std::istringstream input("50 49");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());

    test.generationGragh();
    std::cin.rdbuf(old);

    EXPECT_EQ(test.getVertexesNumber(), 50);
    EXPECT_EQ(test.getEdgesNumber(), 49);
    EXPECT_TRUE(test.callCheckSinglyConnected());
}

TEST(Graph, GenerationTest3)
{
    std::istringstream input("10 45");
    std::streambuf* old = std::cin.rdbuf(input.rdbuf());

    test.generationGragh();
    std::cin.rdbuf(old);

    EXPECT_EQ(test.getVertexesNumber(), 10);
    EXPECT_EQ(test.getEdgesNumber(), 45);
    EXPECT_TRUE(test.callCheckSinglyConnected());
}