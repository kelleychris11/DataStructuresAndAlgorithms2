#include "hashtable.h"

//---------------------------------------------------------------
//File: hashtable.cpp
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Contains Manager class that handles the business logic 
//		 of the program.
//-----------------------------------------------------------------

HashTable::HashTable()
{
	custArray = std::vector<std::vector<Customer*> >(103); // initialize size
}

HashTable::~HashTable()
{
	for (int i = 0; i < custArray.size(); i++)
	{
		for (int j = 0; j < custArray[i].size(); j++)
		{
				delete custArray[i][j];
		}
	}

}

int HashTable::getHashCode(const int custID) const
{
	return custID * 37;
}

int HashTable::getIndex(const int custID) const
{
	return getHashCode(custID) % DEFAULT_VALUE;
}

bool HashTable::insert(const int custID, Customer * cust)
{
	int indexLocation = getIndex(custID);
	for (int i = 0; i < custArray[indexLocation].size(); i++)
	{
		if (custArray[indexLocation][i]->custID == custID)
		{
			return false;
		}
	}
	custArray[indexLocation].push_back(cust);
	return true;
}

Customer * HashTable::find(const int custID) 
{
	int indexLocation = getIndex(custID);
	for (int i = 0; i < custArray[indexLocation].size(); i++)
	{
		if (custArray[indexLocation][i]->custID == custID)
		{
			return custArray[indexLocation][i];
		}
	}
	return NULL;
}

std::vector<std::vector<Customer*> > * HashTable::getCustArray() {
    return &custArray;
}

