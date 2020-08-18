#include "DQGraph.h"

// Graph Implementation in C++ without using STL
int main()
{
	// array of graph edges as per above diagram.
	dqlib::Edge edges[] =
	{
		// pair (x, y) represents edge from x to y
		{ 0, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 },
		{ 3, 2 }, { 4, 5 }, { 5, 4 }
	};

	// Number of vertices in the graph
	int N = 6;

	// calculate number of edges
	int n = sizeof(edges)/sizeof(edges[0]);

	// construct graph
	
	dqlib::DQGraph dqgraph(edges, n, N);


	dqgraph.printAdjList();

	return 0;
}