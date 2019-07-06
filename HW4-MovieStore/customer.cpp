#include "customer.h"
#include <iostream>

//---------------------------------------------------------------
//File: customer.cpp
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Contains customer class. Used for storing information
//		on each specific customer
//-----------------------------------------------------------------

Customer::Customer(const int custID, const std::string firstName, 
	const std::string lastName)
{
	this->custID = custID;
	this->firstName = firstName;
	this->lastName = lastName;
}

void Customer::addTransaction(const char t)
{
	transactions.push_back(t);
}

void Customer::addMovie(Movie* m)
{
	movieHistory.push_back(m);
}

void Customer::gethistory() const
{
	std::cout << firstName << " " << lastName 
	<< "'s transaction history: " << std::endl;
	for (int i = 0; i < transactions.size(); i++)
	{
		std::cout << "Type: " << transactions[i] << "\t Title: " 
		<< movieHistory[i]->getTitle() << std::endl;
	}
	std::cout << std::endl;
}

std::string Customer::getName() const
{
    std::string output = firstName + " " + lastName;
    return output;
}
