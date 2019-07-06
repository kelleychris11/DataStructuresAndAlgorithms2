#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
#include "limits.h"
struct EdgeNode;

//-----------------graphl.h--------------------------
// Author: Chris Kelley
// Creation Date: 2/10/2018
// Last Modified: 2/17/2018
// Course: CSS343B
// Project: Assignment #3
// ----------------------------------------------------
// Purpose: Implement a graph data structure that will
// hold data in an adjacency list. A depth-first-search
// can be performed on the data in the adjacency list
//------------------------------------------------------
// Special Algorithm: Graph Depth-First-Search
//------------------------------------------------------

//-----------------GraphNode Struct----------------------
// Purpose: Used for building a graph with adjacency list
// implementation. Contains data of the node and a pointer
// to an EdgeNode struct that contains information on 
// an adjacent node in the graph.
//------------------------------------------------------

struct GraphNode
{
	//head node of the list of edges
	EdgeNode* edgeHead;

	//data contained in the node
	NodeData* data;
	bool visited;
};

//-------------EdgeNode Struct----------------------
// Purpose: Provides information on an adjacent node.
// Contains a pointer to another edgenode.
//-------------------------------------------------- 

struct EdgeNode
{
	//subscript of the adjacent graph node
	int adjGraphNode;

	//Next node adjacent to the graphnode containing 
	//the headnode to this linked list of edgenodes.
	EdgeNode* nextEdge;
};

//-------------------GraphL Class---------------------------
// Purpose: Implement GraphNodes and EdgeNodes into an 
// adjacency list. Depth-First-Search may be performed
// on an instance of the class, provided that the buildGraph
// method has been run on the instance with valid data.
//----------------------------------------------------------

class GraphL
{
private:
	//array of GraphNodes. Represents vertices in the graph
	GraphNode* graphNodeArray;

	//Number of vertices in graph
	int size;

public:

	//-------------------GraphL-----------------------------
	// Default Constructor
	GraphL();

	//-------------------~GraphL-----------------------------
	//Destructor
	~GraphL();

	//-------------------buildGraph------------------------------
	// values provided in the input parameter are populated into
	// an adjacency list of GraphNodes and EdgeNodes. String vertex
	// data is stored in GraphNodes in the graphNodeArray member.
	// EdgeNodes are provided as from the input parameter and 
	// are included as EdgeNodes that link to the edgeHead member
	// of each GraphNode in the graphNodeArray
	void buildGraph(ifstream& input);

	//-------------------displayGraph-----------------------------
	// Displays information contained in the GraphNodes and EdgeNodes
	// of this. Traverses through all GraphNodes contained in 
	// the graphNodeArray member and all linked EdgeNodes and prints
	// string data and edges of all GraphNodes and EdgeNodes
	void displayGraph();

	//-------------------depthFirstSearch---------------------------
	// Performs depth-first-search traversal of the adjacency list and
	// prints each vertex number in the traversal. Traverses through 
	// each GraphNode and calls dfsHelper.
	void depthFirstSearch();

	//--------------------dfsHelper----------------------------------
	// Helper method to depthFirstSearch method. Recursively calls
	// itself and traverses through each GraphNode and linked 
	// EdgeNode.
	void dfsHelper(int n);
};
#endif

