#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>
#include "customer.h"

const int DEFAULT_VALUE = 103;

//---------------------------------------------------------------
//File: hashtable.h
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Contains Manager class that handles the business logic 
//		 of the program.
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//HashTable class
//Purpose: Provide hashtable for storage of customer objects.
//	Uses open hashing to store items in a 2 dimensional vector array
//------------------------------------------------------------------

class HashTable
{
private:

	//store Customer objects using open hashing
	std::vector<std::vector<Customer*> > custArray;

	//private methods//////////////////////////////////

	//-----------------------getHashCode---------------------------------
	//Calculates and returns the hash code for a specified customer ID
	int getHashCode(const int custID) const;

	//---------------------- getIndex------------------------------------
	//Calculates and returns the index of a customer in the vector based
	//on the Customer's customer ID
	int getIndex(const int custID) const;

public:
	
	//default constructor
	HashTable();

	//destructor
	~HashTable();

	//-----------------------insert-------------------------------------
	//Insert specified Customer object reference into the hashtable 
	bool insert(const int custID, Customer * cust);

	//------------------------find---------------------------------------
	//search for customer with specified customer ID.
	//returns reference to customer or NULL if not found
	Customer * find (const int custID);
    
    //------------------------getCustArray-------------------------------
	//Returns array of Customer objects
    std::vector<std::vector<Customer*> > * getCustArray();
};
#endif

