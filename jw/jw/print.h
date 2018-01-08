#ifndef GRAPHAPP_H
#define GRAPHAPP_H
#include "Graphmtx.h"
#include "Graph.h"
#include <limits.h>
const int maxValue = INT_MAX;



void printpath(Graph& G, int v, int dist[], int path[])   //输出下一跳
{
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



void ShortestPath(Graph& G, int v, int dist[], int path[])
{
	int n = G.NumberOfVertices();
	bool *S = new bool[n];
	int i, j, k;
	int w, min;
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
	printpath(G, v, dist, path);
}

#endif
