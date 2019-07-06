#include "graphm.h"
#include <iomanip>

//-----------------graphm.cpp--------------------------
// Author: Chris Kelley
// Creation Date: 2/10/2018
// Last Modified: 2/17/2018
// Course: CSS343B
// Project: Assignment #3
// ----------------------------------------------------
// Purpose: Build a graph using an adjacency matrix. 
// Find shortest path on data in adjacency matrix using
// Dijckstra's algorithm
//------------------------------------------------------
// Special Algorithm: Dijckstra's algorithm
//------------------------------------------------------


GraphM::GraphM()
{
	//initialize data members
	for(int i = 1; i < MAXNODES; i++)
	{
		for(int j = 1; j < MAXNODES; j++)
		{
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
			C[i][j] = INT_MAX;
		}
	}
	size = 0;
}

void GraphM::buildGraph(ifstream& input)
{
	int origin = 0;
	int desintation = 0;
	int edgeWeight = 0;
	string description;
	input >> size;

	//set data values in data array
	for(int i = 1; i <= size ; i++)
	{
		//check for valid input
		if (input.peek() < std::char_traits<char>::to_int_type(132)
			&& input.peek() > std::char_traits<char>::to_int_type(33))
		{
			data[i].setData(input);
		}
		else
		{
			input.get();
			i--;
		}				
	}

	//input origin node, destination node and edge weight
	input >> origin;
	input >> desintation;
	input >> edgeWeight;

	//insert each edge into the graph
	while(origin != 0)
	{
		insertEdge(origin, desintation, edgeWeight);
		input >> origin;
		input >> desintation;
		input >> edgeWeight;
	}
}

void GraphM::insertEdge(int origin, int dest, int weight)
{
	C[origin][dest] = weight;
}

void GraphM::removeEdge(int origin, int dest)
{
	C[origin][dest] = INT_MAX;
}

void GraphM::findShortestPath()
{
	//not visited, shortest distance vertex at this point
	int v;

	//iterate through each vertex to each other vertex
	for(int source = 1; source <= size; source++)
	{
		//set distance from source node to source node to zero
		T[source][source].dist = 0;

		//starting point is source node
		v = source;

		//finds the distance from source to all other nodes
		for(int i = 1; i <= size; i++)
		{
			int min = INT_MAX;

			//find v, current shortest distance, not visited
			for(int j = 1; j <= size; j++)
			{
				if(!T[source][j].visited)
				{
					if(T[source][j].dist < min)
					{
						min = T[source][j].dist;
						v = j;
					}
				}
			}
			T[source][v].visited = true;

			//check each vertex adjacent to v
			for(int j = 1; j <= size; j++)
			{				
				//check if vertex is adjacent
				if(C[v][j] != INT_MAX)
				{
					//check if adjacent vertex has been visited
					if(!T[source][j].visited)
					{
						if(T[source][j].dist > T[source][v].dist + C[v][j])
						{
							T[source][j].dist = T[source][v].dist + C[v][j];
							T[source][j].path = v;
						}
					}
				}
			}
		}
	}
}

void GraphM::displayAll()
{
	//print headers
	cout << setw(20) << "Description";
	cout << setw(12) << "From Node";
	cout << setw(12) << "To Node";
	cout << setw(20) << "Dijckstra's";
	cout << setw(10) << "Path";

	for(int i = 1; i <= size; i++)
	{
		cout << endl;
		cout << setw(20) << data[i];
		cout << endl;
		for(int j = 1; j <= size; j++)
		{
			//array to hold shortest path, in reverse order
			int * path = new int[size];
			bool hasPath = false;
			if(j != i)
			{
				cout << setw(20) << " ";
				cout << setw(10) << i;
				cout << setw(10) << j;

				//print weight of shortest path, if it exists
				if(T[i][j].dist != INT_MAX)
				{
					cout << setw(20) << T[i][j].dist;
					hasPath = true;
				}
				else
				{
					cout << setw(20) << "---";
				}

				//if a path exists, iterate through nodes
				//add to path arrary then print path
				if(hasPath)
				{
					int v = j;
					int count = 0;

					path[count] = j;

					//repeatedly make v = previous node in shortest path
					while (T[i][v].dist != 0)
					{
						count++;
						path[count] = T[i][v].path;
						v = T[i][v].path;
					}
					cout << setw(10);

					//print path
					for (int k = count; k >= 0; k--)
					{
						cout << path[k] << " ";
					}
				}				
			}
			cout << endl;
			delete[] path;
		}
		cout << endl;
	}
}

void GraphM::display(int origin, int dest)
{
	cout << setw(10) << origin;
	cout << setw(10) << dest;
	bool hasPath = true;
	if(T[origin][dest].dist != INT_MAX)
	{
		cout << setw(10) << T[origin][dest].dist;
	}
	else
	{
		cout << setw(10) << "---";
		hasPath = false;
	}
	cout << setw(20) << " ";

	int * path = new int[size];
	int count = 0;
	int v = dest;
	path[count] = v;
	while(T[origin][v].dist != 0 && hasPath)
	{
		
		count++;
		if(T[origin][v].dist == INT_MAX)
		{
			hasPath = false;
			break;
		}
		path[count] = T[origin][v].path;
		v = T[origin][v].path;
	}

	//if a path exists for the specified origin and destination
	if(hasPath)
	{
		for (int i = count; i >= 0; i--)
		{
			cout << path[i] << " ";
		}
		cout << endl;
		for (int i = count; i >= 0; i--)
		{
			cout << data[path[i]] << endl;
		}
	}
	else
	{
		cout << "----" << endl;
	}
	cout << endl;

	delete[] path;
}




