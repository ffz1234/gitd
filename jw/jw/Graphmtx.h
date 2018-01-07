#ifndef GRAPHMTX_H
#define GRAPHMTX_H
#include "Graph.h"
#include <iostream>
using namespace std;
template<class T, class E>
class Graphmtx : public Graph<T, E>
{
public:
	Graphmtx(int sz = DeafultVertices);
	~Graphmtx()
	{
		delete[] VerticesList;
		delete[] Edge;
	}
	T getValue(int i)
	{
		return (i >= 0 && i <= numVertices) ? VerticesList[i] : NULL;
	}
	E getWeight(int v1, int v2)
	{
		return (v1 != -1 && v2 != -1) ? Edge[v1][v2] : 0;
	}
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const T vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
protected:
	T *VerticesList;		//顶点表
	E * *Edge;				//邻接矩阵
	int getVertexPos(T vertex)
	{
		for (int i = 0; i<numVertices; i++)
		{
			if (VerticesList[i] == vertex)
				return i;
		}
		return -1;
	}
};
template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz /* = DefaultVertices */)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new T[maxVertices];
	Edge = (int **) new int*[maxVertices];
	for (i = 0; i<maxVertices; i++)
		Edge[i] = new int[maxVertices];
	for (i = 0; i<maxVertices; i++)
		for (j = 0; j<maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : maxWeight;
}
template<class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col <numVertices; col++)
			if (Edge[v][col]>0 && Edge[v][col]<maxWeight)
				return col;
	}
	return -1;
}
template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col<numVertices; col++)
			if (Edge[v][col]>0 && Edge[v][col]<maxWeight)
				return col;
	}
	return -1;
}
template<class T, class E>
bool Graphmtx<T, E>::insertVertex(const T vertex)
{
	if (numVertices == maxVertices)
		return false;
	VerticesList[numVertices++] = vertex;
	return true;
}
template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v)
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
template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)
{
	if (v1 > -1 && v1< numVertices && v2>-1 && v2<numVertices && Edge[v1][v2] == maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = cost;
		numEdges++;
		return true;
	}
	else return false;
}
template<class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2)
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
template<class T, class E>
ostream& operator << (ostream& out, Graphmtx<T, E>& G)
{
	int i, j;
	cout << "顶点个数为:" << G.NumberOfVertices() << endl;
	cout << "边的条数为:" << G.NunberOfEdges() << endl;
	cout << "结点集合为:";
	for (i = 0; i< G.NumberOfVertices(); i++)
		cout << "     " << G.getValue(i);
	cout << "\n";
	cout << "权值集合为:\n";
	for (i = 0; i<G.NumberOfVertices(); i++)
	{
		for (j = 0; j<G.NumberOfVertices(); j++)
		{
			if (G.getWeight(i, j) == INT_MAX)
				cout << setw(10) << "Max" << " ";
			else
				cout << setw(10) << G.getWeight(i, j) << "";
		}
		cout << "\n";
	}
	return out;
}
#endif