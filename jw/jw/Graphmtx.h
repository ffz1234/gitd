#pragma once
#ifndef GRAPHMTX_H
#define GRAPHMTX_H


#include "Graph.h"
#include <iostream>
using namespace std;

class Graphmtx : public Graph
{
public:
	Graphmtx(int sz = DeafultVertices);
	~Graphmtx()
	{
		delete[] VerticesList;
		delete[] Edge;
	}
	char getValue(int i);
	int getWeight(int v1, int v2);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const char vertex);
	bool insertEdge(int v1, int v2, int cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
protected:
	char *VerticesList;		//¶¥µã±í
	int * *Edge;				//ÁÚ½Ó¾ØÕó
	int getVertexPos(char vertex);
};

#endif // !GRAPHMTX_H