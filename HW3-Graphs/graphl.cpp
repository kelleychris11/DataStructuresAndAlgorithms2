#include "graphl.h"
#include <iomanip>

//-----------------graphl.cpp--------------------------
// Author: Chris Kelley
// Creation Date: 2/10/2018
// Last Modified: 2/18/2018
// Course: CSS343B
// Project: Assignment #3
// ----------------------------------------------------
// Purpose: Implement a graph data structure that will
// hold data in an adjacency list. A depth-first-search
// can be performed on the data in the adjacency list
//------------------------------------------------------
// Special Algorithm: Graph Depth-First-Search
//------------------------------------------------------

GraphL::GraphL()
{
}

GraphL::~GraphL()
{
	for(int i = 1; i<= size; i++)
	{
		if(graphNodeArray[i].edgeHead == NULL)
		{
			continue;
		}
		int count = 1;
		EdgeNode * cur = graphNodeArray[i].edgeHead;
		//get # of EdgeNodes in link
		while(cur->nextEdge != NULL)
		{
			cur = cur->nextEdge;
			count++;
		}
		delete cur;
		int numLinks = count;
		for(int k = 1; k < count; k++)
		{
			cur = graphNodeArray[i].edgeHead;
			for(int j = 1; j < numLinks - 1; j++)
			{
				cur = cur->nextEdge;
			}
			delete cur;
			numLinks--;
		}
	}
}

void GraphL::buildGraph(ifstream& input)
{

	//check for valid input or end of file
	int c = input.peek();
	while (!isdigit(c))
	{
		if (input.eof())
		{
			return;
		}
		input.get();
		c = input.peek();
	}

	input >> size;

	int origin = 0;
	int destination = 0;
	string description = "";
	graphNodeArray = new GraphNode[size + 1];

	//Iterates through input file and populates graphNodeArray
	for(int i = 1; i <= size; i++)
	{
		//check for valid input
		if (input.peek() < std::char_traits<char>::to_int_type(132)
			&& input.peek() > std::char_traits<char>::to_int_type(33))
		{
			getline(input, description);
			NodeData * newNode = new NodeData(description);
			graphNodeArray[i].data = newNode;
			graphNodeArray[i].edgeHead = NULL;
			graphNodeArray[i].visited = false;
		}
		else
		{
			input.get();
			i--;
		}
	}
	input >> origin;
	input >> destination;

	//Link EdgeNodes to edgeHead member of GraphNodes
	while(destination != 0)
	{
		//if GraphNode does not have EdgeNode linked to it
		//create new EdgeNode to link
		if(graphNodeArray[origin].edgeHead == NULL)
		{
			graphNodeArray[origin].edgeHead = new EdgeNode;
			graphNodeArray[origin].edgeHead->adjGraphNode = destination;
			graphNodeArray[origin].edgeHead->nextEdge = NULL;
		}
		//if GraphNode already has EdgeNode linked, insert new EdgeNode
		//at beginning of link. New EdgeNode becomes current edgeHead
		else
		{
			EdgeNode * newNode = new EdgeNode;
			newNode->adjGraphNode = destination;
			newNode->nextEdge = graphNodeArray[origin].edgeHead;
			graphNodeArray[origin].edgeHead = newNode;
		}
		input >> origin;
		input >> destination;
	}
}

void GraphL::displayGraph()
{
	//iterate through adjacency list and print values
	for(int i = 1; i <= size; i++)
	{
		cout << "Node " << i;
		cout << setw(10) << " ";
		cout << *graphNodeArray[i].data << endl;
		EdgeNode * curEdge = graphNodeArray[i].edgeHead;

		//Check if current edge has values
		if (curEdge != NULL)
		{
			cout << "   Edge " << i << " " << curEdge->adjGraphNode << endl;

			//Iterate through edges until NULL edge is found
			while(curEdge->nextEdge != NULL)
			{
				cout << "   Edge " << i << " " << curEdge->nextEdge->adjGraphNode << endl;
				curEdge = curEdge->nextEdge;
			}
		}
	}
}

void GraphL::depthFirstSearch()
{
	//initialize values to false
	for(int i = 1; i <= size; i++)
	{
		graphNodeArray[i].visited = false;
	}

	cout << "Depth-First Ordering: ";

	for(int i = 1; i <= size; i++)
	{
		if(!graphNodeArray[i].visited)
		{
			dfsHelper(i);
		}
	}
	cout << endl;
}

void GraphL::dfsHelper(int n)
{
	graphNodeArray[n].visited = true;

	//output current vertex
	cout << n << " ";
	EdgeNode * curEdge = graphNodeArray[n].edgeHead;

	while(curEdge != NULL)
	{
		if(!graphNodeArray[curEdge->adjGraphNode].visited)
		{
			dfsHelper(curEdge->adjGraphNode);
		}
		curEdge = curEdge->nextEdge;
	}
}

