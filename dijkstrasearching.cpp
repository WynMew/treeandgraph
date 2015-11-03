#include "stdafx.h"
#include "stdio.h"
#include "string"
#include "sstream"
#include "iostream"

#define MAX 1000
using namespace std;

class graph
{
public:
	int size;
	int **adjmatrix;
	int **mgraph;

	graph();
	graph(int size);

	void addvalue(int i, int j, int key);
	void printmatrix();
	void dijkstra();
	void matrixtograph();
	bool neighbour(int x1,int y1,int x2, int y2);
	void printmgraph();
	int mindis(int *d, bool *s);

	~graph()
	{
		for (int i = 0; i < size; i++)
			delete[] adjmatrix[i];
		delete[] adjmatrix;
		for (int i = 0; i < size; i++)
			delete[] mgraph[i];
		delete[] mgraph;
	};
};

void graph::addvalue(int i, int j, int key)
{
	adjmatrix[i][j] = key;
}

graph::graph(int size)
{
	this->size = size;
	adjmatrix = new int*[size];

	for (int i = 0; i < size; i++)
	{
		adjmatrix[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			adjmatrix[i][j] = NULL;
		}
	}
}

void graph::printmatrix()
{
	int i = 0, j = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			cout << adjmatrix[i][j];
		}
		cout<<endl;
	}
}

void graph::printmgraph()
{
	int i = 0, j = 0;
	for (i = 0; i < size*size; i++)
	{
		for (j = 0; j < size*size; j++)
		{
			cout << mgraph[i][j]<< "\t";
		}
		cout << endl;
	}
}


bool graph::neighbour(int x1, int y1, int x2, int y2)
{
	bool flag = false;
	if ((abs(x1 - x2) == 0) && (abs(y1 - y2) == 1))
		flag = true;
	else if ((abs(x1 - x2) == 1) && (abs(y1 - y2) == 0))
		flag = true;
	return flag;
}

void graph::matrixtograph()
{
	int nodenum = size*size;
	mgraph = new int*[nodenum];
	for (int i = 0; i < nodenum; i++)
	{
		mgraph[i] = new int[nodenum];
		for (int j = 0; j < nodenum; j++)
		{
			mgraph[i][j] = MAX;
			if (i == j)
				mgraph[i][j] = 0;
		}
	}

	for (int x1 = 0; x1 < size; x1++)
	{
		for (int y1 = 0; y1 < size; y1++)
		{
			int i = size*x1 + y1;
			for (int x2 = 0; x2 < size; x2++)
			{
				for (int y2 = 0; y2 < size; y2++)
				{
					int j = size*x2 + y2;
					if (neighbour(x1, y1, x2, y2))
					{
						mgraph[i][j] = adjmatrix[x2][y2];
//						cout << x1 << "-" << y1 << ";" << x2 << "-" << y2 << endl;
//						cout << "i: " << i << ", j: " << j << "; " << mgraph[i][j] << endl;
					}

				}
			}

		}
	}
}

int graph::mindis(int *d, bool *s)
{
	int min = MAX, minindex;
	int numnode = size*size;
	for (int v = 0; v < numnode;v++)
	if ((s[v] == false) && (d[v] <= min))
		min = d[v], minindex = v;

	return minindex;
}

void graph::dijkstra()
{
	matrixtograph();
	printmgraph();
	int v = size*size;
	int *dis;
	dis = new int[v];
	bool *sptset;
	sptset = new bool[v];

	for (int i = 0; i < v; i++)
	{
		dis[i] = MAX;
		sptset[i] = false;
	}

	dis[0] = 0;

	for (int counter = 0; counter < v - 1; counter++)
	{
		int u = mindis(dis, sptset);
		sptset[u] = true;

		for (int i = 0; i < v; i++)
		{
			cout << u << "~" << i << endl;
			cout << sptset[i] << endl;
			cout << mgraph[u][i] << endl;
			cout << dis[u] << endl;
			cout << dis[i] << endl;
			if (sptset[i] == false && mgraph[u][i] < MAX&&dis[u] != MAX && (dis[u] + mgraph[u][i] < dis[i]))
				dis[i] = dis[u] + mgraph[u][i];
			cout << dis[i]<<endl;
		}
	}

	for (int i = 0; i < v; i++)
		cout << "Node distance from start: " << dis[i] << endl;

	delete[] dis;
	delete[] sptset;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int size;
	//cin >> size;
	//cin.ignore();
	size = 4;
	//	string line;
	string line[4];
	//sample input:
	line[0] = "0100";
	line[1] = "1110";
	line[2] = "1011";
	line[3] = "1010";
	graph mymap(size);
	for (int i = 0; i < size; i++)
	{
		//	getline(cin, line);
		for (int j = 0; j < size; j++)
		{
			//			int key = int(line[j]) - 48;
			int key = int(line[i][j]) - 48;
			mymap.addvalue(i, j, key);
			//			cout << mymap.adjmatrix[i][j];
		}
	}
	//mymap.printmatrix();
	//mymap.matrixtograph();
	//mymap.printmgraph();
	mymap.dijkstra();
	system("pause");
	return 0;
}
