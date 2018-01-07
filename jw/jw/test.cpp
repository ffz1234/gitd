#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;
#include "Graph.h"
#include "Graphlnk.h"
#include "Graphmtx.h"
#include "GraphApp.h"
const int MaxVertices = 100;	//ͼ�е���󶥵���Ŀ
const int MaxWeight = 10000;	//������Ȩֵ


typedef char VT;	//ͼ�ж�������������VT
typedef int WT;		//ͼ�б�Ȩֵ����WT

					//����Ϣ���Ͷ���
struct RowColWeight
{
	int row;							//���±�
	int col;							//���±�
	WT weight;							//Ȩֵ
};
void PrintItem(VT item)	//�������������
{
	cout << item << " ";
}
template<class T, class E>
void CreatGraph(Graphlnk<T, E> &G, VT V[], int n, RowColWeight E[], int e)
{	//��ͼG�в���n������V��e����E

	//��ͼG�в���n������
	for (int i = 0; i < n; i++)
		G.insertVertex(V[i]);

	//��ͼG�в���e����
	for (int k = 0; k < e; k++)
		G.insertEdge(E[k].row, E[k].col, E[k].weight);
}
template<class T, class E>
void CreatGraph(Graphmtx<T, E> &G, VT V[], int n, RowColWeight E[], int e)
//��ͼG�в���n������V��e����E
{
	//��ͼG�в���n������
	for (int i = 0; i < n; i++)
		G.insertVertex(V[i]);

	//��ͼG�в���e����
	for (int k = 0; k < e; k++)
		G.insertEdge(E[k].row, E[k].col, E[k].weight);
}

int main()
{
	char v1[] = { '1','2','3','4','5','6','7','8','9' };//������Ϣ
	RowColWeight rcw1[] = { { 0,1,2 },{ 0,5,1 },{ 0,6,1 },{ 1,3,4 },{ 1,2,2 },{ 2,5,3 },{ 2,6,2 },{ 2,3,1 },{ 3,6,6 },{ 3,4,1 },{ 3,7,5 },{ 3,8,2 } ,{ 4,5,5 },{ 5,6,1 },{ 6,7,3 },{ 7,8,2 } };//����Ϣ
	int n = 9, e = 16, i, j, k;
	WT *distance = new int[n];
	int *path = new int[n];
	//MSTEdgeNode<VT, WT> MST[MaxVertices];
	Graphmtx<VT, WT> g1;
	CreatGraph(g1, v1, n, rcw1, e);
	cout << "------��ӭ����·�ɱ�������--------" << endl;
	cout << "------1.���·������·�ɱ�--------" << endl;
	cout << "------2.ɾ��·�ɱ�ı�--------" << endl;
	cout << "���������ѡ��" << endl;
	cin >> i;
	if (i == 1)
	{
		cout << "��������Ҫ·�ɱ��·��������1-9��" << endl;
		cin >> i;
		ShortestPath(g1, i - 1, distance, path);
		cout << endl;
		//MinSpanTree<VT, WT> tree;
	}
	if (i == 2)
	{
		cout << "��������Ҫɾ����·������";
		cin >> i;
		g1.removeVertex(i);
		cout << "��������Ҫ·�ɱ��·��������1-9��" << endl;
		cin >> i;
		ShortestPath(g1, i - 1, distance, path);
	}
	else cout << "���������������";
	system("pause");

}