#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <vector>
#include "movie.h"

//---------------------------------------------------------------
//File: customer.h
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Contains customer class. Used for storing information
//		on each specific customer
//-----------------------------------------------------------------

//--------------------------------------------------------------
//Customer class
// Purpose: Represents a customer. Contains data associated with 
// customer.
//---------------------------------------------------------------

class Customer
{
	friend class HashTable;
private:
	int custID;
	std::string lastName;
	std::string firstName;

	//history of transactions
	std::vector<char> transactions;

	//history of movies associated with each transaction
	std::vector<Movie*> movieHistory;

public:

	//constructor
	Customer(const int custID, const std::string firstName, const std::string lastName);
	
	//-------------------------addTransaction-----------------------
	//Add transaction to customer's transaction history
	void addTransaction(const char t);

	//-------------------------addMovie------------------------------
	//Add transaction to customer's transaction history
	void addMovie(Movie*);

	//------------------------ getHistory---------------------------
	//print transaction history of customer
	void gethistory() const;
    
	//-------------------------getName------------------------------
	//retun name of customer
    std::string getName() const;
};
#endif

