#include "graph.h"
#include <iostream>

int main()
{
	Graph<double> g;
	try
	{
		g.input();
		g.print();
		auto dist = g.Dijkstra(1);
		for (int i = 0; i < dist.length(); i++)
		{
			std::cout << dist[i] << " ";
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
	
	return 0;
}