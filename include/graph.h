#pragma once

#include <iostream>
#include "Vector.h"
#include "myData.h"
#include "BinHeap.h"

template<class TypeWeights>
class Graph
{
private:
	int vertexes_number, edges_number;
	Vector <Vector<std::pair<int32_t, TypeWeights>>> adjList;
	TypeWeights infinity;//в качестве бесконечности используется сумма всех ребёр +1
	bool checkSinglyConnected() const;
	void DFS(const int32_t& stV, Vector<bool>& used) const;
public:
	Graph();
	void input();
	void print() const;
	Vector<TypeWeights> Dijkstra(int32_t stV);
};

template<class TypeWeights>
inline Graph<TypeWeights>::Graph() : vertexes_number(0), edges_number(0), infinity(1)
{
	
}

template<class TypeWeights>
void Graph<TypeWeights>::input()
{
	std::cout << "Enter the number of vertices: ";
	std::cin >> vertexes_number;
	std::cout << "enter the number of edges: ";
	std::cin >> edges_number;
	adjList.clear();
	adjList.resize(vertexes_number);
	for (int32_t i = 0; i < edges_number; i++)
	{
		int32_t a, b;
		int32_t w;
		std::cin >> a >> b >> w;
		if (a < 0 || b < 0 || a >= vertexes_number || b > vertexes_number) throw std::runtime_error("invalid index of vertex");
		if (w < 0) throw std::runtime_error("the weight of a vertex cannot be negative");
		infinity += w;
		adjList[a].push_back(std::make_pair(b, w));
		adjList[b].push_back(std::make_pair(a, w));
	}
	if (!checkSinglyConnected()) throw std::runtime_error("not singly connected graph");
	return;
}

template<class TypeWeights>
void Graph<TypeWeights>::print() const
{
	std::cout << "number of vertices = " << vertexes_number << std::endl;
	for (size_t i = 0; i < adjList.length(); i++)
	{
		if (adjList[i].length() == 0) continue;
		std::cout << i << ": { ";
		for (size_t j = 0; j < adjList[i].length(); j++)
		{
			std::cout << adjList[i][j].first << " ";
		}
		std::cout << "}" << std::endl;
	}
}

template<class TypeWeights>
bool Graph<TypeWeights>::checkSinglyConnected() const
{
	if (vertexes_number == 0) return true;
	Vector<bool> used(vertexes_number, false);
	DFS(0, used);
	for (int i = 0; i < vertexes_number; i++)
	{
		if (!used[i]) return false;
	}
	return true;
}

template<class TypeWeights>
void Graph<TypeWeights>::DFS(const int32_t& stV, Vector<bool>& used) const
{
	//std::cout << stV << " ";
	used[stV] = true;
	for (int j = 0; j < adjList[stV].length(); j++)
	{
		if (used[adjList[stV][j].first] == false) { DFS(adjList[stV][j].first, used); }
	}
	return;
}

template<class TypeWeights>
Vector<TypeWeights> Graph<TypeWeights>::Dijkstra(int32_t stV)
{
	Vector<bool> used(vertexes_number);
	Vector<TypeWeights> weights(vertexes_number, infinity);
	weights[stV] = 0;
	BinHeap<myPair> bheap;
	bheap.add(myPair(stV, 0));
	while (bheap.size() != 0)
	{
		//std::cout << "heap size = " << bheap.size() << std::endl;
		myPair minV = bheap.extructMin();
		used[minV.v] = true;
		for (size_t j = 0; j < adjList[minV.v].length(); j++)
		{
			auto adjV = adjList[minV.v][j];
			if (used[adjV.first] == true) { continue; }
			int32_t new_weight = adjV.second + minV.w;
			if (new_weight < weights[adjV.first])
			{
				bheap.add(myPair(adjV.first, new_weight));
				weights[adjV.first] = new_weight;
			}
		}
	}
	return weights;
}