#ifndef GRAPHAPP_H
#define GRAPHAPP_H
#include "Graphlnk.h"
#include "Graphmtx.h"
#include "Graph.h"
//#include "SeqQueue.h"
#include "MinHeap.h"
#include <limits.h>
/*template<class T,class E>
void DFS(Graph<T,E>& G,const T& v)
{//从顶点v出发，对图G进行深度优先遍历
int i,loc,n = G.NumberOfVertices();
bool * visited = new bool[n];
for( i = 0;i<n; i++)
visited[i] = false;
loc = G.getVertexPos(v);
for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n)
{

if (!visited[i])
DFS(G, loc, visited);
}
delete[] visited;

}
/*template<class T,class E>
void DFS(Graph<T,E>& G,int v,bool visited[])
{//从顶点v出发，以深度优先方式遍历访问所有可读入的尚未方位结点
cout<<G.getValue(v)<<" ";
visited[v] = true;
int w = G.getFirstNeighbor(v);
while (w != -1)
{
if(visited[w] == false)
DFS(G,w,visited);
w = G.getNextNeighbor(v,w);
}
}*/
/*template<class T,class E>
void BFS(Graph<T,E>& G,const T& v)
{//从顶点v出发，以广度优先的次序横向搜索图，算法中使用了一个队列
int i ,w ,n = G.NumberOfVertices();
bool * visited = new bool[n];
for( i =0; i<n;i++)
visited[i] = false;
int loc = G.getVertexPos(v);
SeqQueue<int> Q;

for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n)
{
if (!visited[i])
{
cout << G.getValue(v) << " ";
visited[loc] = true;
Q.EnQueue(loc);
while (!Q.IsEmpty())
{
Q.DeQueue(loc);
w = G.getFirstNeighbor(loc);
while (w != -1)
{
if (visited[w] == false)
{
cout << G.getValue(w) << " ";
visited[w] = true;
Q.EnQueue(w);
}
w = G.getNextNeighbor(loc, w);
}
}
delete[] visited;
}
}
}

template<class T,class E >
int * Path(Graph<T,E> &G,int v1)//使用广度优先搜索求解一个顶点到其他各顶点的路径（路径长度最小）。
{
return NULL;
}*/

template<class T, class E>
void printPath(Graph<T, E>& G, int v, E dist[], int path[])
{//输出path数组中存储的图G从顶点v到其余各顶点的路径和距离
	cout << "路由器" << G.getValue(v) << "的路由表为：" << endl;
	int i, j, k, n = G.NumberOfVertices();
	int * d = new int[n];
	for (i = 0; i<n; i++)
	{
		if (i != v)
		{
			j = i;
			k = 0;
			while (j != v)
			{
				d[k++] = j;
				j = path[j];
			}
			cout << "目的路由" << G.getValue(i) << "的下一跳为：" << " ";
			cout << G.getValue(d[k - 1]) << endl;
		}
	}
	delete[] d;
}


#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Dijkstra最短路径///////////////////////////////////////////////////////////////////
template<class T, class E>
void ShortestPath(Graph<T, E>& G, int v, E dist[], int path[])
{//Graph是一个带权有向图，本算法建立一个数组，dist[j],0<=j<n;是当前求到的从顶点v到顶点j的最短路径长度，同时用数组path存放求到的最短路径
	int n = G.NumberOfVertices();
	bool *S = new bool[n];
	int i, j, k;
	E w, min;
	for (i = 0; i<n; i++)
	{
		dist[i] = G.getWeight(v, i);
		S[i] = false;
		if (i != v && dist[i] <maxValue)
			path[i] = v;
		else
		{
			path[i] = -1;
		}
	}
	S[v] = true;
	dist[v] = 0;
	for (i = 0; i<n - 1; i++)
	{
		min = maxValue;
		int u = v;
		for (j = 0; j<n; j++)
		{
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;
		for (k = 0; k<n; k++)
		{
			w = G.getWeight(u, k);
			if (S[k] == false && w <maxValue && dist[u] + w<dist[k])
			{
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}
	printPath(G, v, dist, path);
}


/////////////////////////////最小生成树//////////////////////////////////////////////////////////////////////////////
const int maxValue = INT_MAX;
template<class T, class E>
struct MSTEdgeNode						//最小生成树边结点
{
	int  tail, head;						//两顶点的位置
	E key;								//边上的权值，为关键码
	MSTEdgeNode() :tail(-1), head(-1), key(0) {}
};
template<class T, class E>
class MinSpanTree
{
protected:
	MSTEdgeNode<T, E> * edgevalue;		//用边值数组表示树
	int maxSize, n;
public:
	MinSpanTree(int sz = DeafultVertices - 1) : maxSize(sz), n(0)
	{
		edgevalue = new MSTEdgeNode<T, E>[sz];
	}
	int Insert(MSTEdgeNode<T, E>& item);
};
template<class T, class E>
void Prim(Graph<T, E>& G, const int u0, MinSpanTree<T, E>& MST)
{
	MSTEdgeNode<T, E> ed;
	int i, v, count;
	int n = G.NumberOfVertices();
	int m = G.NunberOfEdges();
	int u = u0;
	MinHeap<E, MSTEdgeNode<T, E>> H(m);		//最小堆，关键码为E
	bool * Vmst = new bool[n];
	for (i = 0; i<n; i++)
	{
		Vmst[i] = false;
	}
	Vmst[u] = true;
	count = 1;
	do
	{
		v = G.getFirstNeighbor(u);
		while (v != -1)
		{
			if (Vmst[v] == false)
			{
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}

		while (H.IsEmpty() == false && count<n)
		{
			H.RemoveMin(ed);
			if (Vmst[ed.head] == false)
			{
				MST.Insert(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	} while (count<n);
}
