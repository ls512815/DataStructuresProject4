/*
Name: Lydia Shiffler 
Date: 4/23/18
description: Minimum Spanning Tree Project
*/



#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;


class graphType
{

public:
	void makeGraph();
	void minSpanning(int sVertex, ofstream &fout);

protected:
	int graphSize;
	list<int> *graph;
	int source;
	double **weights;
	int *edges;
	double *edgeWeights;
};



void graphType::makeGraph()
{
	ifstream fin;
	string filename;
	ofstream fout;

	int cases;
	int vertex;
	int adjacentVertex;
	int weight;
	cout<<"Your input file should be set up as so:" << endl;
	cout<< endl;
	cout<<"- The first of each input file is the number of test cases T." << endl;
	cout<<"- The first line of each test case is the number of cities N and number of roads M." << endl;
	cout<<"- The cities are conveniently labeled with integers ranging from 0 to N-2" << endl;
	cout<<"- Following the city and road counts are M lines describing the M roads." << endl;
	cout<<"- Each road is defined as a pair of cities along with the distance between those citites" << endl;
	cout<< endl;
	cout << "Enter input file name: ";
	cin >> filename;

	fin.open(filename.c_str());
	if(fin.fail())
	{
		cout << "File not found" << endl;
		return;
	}

	fout.open("output1.dat");
	cout << "Output file created and named 'output1.dat'" << endl;


	fin >> cases;
	while(cases != 0)
	{
		fin >> graphSize;
		int roads;
		fin >> roads;
		graph = new list<int>[graphSize];
		weights = new double*[graphSize];
		for(int i = 0; i < graphSize; ++i)
		{
			weights[i] = new double[graphSize];
		}

		for(int i = 0; i < graphSize; ++i)
		{
			for(int j = 0; j < graphSize; ++j)
			{
				weights[i][j] = 9999;
			}
		}
		edges = new int[graphSize];
		edgeWeights = new double[graphSize];

		for(int index = 0; index < roads; ++index)
		{
			fin >> vertex;
			fin >> adjacentVertex;
			graph[vertex].push_back(adjacentVertex);
			fin >> weight;
			if(weights[vertex][adjacentVertex] < weight)
			{
				weights[vertex][adjacentVertex] = weights[vertex][adjacentVertex];
			}
			if(weights[adjacentVertex][vertex] < weight)
			{
				weights[adjacentVertex][vertex] = weights[adjacentVertex][vertex];
			}
			else
			{
				weights[vertex][adjacentVertex] = weight;
				weights[adjacentVertex][vertex] = weight;
			}
		}
		minSpanning(0, fout);
		cases--;
	}	
	fin.close();
}

void graphType::minSpanning(int sVertex, ofstream& fout)
{
	int startVertex;
	int endVertex;
	double minWeight;

	source = sVertex;
	bool *minSearchTreeV = new bool[graphSize];

	for(int i = 0; i < graphSize; ++i)
	{
		minSearchTreeV[i] = false;
		edges[i] = source;
		edgeWeights[i] = weights[source][i];
	}

	minSearchTreeV[source] = true;
	edgeWeights[source] = 0;

	for(int i = 0; i < graphSize - 1; ++i)
	{
		minWeight = 9999;
		for(int j = 0; j < graphSize; ++j)
		{
			if(minSearchTreeV[j])
			{
				for(int k = 0; k < graphSize; ++k)
				{
					if(!minSearchTreeV[k] && weights[j][k] < minWeight && weights[k][j] < minWeight)
					{
						endVertex = k;
						startVertex = j;
						minWeight = weights[j][k];
					}
				}
			}
		}
		minSearchTreeV[endVertex] = true;
		edges[endVertex] = startVertex;
		edgeWeights[endVertex] = minWeight;
	}


	int maxWeight = 0;
	for(int i = 0; i<graphSize; ++i)
	{
		if(edgeWeights[i] > maxWeight)
		{
			maxWeight = edgeWeights[i];
		}
	}
	fout << maxWeight << endl;

	for(int j = 0; j < graphSize; ++j)
	{
		if(edges[j] != j)
		{
			fout << "("<<j << "," << edges[j] << "," << edgeWeights[j] << ") ";
		}
	}
	fout << endl;
}
