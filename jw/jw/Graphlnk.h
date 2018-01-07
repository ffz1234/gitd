#ifndef GRAPHLNK_H
#define GRAPHLNK_H
#include "Graph.h"

template<class T, class E>
class Graphlnk : public Graph<T, E>
{
	friend istream& operator >> (istream& in, Graphlnk<T, E>& G);
	//friend ostream& operator << (ostream& out,Graphlnk<T,E>& G);
public:
	Graphlnk(int sz = DeafultVertices);
	~Graphlnk();
	T getValue(int i)					//取位置为i的顶点中的值
	{
		return (i >= 0 && i< numVertices) ? NodeTable[i].data : 0;
	}
	E getWeight(int v1, int v2);			//返回边(v1,v2)的权值
	bool insertVertex(const T vertex);
	bool removeVertex(int v);
	bool insertEdge(int v1, int v2, E cost);
	bool removeEdge(int v1, int v2);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	int NumberOfVertices()
	{
		return this->numVertices;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int InDegree(int v) const;			//计算v点的入度
	int OutDegree(int v)const;			//计算v点的出度
	int Degree(int v)const;				//计算v点的度
										////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	Vertex<T, E> * NodeTable;
	int getVertexPos(const T vertex)
	{
		for (int i = 0; i< numVertices; i++)
			if (NodeTable[i].data == vertex)
				return i;
		return -1;
	}
};
template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz /* = DeafultVertices */)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = NULL;

	try
	{
		NodeTable = new Vertex<T, E>[maxVertices];
	}
	catch (bad_alloc & memExp)
	{
		cerr << memExp.what() << endl;
	}
	//NodeTable = new  struct Vertex<T,E>[maxVertices];
	//if(NodeTable = NULL)
	//{
	//	cerr << "存储分配错误！"<<endl;
	//	exit(1);
	//}
	for (int i = 0; i<maxVertices; i++)
	{
		NodeTable[i].adj = NULL;
		//	NodeTable[i].adj->cost = maxWeight;
	}
}
template<class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
	for (int i = 0; i<maxVertices; i++)
	{
		Edge<T, E> * p = NodeTable[i].adj;
		while (p != NULL)
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[] NodeTable;
}
template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		Edge<T, E> * p = NodeTable[v].adj;
		if (p != NULL) return p->dest;
	}
	return -1;
}
template<class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{
	if (v != -1)
	{
		Edge<T, E> * p = NodeTable[v].adj;
		while (p != NULL && p->dest != w)
		{
			p = p->link;
		}
		if (p != NULL && p->link != NULL)
			return p->link->dest;
	}
	return -1;
}
template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E> *p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL)
			return p->cost;
		else return maxWeight;
	}
}
template<class T, class E>
bool Graphlnk<T, E>::insertVertex(const T vertex)
{
	if (numVertices == maxVertices) return false;
	NodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}
template<class T, class E>
bool Graphlnk<T, E>::removeVertex(int v)
{
	if (numVertices == 1 || v<0 || v >= numVertices)return false;
	Edge<T, E> *p, *s, *t;
	int i, k;
	while (NodeTable[v].adj != NULL)
	{
		p = NodeTable[v].adj;
		k = p->dest;
		s = NodeTable[k].adj;
		t = NULL;
		while (s != NULL && s->dest != v)
		{
			t = s;
			s = s->link;
		}
		if (s != NULL)
		{
			if (t == NULL) NodeTable[k].adj = s->link;
			else t->link = s->link;
			delete s;
		}
		NodeTable[v].adj = p->link;
		delete p;
		numEdges--;
	}
	numVertices--;
	NodeTable[v].data = NodeTable[numVertices].data;
	p = NodeTable[v].adj = NodeTable[numVertices].adj;
	while (p != NULL)
	{
		s = NodeTable[p->dest].adj;
		while (s != NULL)
			if (s->dest == numVertices) { s->dest = v; break; }
			else s = s->link;
	}
	return true;
}
template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E cost)
{
	if (v1 >= 0 && v1< numVertices && v2 >= 0 && v2<numVertices)
	{
		Edge<T, E> *q, *p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL) return false;
		p = new Edge<T, E>;
		q = new Edge<T, E>;
		p->dest = v2;
		p->cost = cost;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->cost = cost;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return false;
}
template<class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E> *p = NodeTable[v1].adj, *q = NULL, *s = p;
		while (p != NULL && p->dest != v2)
		{
			q = p;
			p = p->link;
		}
		if (p != NULL)
		{
			if (p == s)
				NodeTable[v1].adj = p->link;
			else
			{
				q->link = p->link;
			}
			delete p;
		}
		else
		{
			return false;
		}
		p = NodeTable[v2].adj;
		q = NULL;
		s = p;
		while (p->dest != v1)
		{
			q = NULL;
			s = p;
		}
		if (p == s)
			NodeTable[v2].adj = p->link;
		else
		{
			q->link = p->link;
		}
		delete p;
		return true;
	}
	return false;
}
template<class T, class E>
ostream& operator << (ostream& out, Graphlnk<T, E>& G)
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
			if (G.getWeight(i, j) == maxWeight)
				cout << setw(10) << "Max";
			else
				cout << setw(10) << G.getWeight(i, j);
		}
		cout << "\n";
	}
	return out;
}
template<class T, class E>
int Graphlnk<T, E>::InDegree(int v)const
{
	//在此插入你的代码，替换掉下面的语句
	int i, j = 0;
	Edge<T, E> *p;
	if (v >= 0 && v<maxVertices)//判断序号v的合法性
	{
		for (i = 0; i<numVertices; i++)
		{
			p = NodeTable[i].adj;
			while (p != NULL&&p->dest != v)
				p = p->link;
			if (p != NULL)
				j++;
		}
		return j;
	}
	else
		return -1;
}

//计算带权有向图G中第v个顶点的出度，时间复杂度:O(n)。
template<class T, class E>
int Graphlnk<T, E>::OutDegree(int v)const
{
	//在此插入你的代码，替换掉下面的语句
	int j = 0;
	Edge<T, E> *p;
	if (v >= 0 && v<maxVertices)//判断序号v的合法性
	{
		//for(i=0;i<=NumOfVertices();i++)
		//{
		p = NodeTable[v].adj;///////////
		while (p != NULL)
		{
			j++;
			p = p->link;
		}
		//}
		return j;
	}
	else
		return -1;

}

//计算带权有向图G中第v个顶点的度，时间复杂度:O(n)。
template<class T, class E>
int Graphlnk<T, E>::Degree(int v)const
{
	return(InDegree(v) + OutDegree(v));
}

#endif