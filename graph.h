/*
Name: Lydia Shiffler 
Date:4/23/18
*/

#include <list>
#include <vector>
#include <iostream>
#include <fstream>

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
	double **weight;
	int *edges;	
	double *edgeWeights; 
	
	
};

void graphType::makeGraph()
{
	ifstream fin;
	string file;
	ofstream fout;

	int weights;
	int cases;
	int vertex;
	int adjacentVertex;
	
	cout << "Enter file name: ";
	cin >> file;
	fin.open(file.c_str());

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
		weights = new int*[graphSize];
		for(int i = 0; i < graphSize; i++)
		{
			weights[i] = new double[graphSize];
		}

		for(int i = 0; i < graphSize; i++)
		{
			for(int j = 0; j < graphSize; j++)
			{
				weights[i][j] = 9999;
			}
		}
		edges = new int[graphSize];
		edgeWeights = new double[graphSize];

		for(int index = 0; index < roads; index++)
		{
			fin >> vertex;
			fin >> adjacentVertex;
			graph[vertex].push_back(adjacentVertex);
			fin >> weight;
			if(weights[vertex][adjacentVertex] < weights)
			{
				weights[vertex][adjacentVertex] = weights[vertex][adjacentVertex];
			}
			if(weights[adjacentVertex][vertex] < weights)
			{
				weights[adjacentVertex][vertex] = weights[adjacentVertex][vertex];
			}
			else
			{
				weights[vertex][adjacentVertex] = weights;
				weights[adjacentVertex][vertex] = weights;
			}
		}
		minSpanning(0, fout);
		cases--;
	}	
	fin.close();
}

void graphType::minSpanning(int sVertex, ofstream& fout){
	int startV;
	int endV;
	double minWeight;
	source = sVertex;

	bool *X = new bool[graphSize];

	for(int i = 0; i < graphSize; i++)
	{
		X[i] = false;
		edges[i] = source;
		edgeWeights[i] = weight[source][i];
	}

	X[source] = true;
	edgeWeights[source] = 0;

	for(int i = 0; i < graphSize - 1; i++)
	{
		minWeight = 9999;
		for(int j = 0; j < graphSize; j++)
		{
			if(X[j])
			{
				for(int k = 0; k < graphSize; k++)
				{
					if(!X[k] && weight[j][k] < minWeight && weight[k][j] < minWeight)
					{
						endV = k;
						startV = j;
						minWeight = weight[j][k];
					}
				}
			}
		}
		X[endV] = true;
		edges[endV] = startV;
		edgeWeights[endV] = minWeight;
	}

	int maxWeight = 0;
	for(int i = 0; i < graphSize; ++i)
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
