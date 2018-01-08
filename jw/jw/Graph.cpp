#include "Graph.h"



Graph::Graph()
{
	int sz = DeafultVertices;
}


Graph::~Graph()
{
}


bool Graph::GraphEmpty()const
{
	if (numEdges == 0)
		return true;
	else
	{
		return false;
	}
}


bool Graph::GraphFull() const
{
	if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
		return true;
	else return false;
}


int Graph::NumberOfVertices() { return numVertices; }


int Graph::NunberOfEdges() { return numEdges; }