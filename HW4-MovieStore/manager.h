#ifndef MANAGER_H
#define MANAGER_H
#include "hashtable.h"
#include "movieList.h"

//---------------------------------------------------------------
//File: manager.h
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Contains Manager class that handles the business logic 
//		 of the program.
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Manager class
// Purpose: Handles business logic of program. Accept input ifstream
// and processes and stores data (customers, movies) and commands
// executed on that data
//------------------------------------------------------------------

class Manager
{
private:
	//hashtable containing references to customers
	HashTable customers;

	//vector containing references to movies
	MovieList movies;

	//private helper methods

	//--------------------displayInventory-----------------------------
	//Traverses all Movies in inventory (Movies stored in MovieList object)
	//Prints information for each movie(release date, title, stock, etc.
	void displayInventory();

	//--------------------displayHistory-------------------------------
	//Display the history for a customer (specified in the input ifstream)
	//Searches HashTable for specified customer and prints transactions 
	//from specified customer (output: 'B'  = Borrow, 'R' = Return)
	void displayHistory(std::ifstream& input);

	//--------------------borrowMovie----------------------------------
	//Executes when file input indicates a borrow movie command. Identifies
	// what kind of movie it is and calls appropriate helper method to
	//process input
	void borrowMovie(std::ifstream& input);

	//--------------------returnMovie----------------------------------
	//Executes when file input indicates a return movie command. Identifie
	//what kind of movie it is and calls appropriate helper method to 
	//proces input.
	void returnMovie(std::ifstream& input);

	//--------------------handleInvalidCommand---------------------------
	//Executes when command input is not a normal command: (I, H, B, R)
	//Outputs error message and processes file input for next file input
	void handleInvalidCommand(std::ifstream& input, char type) const;

	//--------------------handleInvalidMovieMedium----------------------
	//Executes when medium indicated in a borrow or return command
	//is not a recognized medium. Outputs error message and processs
	//invalid file input for next file input.
	void handleInvalidMedium(std::ifstream& input) const;

	//--------------------handleInvalidTYpe-----------------------------
	//Executes when genre of movie is no recognized. Outputs error message
	//and processes invalid file input for next file input
	void handleInvalidType(std::ifstream& input, const int custID) const;

	//--------------------borrowClassic----------------------------------
	//Helper method for borrowMovie method. Processes input specific to 
	//Classic movies & identifies customer. If specified Movie and
	//specified Customer are found in storage, command is executed.
	void borrowClassic(std::ifstream& input, const int custID);

	//--------------------borrowComedy----------------------------------
	//Helper method for borrowMovie method. Processes input specific to 
	//Comedy movies & identifies customer. If specified Movie and
	//specified Customer are found in storage, command is executed.
	void borrowComedy(std::ifstream& input, const int custID);

	//--------------------borrowDrama----------------------------------
	//Helper method for borrowMovie method. Processes input specific to 
	//Drama movies & identifies customer. If specified Movie and
	//specified Customer are found in storage, command is executed.
	void borrowDrama(std::ifstream& input, const int custID);

	//--------------------returnComedy---------------------------------
	//Helper method for returnMovie method. Processes input specific to
	//Comedy movies & identifies customer. If specified Movie and 
	//specified Customer are found in storage, command is executed
	void returnComedy(std::ifstream& input, const int custID);

	//--------------------returnClassic---------------------------------
	//Helper method for returnMovie method. Processes input specific to
	//Classic movies & identifies customer. If specified Movie and 
	//specified Customer are found in storage, command is executed
	void returnClassic(std::ifstream& input, const int custID);

	//--------------------returnDrama---------------------------------
	//Helper method for returnMovie method. Processes input specific to
	//Drama movies & identifies customer. If specified Movie and 
	//specified Customer are found in storage, command is executed
	void returnDrama(std::ifstream& input, const int custID);

public:

	//default constructor
	Manager() {}

	//---------------------buildCustomerList----------------------------
	//Reads file input containing list of customers and each customer's
	//associated data (name, customer ID). Creates Customer object 
	//for each customer and stores object reference in a HashTable
	void buildCustomerList();

	//---------------------buildMovieList-------------------------------
	//Reads file input containing list of movies and each movie's 
	//associated data (name,release date, stock, etc). Store reference
	//to each movie as Movie object in MovieList
	void buildMovieList();

	//---------------------executeCommand------------------------------
	//Reads file input containing list of commands to perform of stored
	//movies and customers. Processes input data and executes commands
	void executeCommands();
};
#endif

