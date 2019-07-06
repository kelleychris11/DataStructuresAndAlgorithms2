#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include "limits.h"
const int MAXNODES = 101;

//-----------------graphm.h--------------------------
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

//-----------------GraphM Class-------------------------
// Purpose: Create Graph using an adjacency list. 
// The shortest path through the graph from each
// vertex to every other vertex can be calculated 
// using Dijckstra's algorithm
class GraphM
{
private:
	//----------------TableType Struct-------------------
	//Contains data of each vertex to each other vertex
	struct TableType
	{
		bool visited;
		//shortest distance from source so far
		int dist;
		//previous node in path of min dist
		int path;
	};

	//data for graph nodes
	NodeData data[MAXNODES];

	//adjacency matrix
	int C[MAXNODES][MAXNODES];

	//number of nodes in graph
	int size;

	//stores visited, distance, path
	TableType T[MAXNODES][MAXNODES];

public:

	//------------------GraphM----------------------------
	//Default Constructor
	GraphM();

	//------------------buildGraph------------------------
	// Build graph with provided input file data. Data is 
	// stored in adjacency matrix C member and matrix T member.
	void buildGraph(ifstream& input);

	//------------------insertEdge-------------------------
	// Insert edge into adjacency matrix. Weight is inserted
	// at row 'origin' and colum 'dest' of C data member
	void insertEdge(int origin, int dest, int weight);

	//------------------removeEdge-------------------------
	// Remove edge from adjacency matrix. Infinity, represented
	// as INT_MAX is inserted into row 'origin' and column 'dest'
	// of data member C
	void removeEdge(int origin, int dest);

	//------------------findShortestPath---------------------
	// Find shortest path of each vertex in graph to every other
	// vertex. Uses Dijckstra's method to find path.
	void findShortestPath();

	//------------------displayAll----------------------------
	// Displays paths from each vertex in graph to every other 
	// vertex. Prints origin, destination, weight of path, and
	// vertices in path for each possible path in graph.
	void displayAll();

	//------------------display-------------------------------
	// Display path from specified origin to specified destination.
	// Displays origin number, destination number, weight, vertices
	// in path, and names of all vertices in path.
	void display(int origin, int dest);
};
#endif

