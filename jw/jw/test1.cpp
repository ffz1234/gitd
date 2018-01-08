#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include "Graph.h"
#include "Graphmtx.h"
#include"print.h"
using namespace std;
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


void CreatGraph(Graphmtx &G, char V[], int n, RowColWeight E[], int e)
//��ͼG�в���n������V��e����E
{
	//��ͼG�в���n������
	for (int i = 0; i < n; i++)
		G.insertVertex(V[i]);

	//��ͼG�в���e����
	for (int k = 0; k < e; k++)
		G.insertEdge(E[k].row, E[k].col, E[k].weight);
}

ostream& operator << (ostream& out, Graphmtx& G)
{
	int i, j;
	cout << "�������Ϊ:" << G.NumberOfVertices() << endl;
	cout << "�ߵ�����Ϊ:" << G.NunberOfEdges() << endl;
	cout << "��㼯��Ϊ:";
	for (i = 0; i< G.NumberOfVertices(); i++)
		cout << "     " << G.getValue(i);
	cout << "\n";
	cout << "Ȩֵ����Ϊ:\n";
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


int main()
{
	int i;
	int head, tail;
	char v1[] = { '1','2','3','4','5','6','7','8','9' };//������Ϣ
	RowColWeight rcw1[] = { { 0,1,2 },{ 0,5,1 },{ 0,6,1 },{ 1,2,2 },{ 1,3,4 },
	{ 2,3,1 },{ 2,5,3 },{ 2,6,2 },{ 3,4,1 },{ 3,6,6 },
	{ 3,7,5 },{ 3,8,2 },{ 4,5,5 },{ 5,6,1 },{ 6,7,3 },
	{ 7,8,2 } };//����Ϣ
	int n = 9, e = 16;
	WT *distance = new int[n];
	int *path = new int[n];
	Graphmtx g1;
	//MSTEdgeNode<VT, WT> MST[MaxVertices];
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
		main();
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
	if(i != 1 && i != 2)
	{cout << "���������������"; }
	system("pause");

}