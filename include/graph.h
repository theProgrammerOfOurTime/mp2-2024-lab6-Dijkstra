#pragma once

#include <iostream>
#include "Vector.h"
#include <string>
#include "myData.h"
#include "BinHeap.h"
#define GVDLL
#include "..\\Graphviz\\include\\graphviz\\gvc.h"
#include  "..\\Graphviz\\include\\graphviz\\cgraph.h"

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
	void generationGragh();
	void print() const;
	template<class TypeWeights, class THeap>
	friend class Dijkstra;
	
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
	if (vertexes_number - 1 > edges_number) throw std::runtime_error("A graph with this number of vertices and edges is not connected.");
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
	/*std::cout << "number of vertices = " << vertexes_number << std::endl;
	for (size_t i = 0; i < adjList.length(); i++)
	{
		if (adjList[i].length() == 0) continue;
		std::cout << i << ": { ";
		for (size_t j = 0; j < adjList[i].length(); j++)
		{
			std::cout << "(" << adjList[i][j].first << ", " << adjList[i][j].second << ")" << " ";
		}
		std::cout << "}" << std::endl;
	}*/
	GVC_t* gv = gvContext();
	Agraph_t* g = agopen(const_cast<char*>("g"), Agundirected, nullptr);
	agattr(g, AGNODE, const_cast<char*>("shape"), const_cast<char*>("circle"));

	Vector<Agnode_t*> nodes(vertexes_number);
	for (size_t i = 0; i < vertexes_number; i++)
	{
		nodes[i] = agnode(g, const_cast<char*>(std::to_string(i).c_str()), 1);
	}
	//запоминаем рёбра и веса, которые уже использовали, чтобы не было дублирования
	Vector<Vector<Vector<TypeWeights>>> usedAgedge(vertexes_number, Vector<Vector<TypeWeights>>(vertexes_number, Vector<TypeWeights>(0, TypeWeights(0))));
	for (size_t i = 0; i < adjList.length(); i++)
	{
		for (size_t j = 0; j < adjList[i].length(); j++)
		{
			bool fl = true;
			for (size_t k = 0; k < usedAgedge[i][adjList[i][j].first].length(); k++)
			{
				if (std::abs(usedAgedge[i][adjList[i][j].first][k] - adjList[i][j].second) < 1e-14)
				{
					fl = false;
					break;
				}
			}
			if (fl)
			{
				Agedge_t* e = agedge(g, nodes[i], nodes[adjList[i][j].first], nullptr, 1);
				agsafeset(e, const_cast<char*>("label"), const_cast<char*>((std::to_string((int)adjList[i][j].second) + "." + (std::to_string((int)(adjList[i][j].second * 100) - ((int)adjList[i][j].second) * 100))).c_str()), const_cast<char*>(""));
				usedAgedge[i][adjList[i][j].first].push_back(adjList[i][j].second);
				usedAgedge[adjList[i][j].first][i].push_back(adjList[i][j].second);
			}
			
		}
	}

	gvLayout(gv, g, "dot");
	gvRenderFilename(gv, g, "png", "graph.png");
	gvFreeLayout(gv, g);
	agclose(g);
	gvFreeContext(gv);
	std::cout << "The graph is displayed in the graph.png" << std::endl;
	return;
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
void Graph<TypeWeights>::generationGragh()
{
	std::cout << "Enter the number of vertices: ";
	std::cin >> vertexes_number;
	std::cout << "enter the number of edges: ";
	std::cin >> edges_number;
	if (vertexes_number - 1 > edges_number) throw std::runtime_error("A graph with this number of vertices and edges is not connected.");
	adjList.clear();
	adjList.resize(vertexes_number);
	//сначала будем генерировать дерево с помощью кода Прюфера, а дальше добавлять оставшиеся рёбра,
	//в таком случае граф всегда будет односвязный при m >= n - 1, где n - число вершин, а m - число рёбер
	srand(time(NULL));
	Vector<size_t> codePrifer(vertexes_number - 2, 0), cntUsed(vertexes_number);
	for (size_t i = 0; i < codePrifer.length(); i++) codePrifer[i] = rand() % vertexes_number;
	for (size_t i = 0; i < codePrifer.length(); i++) cntUsed[codePrifer[i]]++;
	for (size_t i = 0; i < codePrifer.length(); i++)
	{
		for (size_t j = 0; j < cntUsed.length(); j++)
		{
			if (cntUsed[j] == 0)
			{
				cntUsed[j] = -1; //вычёркиваем вершину
				cntUsed[codePrifer[i]]--;
				size_t w = rand();
				infinity += w;
				adjList[j].push_back(std::make_pair(codePrifer[i], w));
				adjList[codePrifer[i]].push_back(std::make_pair(j, w));
				break;
			}
		}
	}
	bool fl = false;
	size_t a, b, w = rand();
	for (size_t i = 0; i < cntUsed.length(); i++)
	{
		if (cntUsed[i] == 0 && !fl)
		{
			a = i;
			fl = true;
		}
		else if (cntUsed[i] == 0 && fl)
		{
			b = i;
			break;
		}
	}
	infinity += w;
	adjList[a].push_back(std::make_pair(b, w));
	adjList[b].push_back(std::make_pair(a, w));
	for (size_t i = 0; i < 1 + edges_number - vertexes_number; i++)
	{
		a = rand() % vertexes_number;
		b = rand() % vertexes_number;
		w = rand();
		infinity += w;
		adjList[a].push_back(std::make_pair(b, w));
		adjList[b].push_back(std::make_pair(a, w));
	}
	//if (!checkSinglyConnected()) throw std::runtime_error("not singly connected graph");
	return;
}