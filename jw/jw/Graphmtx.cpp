#include "Graphmtx.h"	
char Graphmtx::getValue(int i) {
	return (i >= 0 && i <= numVertices) ? VerticesList[i] : NULL;
}


int Graphmtx::getWeight(int v1, int v2) {
	return (v1 != -1 && v2 != -1) ? Edge[v1][v2] : 0;
}


bool Graphmtx::insertVertex(const char vertex)
{
	if (numVertices == maxVertices)
		return false;
	VerticesList[numVertices++] = vertex;
	return true;
}

bool Graphmtx::insertEdge(int v1, int v2, int cost)
{
	if (v1 > -1 && v1< numVertices && v2>-1 && v2<numVertices && Edge[v1][v2] == maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = cost;
		numEdges++;
		return true;
	}
	else return false;
}


Graphmtx::Graphmtx(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new char[maxVertices];
	Edge = (int **) new int*[maxVertices];
	for (i = 0; i<maxVertices; i++)
		Edge[i] = new int[maxVertices];
	for (i = 0; i<maxVertices; i++)
		for (j = 0; j<maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : maxWeight;
}


int Graphmtx::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col <numVertices; col++)
			if (Edge[v][col]>0 && Edge[v][col]<maxWeight)
				return col;
	}
	return -1;
}

int Graphmtx::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col<numVertices; col++)
			if (Edge[v][col]>0 && Edge[v][col]<maxWeight)
				return col;
	}
	return -1;
}




bool Graphmtx::removeVertex(int v)
{
	if (v < 0 && v >= numVertices)
		return false;
	if (numVertices == 1)
		return false;
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];
	for (i = 0; i<numVertices; i++)
	{
		if (Edge[i][v] >0 && Edge[i][v] <maxWeight)
			numEdges--;
	}
	for (i = 0; i<numVertices; i++)
	{
		Edge[i][v] = Edge[i][numVertices - 1];
	}
	numVertices--;
	for (j = 0; j<numVertices; j++)
		Edge[v][j] = Edge[numVertices][j];
	return true;
}


bool Graphmtx::removeEdge(int v1, int v2)
{
	if (v1 > -1 && v1< numVertices && v2>-1 && v2<numVertices && Edge[v1][v2] > 0 && Edge[v1][v2]< maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		numEdges--;
		return true;
	}
	else
	{
		return false;
	}
}


int Graphmtx::getVertexPos(char vertex) {
	for (int i = 0; i<numVertices; i++)
	{
		if (VerticesList[i] == vertex)
			return i;
	}
	return -1;
}

