#include "graph.h"
#include "BinHeap.h"
#include "Dijkstra.h"
#include "FibonacciHeap.h"
#include <iostream>

int main()
{
	Graph<double> g;
	try
	{
		std::cout << "Generate a graph or enter it from the keyboard? 0/1" << std::endl;
		short move;
		std::cin >> move;
		if (move == 0) g.generationGragh();
		else if (move == 1) g.input();
		else throw std::runtime_error("incorrect value");
		std::cout << "Print graph? 0(No)/1(Yes)" << std::endl;
		std::cin >> move;
		if (move == 1) g.print();
		Dijkstra<double, BinHeap<myPair>> di1(&g);
		Dijkstra<double, FibonacciHeap<myPair>> di2(&g);
		std::cout << "Enter the starting vertex for Dijkstra's algorithm: " << std::endl;
		int32_t beginVer;
		std::cin >> beginVer;
		clock_t start = clock();
		auto dist1 = di1.dijkstra(beginVer);
		clock_t end = clock();
		std::cout << "Running time of Dijkstra's algorithm using binary heap: " << (double)(end - start) / 1000 << " sec." << std::endl;
		start = clock();
		auto dist2 = di2.dijkstra(beginVer);
		end = clock();
		std::cout << "Running time of Dijkstra's algorithm using Fibonacci heap: " << (double)(end - start) / 1000 << " sec." << std::endl << std::endl;
		bool fl = true;
		while (fl)
		{
			std::cout << "Enter the number of the vertex to which the shortest path and cost cannot be deduced?" << std::endl;
			std::cout << "To finish, enter -1." << std::endl;
			std::cin >> move;
			if (move == -1) fl = false;
			else
			{
				if (move < 0 || move >= dist1.length()) throw std::runtime_error("incorrect number of vertex");
				std::cout << "dist = " << dist1[move] << std::endl;
				//std::cout << "dist = " << dist2[move] << std::endl;
				std::cout << "way = " << di1.getWay(move) << std::endl;
				//std::cout << "way = " << di2.getWay(move) << std::endl;
			}
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
	
	return 0;
}