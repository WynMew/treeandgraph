// ConsoleApplication43.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "string"
#include "sstream"
#include "cmath"


using namespace std;

struct islands
{
	int x;
	int y;
};

class route
{
public:
	int numi;
	float E;

	bool *sset;

	route();
	route(int n, float e);

	islands *isd;
	int **distmatrix;
	long sum;
	void addislands(int coor, int num, char c);
	void printoutislands();
	void printoutdistmatrix();
	void compdistmat();
	void connected();
	bool allcon();
	void prim();
	int min();
	int *mindis;

	~route()
	{
		delete[] isd;
		delete[] sset;
		for (int i = 0; i < numi; i++)
			delete[] distmatrix[i];
		delete[] distmatrix;
	}

	islands start;
};

void route::addislands(int coor, int num, char c)
{
	if (c == 'x')
	{
		isd[num].x = coor;
		sset[num] = 0;
		mindis[num] = INT_MAX;
	}
	else
	{
		isd[num].y = coor;
	}
};

route::route(int n, float e)
{
	this->numi = n;
	this->E = e;
	isd = new islands[n];
	sset = new bool[n];
	mindis = new int[n];
}

void route::printoutislands()
{
	for (int i = 0; i < numi; i++)
	{
		cout << isd[i].x << " ~ " << isd[i].y << endl;
	}
}

void route::printoutdistmatrix()
{
	for (int i = 0; i < numi; i++)
	{
		for (int j = 0; j < numi; j++)
		{
			cout << distmatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void route::compdistmat()
{
	distmatrix = new int*[numi];
	for (int i = 0; i < numi; i++)
	{
		distmatrix[i] = new int[numi];
		for (int j = 0; j < numi; j++)
		{
			distmatrix[i][j] = sqrt(pow((isd[i].x - isd[j].x), 2) + pow((isd[i].y - isd[j].y), 2));
		}
	}
}


int route::min()
{
	int minIndex;
	int min = INT_MAX;
	for (int i = 0; i < numi; i++)
	{
		if ((sset[i] == 0) && (mindis[i] < min))
		{
			min = mindis[i];
			minIndex = i;
		}
	}

	return minIndex;
}

void route::prim()
{
	sset[0] = 1;
	for (int i = 0; i < numi; i++)
		mindis[i] = INT_MAX;
	mindis[0] = 0;

	sum = 0;

	for (int counter = 0; counter < numi-1; counter++)
	{
		for (int u = 0; u < numi; u++)
		{
			int tmpmin = INT_MAX;
			for (int v = 0; v < numi; v++)
			{
				if ((sset[u] == 0) && (sset[v] == 1))
				{
					if (distmatrix[u][v] < tmpmin)
					{
						mindis[u] = distmatrix[u][v];
					}
				}
			}
		}

		int tmp = min();
		sset[tmp] = 1;


		int tmpmin = INT_MAX;
		for (int v = 0; v < numi; v++)
		{
			if ((sset[v] == 1)&&(v!=tmp)&&(distmatrix[tmp][v]<tmpmin))
			{
				tmpmin = distmatrix[tmp][v];
			}
		}
		sum = sum + tmpmin;
	}

	sum = sum*E;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int numi;
	float E;
	//	cin >> numi;
	//	cin.ignore();
	numi = 4;
	string linex;
	string liney;
	string tmp;

	//cin >> linex;
	//cin.ignore();
	//cin >> liney;
	//cin.ignore();

	linex = "0 0 400 400";
	liney = "0 100 0 100";

	//	cin >> E;
	//	cin.ignore();
	E = 1.0;

	route myroute(numi, E);

	istringstream strx(linex);
	int counter = 0;
	while (getline(strx, tmp, ' '))
	{
		int x = atoi(tmp.c_str());
		//		cout << x << endl;
		myroute.addislands(x, counter, 'x');
		counter++;
	}

	counter = 0;
	istringstream stry(liney);
	while (getline(stry, tmp, ' '))
	{
		int y = atoi(tmp.c_str());
		//		cout << y << endl;
		myroute.addislands(y, counter, 'y');
		counter++;
	}

	myroute.compdistmat();
	myroute.printoutislands();
	myroute.printoutdistmatrix();
	myroute.prim();

	cout << myroute.sum << endl;

	system("pause");
	return 0;
}
