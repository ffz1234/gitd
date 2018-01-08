#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include<iomanip>


#include<limits.h>
const int maxWeight = INT_MAX;
const int DeafultVertices = 30;			//代表最大顶点数 =n

struct Edge
{
	int dest;			//边的另一个顶点位置
	int cost;				//边上的权值
	Edge * link;	//下一条边链指针
	Edge() { cost = maxWeight; }
	Edge(int num, int weight) : dest(num), cost(weight), link(NULL) {}
	bool operator != (Edge& R)const
	{
		return (dest != R.dest) ? true : false;
	}
};

struct Vertex
{
	char data;
	Edge *adj;			//边链表的头指针
};


class Graph
{
public:
	Graph();
	~Graph();
	bool GraphEmpty()const;
	bool GraphFull()const;
	int NumberOfVertices();		//返回当前顶点数
	int NunberOfEdges();			//返回当前边数
	virtual char getValue(int i) = 0;							//取顶点i的值
	virtual int getWeight(int v1, int v2) = 0;					//取边（v1，v2）上的权值
	virtual int getFirstNeighbor(int v) = 0;				//取顶点v的第个邻接顶点
	virtual int getNextNeighbor(int v, int w) = 0;			//取邻接顶点w的下一个邻接顶点
	virtual bool insertVertex(const char vertex) = 0;			//插入一个顶点vertex
	virtual bool insertEdge(int v1, int v2, int cost) = 0;		//插入边(v1,v2),权为cost
	virtual bool removeVertex(int v) = 0;					//删去顶点v和所有与v相关的边
	virtual bool removeEdge(int v1, int v2) = 0;				//删去边(v1,v2)
protected:
	int maxVertices;
	int numEdges;
	int numVertices;
	int getVertexPos(char vertex);				//给出顶点vertex在图中的位置
};

#endif // !GRAPH_H