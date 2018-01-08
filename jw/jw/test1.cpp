#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;
#include "Graph.h"
#include "Graphlnk.h"
#include "Graphmtx.h"
#include "GraphApp.h"
const int MaxVertices = 100;	//图中的最大顶点数目
const int MaxWeight = 10000;	//无穷大的权值


typedef char VT;	//图中顶点数据域类型VT
typedef int WT;		//图中边权值类型WT

					//边信息类型定义
struct RowColWeight
{
	int row;							//行下标
	int col;							//列下标
	WT weight;							//权值
};
void PrintItem(VT item)	//输出顶点数据域
{
	cout << item << " ";
}
template<class T, class E>
void CreatGraph(Graphlnk<T, E> &G, VT V[], int n, RowColWeight E[], int e)
{	//在图G中插入n个顶点V和e条边E

	//在图G中插入n个顶点
	for (int i = 0; i < n; i++)
		G.insertVertex(V[i]);

	//在图G中插入e条边
	for (int k = 0; k < e; k++)
		G.insertEdge(E[k].row, E[k].col, E[k].weight);
}
template<class T, class E>
void CreatGraph(Graphmtx<T, E> &G, VT V[], int n, RowColWeight E[], int e)
//在图G中插入n个顶点V和e条边E
{
	//在图G中插入n个顶点
	for (int i = 0; i < n; i++)
		G.insertVertex(V[i]);

	//在图G中插入e条边
	for (int k = 0; k < e; k++)
		G.insertEdge(E[k].row, E[k].col, E[k].weight);
}

int main()
{
	char v1[] = { '1','2','3','4','5','6','7','8','9' };//顶点信息
	RowColWeight rcw1[] = { { 0,1,2 },{ 0,5,1 },{ 0,6,1 },{ 1,3,4 },{ 1,2,2 },{ 2,5,3 },{ 2,6,2 },{ 2,3,1 },{ 3,6,6 },{ 3,4,1 },{ 3,7,5 },{ 3,8,2 } ,{ 4,5,5 },{ 5,6,1 },{ 6,7,3 },{ 7,8,2 } };//边信息
	int n = 9, e = 16, i, j, k;
	WT *distance = new int[n];
	int *path = new int[n];
	//MSTEdgeNode<VT, WT> MST[MaxVertices];
	Graphmtx<VT, WT> g1;
	CreatGraph(g1, v1, n, rcw1, e);
	cout << "------欢迎来到路由表管理界面--------" << endl;
	cout << "------1.输出路由器的路由表--------" << endl;
	cout << "------2.删出路由表的边--------" << endl;
	cout << "请输入你的选择：" << endl;
	cin >> i;
	if (i == 1)
	{
		cout << "请输入需要路由表的路由器：（1-9）" << endl;
		cin >> i;
		ShortestPath(g1, i - 1, distance, path);
		cout << endl;
		//MinSpanTree<VT, WT> tree;
	}
	if (i == 2)
	{
		cout << "请输入你要删除的路由器：";
		cin >> i;
		g1.removeVertex(i);
		cout << "请输入需要路由表的路由器：（1-9）" << endl;
		cin >> i;
		ShortestPath(g1, i - 1, distance, path);
	}
	else cout << "您输入的数据有误！";
	system("pause");

}