#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>

//---------------------------------------------------------------
//File: movie.h
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Contains movie class. Used for storing information
//		on each specific movie.
//-----------------------------------------------------------------

//----------------------------------------
//Movie class
//Purpose: Represents a movie title. Contains
// information on a movie rental item (director,
// stock, release data, etc). 
//---------------------------------------------

class Movie
{
	friend class MovieList;
protected:
	char genre;
	int stock;
	std::string title;
	std::string director;

public:
	virtual ~Movie();

	//----------------------setData--------------------------
	//Reads file input and populates movie data fields
	virtual void setData(std::ifstream&) = 0;

	//----------------------getGenre-------------------------
	//Return movie genre
	char getGenre() const;

	//----------------------getStock--------------------------
	//Return movie stock
	int getStock() const;

	//----------------------incrementStock---------------------
	//Increase stock of movie by 1
	bool incrementStock();

	//----------------------decrementStock---------------------
	//Decrease stock of movie by 1
	bool decrementStock();

	//----------------------getDirector-----------------------
	//Return movie director
	std::string getDirector() const;

	//----------------------getTitle---------------------------
	//Return movie Title
	std::string getTitle() const;

	//----------------------getKey-----------------------------
	//Calcuate and return key for sorting
	virtual int getKey() = 0;
	
	//----------------------print------------------------------
	//Print movie data
	virtual void print() const = 0;

	//---------------------getGenre---------------------------
	//return movie genre
	char getGenre();
};

//--------------------------------------------
//Classic class
// Purpose: Child of Movie class. Represents
// more specifc movie type of the classic genre
//---------------------------------------------

class Classic : public Movie
{
private:
	int releaseMonth;
	int releaseYear;
	std::string actor;
public:

	//constructor
	Classic() { genre = 'C'; }

	//----------------------setData--------------------------
	//Reads file input and populates movie data fields
	void setData(std::ifstream& input);

	//----------------------getReleaseMonth------------------
	//Return movie release month
	int getReleaseMonth() const;

	//----------------------getReleaseYear-------------------
	//Return movie release year
	int getReleaseYear() const;

	//----------------------getActor------------------------
	//Return movie actor
	std::string getActor() const;

	//----------------------getKey-------------------------
	//Calculate and return key for sorting
	int getKey();

	//----------------------print---------------------------
	//Print movie data
	void print() const;
};

//-------------------------------------------------------
//Drama class
// Purpose: Child of Movie class. Represents more specific
// type of movie of the drama genre.
//--------------------------------------------------------
class Drama : public Movie
{
private:
	int releaseDate; // only the year
public:

	//constructor
	Drama() { genre = 'D'; }

	//----------------------setData--------------------------
	//Reads file input and populates movie data fields
	void setData(std::ifstream& input);

	//----------------------print---------------------------
	//Print movie data
	void print() const;

	//----------------------getKey--------------------------
	//Calculate and return key for sorting
	int getKey();

	//----------------------getReleaseDate------------------
	//Return movie release year
	int getReleaseDate() const;
};

//----------------------------------------------------------
//Comedy class
// Purpose: Child of Movie class. Represents more specific 
// type of movie of the comedy genre.
//--------------------------------------------------------

class Comedy : public Movie
{
private:
	int releaseDate; // only the year

public:

	//constructor
	Comedy() { genre = 'F'; }

	//----------------------setData--------------------------
	//Reads file input and populates movie data fields
	void setData(std::ifstream& input);

	//----------------------print----------------------------
	//Print movie data
	void print() const;

	//----------------------getKey----------------------------
	//Calculate and return key for sorting
	int getKey();
	
	//----------------------getReleaseDate-------------------
	//Return movie release year
	int getReleaseDate() const;
};

//-----------------------------------------------------------
//MovieFactory class
// Purpose: Allows dynamic binding of a movie object to a 
// child class depending on the input genre of the movie
//-----------------------------------------------------------
class MovieFactory
{
public:

	//default constructor
	MovieFactory() {}

	//---------------------createMovie----------------------
	//Determines class instantiation based on provided type.
	// Returned object is pointer to child of movie determined
	// at runtime.
	static Movie * createMovie(const char type);
};

//-------------------------checkFileInput-----------------------
//Removes non-alphanumeric file input from provided file stream.
inline void checkFileInput(std::ifstream& input)
{
	while (!isalnum(input.peek()))
	{
		input.get();
	}
}
#endif