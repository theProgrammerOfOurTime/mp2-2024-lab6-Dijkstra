#pragma once
#include "graph.h"
#include <string>

template<class TypeWeights, class THeap>
class Dijkstra
{
private:
	Graph<TypeWeights>* g;
	Vector<size_t> way;
public:
	Dijkstra(Graph<TypeWeights>* _g) : g(_g), way(g->vertexes_number) { }
	Vector<TypeWeights> dijkstra(int32_t stV);
	std::string getWay(int32_t stV);
};

template<class TypeWeights, class THeap>
std::string Dijkstra<TypeWeights, THeap>::getWay(int32_t stV)
{
	std::string res;
	while (way[stV] != stV)
	{
		res += std::to_string(stV) + " ";
		stV = way[stV];
	}
	res += std::to_string(stV);
	return res;
}

template<class TypeWeights, class THeap>
Vector<TypeWeights> Dijkstra<TypeWeights, THeap>::dijkstra(int32_t stV)
{
	if (stV >= g->vertexes_number || stV < 0) throw std::runtime_error("incorrect nomber of start vertex");
	Vector<bool> used(g->vertexes_number);
	Vector<TypeWeights> weights(g->vertexes_number, g->infinity);
	way[stV] = stV;
	weights[stV] = 0;
	THeap bheap;
	bheap.add(myPair(stV, 0));
	while (!bheap.empty())
	{
		//std::cout << "heap size = " << bheap.size() << std::endl;
		myPair minV = bheap.extructMin();
		used[minV.v] = true;
		for (size_t j = 0; j < g->adjList[minV.v].length(); j++)
		{
			auto adjV = g->adjList[minV.v][j];
			if (used[adjV.first] == true) { continue; }
			int32_t new_weight = adjV.second + minV.w;
			if (new_weight < weights[adjV.first])
			{
				bheap.add(myPair(adjV.first, new_weight));
				weights[adjV.first] = new_weight;
				way[adjV.first] = minV.v;
			}
		}
	}
	return weights;
}