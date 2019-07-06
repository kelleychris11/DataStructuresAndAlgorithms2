#include "manager.h"
#include <fstream>
#include <iostream>
#include <cctype>

//---------------------------------------------------------------
//File: manager.cpp
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Contains Manager class that handles the business logic 
//		 of the program.
//-----------------------------------------------------------------

void Manager::buildCustomerList()
{
	std::ifstream inFile;
	int custID;
	std::string firstName;
	std::string lastName;

	inFile.open("data4customers.txt");

	//check if file is valid
	if(!inFile)
	{
		std::cout << "Failed to open customer file" << std::endl;
	}

	for(;;)
	{
		if(inFile.eof())
		{
			break;
		}

		inFile >> custID;
		inFile >> lastName;
		inFile >> firstName;

		//Create customer with data and store it in Customers hashtable
		Customer * newCust = new Customer(custID, firstName, lastName);
		customers.insert(custID, newCust);
	}
	//TODO maybe add setData to Customer class
}

void Manager::buildMovieList()
{
	char type;
	std::ifstream inFile;
	inFile.open("data4movies.txt");

	//check if file is valid
	if(!inFile)
	{
		std::cout << "Failed to open movie file." << std::endl;
	}

	for(;;)
	{
		//look for valid input and end of file
		while(!isalpha(inFile.peek()))
		{
			if(inFile.peek() == EOF)
			{
				return;
			}
			inFile.get();
		}

		inFile >> type;

		//use factory class to instantiate movie to specific
		//child based on the genre of the movie
		Movie * newMovie = MovieFactory::createMovie(type);

		//handle invalid movie type
		if(!newMovie)
		{
			std::string field1;
			std::string field2;
			std::string field3;

			checkFileInput(inFile);
			std::getline(inFile, field1, ',');
			std::getline(inFile, field2, ',');
			std::getline(inFile, field3);

			//error message
			std::cout << "Error reading movie: " << type << ", " << field1 << ", "
				<< field2 << ", " << field3 << std::endl << std::endl;
		}
		else
		{
			newMovie->setData(inFile);
			movies.add(newMovie);
		}	
	}
}

void Manager::executeCommands()
{
	std::ifstream inFile;
	inFile.open("data4commands.txt");

	//check for valid input
	if(!inFile)
	{
		std::cout << "Failed to open commands file" << std::endl;
		return;
	}
	for(;;)
	{
		//check for valid input and end of file
		while (!isalnum(inFile.peek()))
		{
			if (inFile.peek() == EOF)
			{
				return;
			}
			inFile.get();
		}

		char type;
		inFile >> type;

		//identify which command to execute
		switch (type)
		{
		case 'I': displayInventory();
			break;
		case 'H': displayHistory(inFile);
			break;
		case 'B': borrowMovie(inFile);
			break;
		case 'R': returnMovie(inFile);
			break;
		default:
			handleInvalidCommand(inFile, type);
		}
	}
}

void Manager::displayInventory()
{
	std::cout << "Displaying Inventory: " << std::endl;
	char genres[] = { 'F', 'D', 'C' };
	int genreCount = 3;

	for (int j = 0; j < genreCount; j++) {
		for (int i = 0; i < movies.getSize(); i++)
		{
			if (movies.get(i)->getGenre() == genres[j]) {
				movies.get(i)->print();
			}
		}

		std::cout << std::endl << std::endl;
	}
}

void Manager::displayHistory(std::ifstream& input)
{
	checkFileInput(input);
	int custID;
	input >> custID;

	if (customers.find(custID))
	{
		customers.find(custID)->gethistory();
	}
}

void Manager::borrowMovie(std::ifstream& input)
{
	int custID;
	input >> custID;

	char medium;
	input >> medium;

	if(medium != 'D')
	{
		handleInvalidMedium(input);
	}
	else
	{
		char movieType;
		input >> movieType;

		//check which kind of movie to execute borrow command
		switch (movieType)
		{
		case 'F': borrowComedy(input, custID);
			break;
		case 'D': borrowDrama(input, custID);
			break;
		case 'C': borrowClassic(input, custID);
			break;
		default: handleInvalidType(input, custID);
		}
	}
}

void Manager::handleInvalidMedium(std::ifstream& input) const
{
	char type;
	std::string title;
	int year;

	//get file input
	input >> type;
	checkFileInput(input);
	getline(input, title, ',');
	input >> year;

	std::cout << "Invalid Medium (Command Failed): " << type << ", " << title
		<< ", " << year << std::endl << std::endl;
}

void Manager::handleInvalidType(std::ifstream& input, const int custID) const
{
	int month;
	int year;
	std::string name;

	//get file input
	input >> month;
	input >> year;
	checkFileInput(input);
	getline(input, name);

	std::cout << "Invalid Genre Type (Command Failed): ";
	std::cout << custID << ", "<<  month << " " 
	<< year << ", " << name << std::endl << std::endl;
}

void Manager::borrowClassic(std::ifstream& input, const int custID)
{
	int month;
	int year;
	std::string actor;

	//get file input
	input >> month;
	input >> year;
	checkFileInput(input);
	getline(input, actor);

	//Find specified Movie and specified Customer
	Movie * movie = movies.searchClassic(month, year, actor);
	Customer * customer = customers.find(custID);

	//if movie and customer are not NULL, both were found
	//in previous search
	if(movie && customer)
	{
		//if stock is available, execute borrow transaction
		if(movie->decrementStock())
		{
			customer->addTransaction('B');
			customer->addMovie(movie);
		}
		else
		{
			std::cout << "Insufficient Stock (Borrow Command Failed): " << std::endl;
			std::cout << "Customer ID: " << custID << std::endl;
			std::cout << "Movie: ";
			movie->print();
			std::cout << std::endl << std::endl;
		}	
	}
	else if(movie == NULL && customer != NULL)
	{
		std::cout << "Movie Not found (Borrow Command Failed): " << std::endl;
		std::cout << "Custmer ID: " << custID << std::endl;
		std::cout << "Movie: " << actor << ", " << month << " " << year 
		<< std::endl << std::endl;
	}
	else
	{
		std::cout << "Customer not found (Borrow Command Failed): " 
		<< std::endl;
		std::cout << "Customer ID: " << custID << std::endl;
		std::cout << "Movie: " << actor << ", " << month << " " << year 
		<< std::endl << std::endl;
	}
}

void Manager::borrowComedy(std::ifstream& input, const int custID)
{
	std::string title;
	int year;

	//get ile input
	checkFileInput(input);
	getline(input, title, ',');
	input >> year;

	//find specified Movie & specified Customer
	Movie * movie = movies.searchComedy(title, year);
	Customer * customer = customers.find(custID);

	//if movie and cusomer or not NULL, both were found
	//and command execution can poceed
	if (movie && customer)
	{
		//if stock is available, execute command
		if(movie->decrementStock())
		{
			customer->addTransaction('B');
			customer->addMovie(movie);
		}
		else
		{
			std::cout << "Insufficient Stock (Borrow Command Failed): " << std::endl;
			std::cout << "Customer ID: " << custID << std::endl;
			std::cout << "Movie: ";
			movie->print();
			std::cout << std::endl << std::endl;
		}
	}
	else if (movie == NULL && customer != NULL)
	{
		std::cout << "Movie Not found (Borrow Command Failed): " << std::endl;
		std::cout << "Custmer ID: " << custID << std::endl;
		std::cout << "Movie: " << title << ", " << year
			<< std::endl << std::endl;
	}
	else
	{
		std::cout << "Customer not found (Borrow Command Failed): "
			<< std::endl;
		std::cout << "Customer ID: " << custID << std::endl;
		std::cout << "Movie: " << title << ", " << year
			<< std::endl << std::endl;
	}
}

void Manager::borrowDrama(std::ifstream& input, const int custID)
{
	std::string director;
	std::string title;

	//get file input
	checkFileInput(input);
	getline(input, director, ',');
	checkFileInput(input);
	getline(input, title, ',');

	//search for specified Movie and specified Customer
	Movie * movie = movies.searchDrama(director, title);
	Customer * customer = customers.find(custID);

	//if movie and customer are bot not NULL, both were
	//found and execution can proceed
	if (movie && customer)
	{
		//check if stock is available
		if(movie->decrementStock())
		{
			customer->addTransaction('B');
			customer->addMovie(movie);
		}
		else
		{
			std::cout << "Insufficient Stock (Borrow Command Failed): " << std::endl;
			std::cout << "Customer ID: " << custID << std::endl;
			std::cout << "Movie: ";
			movie->print();
			std::cout << std::endl << std::endl;
		}
	}
	else if (movie == NULL && customer != NULL)
	{
		std::cout << "Movie Not found (Borrow Command Failed): " << std::endl;
		std::cout << "Custmer ID: " << custID << std::endl;
		std::cout << "Movie: " << title << ", " << director
			<< std::endl << std::endl;
	}
	else
	{
		std::cout << "Customer not found (Borrow Command Failed): "
			<< std::endl;
		std::cout << "Customer ID: " << custID << std::endl;
		std::cout << "Movie: " << title << ", " << director
			<< std::endl << std::endl;
	}
}

void Manager::returnMovie(std::ifstream& input)
{
	int custID;
	char medium;

	input >> custID;
	input >> medium;

	//check medium is valid
	if (medium != 'D')
	{
		handleInvalidMedium(input);
	}
	else
	{
		char movieType;
		input >> movieType;

		//identify which genre of movie to execute
		//return command on
		switch (movieType)
		{
		case 'F': returnComedy(input, custID);
			break;
		case 'D': returnDrama(input, custID);
			break;
		case 'C': returnClassic(input, custID);
			break;
		default: handleInvalidCommand(input, movieType);
		}
	}
}

void Manager::returnComedy(std::ifstream& input, const int custID)
{
	std::string title;
	int year;

	//get file input
	checkFileInput(input);
	getline(input, title, ',');
	input >> year;

	//find specified Movie and Customer
	Movie * movie = movies.searchComedy(title, year);
	Customer * customer = customers.find(custID);

	//if movie and customer are not NULL, both were
	//found and command execution can continue.
	if (movie && customer)
	{
		if (movie->incrementStock())
		{
			customer->addTransaction('R');
			customer->addMovie(movie);
		}
		else
		{
			std::cout << "Faild to execute return command: " << std::endl;
			std::cout << "Customer ID: " << custID << std::endl;
			std::cout << "Movie: ";
			movie->print();
			std::cout << std::endl << std::endl;
		}
	}
	else if (movie == NULL && customer != NULL)
	{
		std::cout << "Movie Not found (Return Command Failed): " << std::endl;
		std::cout << "Custmer ID: " << custID << std::endl;
		std::cout << "Movie: " << title << ", " << year
			<< std::endl << std::endl;
	}
	else
	{
		std::cout << "Customer not found (Return Command Failed): "
			<< std::endl;
		std::cout << "Customer ID: " << custID << std::endl;
		std::cout << "Movie: " << title << ", " << year
			<< std::endl << std::endl;
	}
}

void Manager::returnClassic(std::ifstream& input, const int custID)
{
	int month;
	int year;

	//get file input
	std::string actor;
	input >> month;
	input >> year;
	checkFileInput(input);
	getline(input, actor);

	//find specified Movie and Customer
	Movie * movie = movies.searchClassic(month, year, actor);
	Customer * customer = customers.find(custID);

	//if movie and customer are both not NULL, both were found
	//and command execution can continue
	if (movie && customer)
	{
		if (movie->incrementStock())
		{
			customer->addTransaction('R');
			customer->addMovie(movie);
		}
		else
		{
			std::cout << "Faild to execute return command: " << std::endl;
			std::cout << "Customer ID: " << custID << std::endl;
			std::cout << "Movie: ";
			movie->print();
			std::cout << std::endl << std::endl;
		}
	}
	else if (movie == NULL && customer != NULL)
	{
		std::cout << "Movie Not found (Return Command Failed): " << std::endl;
		std::cout << "Custmer ID: " << custID << std::endl;
		std::cout << "Movie: " << actor << ", " << month << " " << year
			<< std::endl << std::endl;
	}
	else
	{
		std::cout << "Customer not found (Return Command Failed): "
			<< std::endl;
		std::cout << "Customer ID: " << custID << std::endl;
		std::cout << "Movie: " << actor << ", " << month << " " << year
			<< std::endl << std::endl;
	}
}

void Manager::returnDrama(std::ifstream& input, const int custID)
{
	std::string director;
	std::string title;

	//get file input
	checkFileInput(input);
	getline(input, director, ',');
	checkFileInput(input);
	getline(input, title, ',');

	//find specified Movie and Customer
	Movie * movie = movies.searchDrama(director, title);
	Customer * customer = customers.find(custID);

	//if movie and customer are both not NULL, both were found
	//and command execution can continue
	if (movie && customer)
	{
		if (movie->incrementStock())
		{
			customer->addTransaction('R');
			customer->addMovie(movie);
		}
		else
		{
			std::cout << "Faild to execute return command: " << std::endl;
			std::cout << "Customer ID: " << custID << std::endl;
			std::cout << "Movie: ";
			movie->print();
			std::cout << std::endl << std::endl;
		}
	}
	else if (movie == NULL && customer != NULL)
	{
		std::cout << "Movie Not found (Return Command Failed): " << std::endl;
		std::cout << "Custmer ID: " << custID << std::endl;
		std::cout << "Movie: " << title << ", " << director
			<< std::endl << std::endl;
	}
	else
	{
		std::cout << "Customer not found (Return Command Failed): "
			<< std::endl;
		std::cout << "Customer ID: " << custID << std::endl;
		std::cout << "Movie: " << title << ", " << director
			<< std::endl << std::endl;
	}
}

void Manager::handleInvalidCommand(std::ifstream& input, const char type) const
{
	//checkFileInput(input);
	if(type == 'Z')
	{
		int custID;
		char medium;
		char genre;
		int month;
		int year;
		std::string name;

		//get file input
		checkFileInput(input);
		input >> custID;
		input >> medium;
		input >> genre;
		input >> month;
		input >> year;
		checkFileInput(input);
		getline(input, name);

		//output error 
		std::cout << "Invalid Transaction Command: " << type << std::endl;
			std::cout << custID << ", " << medium << ", " << genre
			<< ", " << month << " " << year << ", " << name 
		<< std::endl << std::endl;
	}
	else
	{
		//output error
		std::cout << "Invalid Transaction Command: " << type 
		<< std::endl << std::endl;
	}
	//clear buffer for next command input
	checkFileInput(input);
}


