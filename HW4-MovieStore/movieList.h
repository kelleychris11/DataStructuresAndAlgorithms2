#ifndef MOVIELIST_H
#define MOVIELIST_H
#include <vector>
#include "movie.h"
#include <string>

//---------------------------------------------------------------
//File: movielist.h
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Conatins MovieList class which stores a list of Movie objects.
//-----------------------------------------------------------------

//------------------------------------------------------
//MovieList class
//Purpose: Stores list of Movie objects
//------------------------------------------------------
class MovieList
{
private:
	//List of movie objecs
	std::vector<Movie*> movieList;

	//count of Movie items
	int size; 
public:

	//default constructor
	MovieList() { size = 0; }

	//destructor
	~MovieList();

	//---------------------------add-----------------------
	//Add movie to vector in sorted manner
	void add(Movie* movie);

	//---------------------------get-----------------------
	//Retrieve movie in vector for specified index
	Movie * get(const int index);

	//--------------------------getSize------------------
	//Return size of vector
	int getSize() const;

	//-------------------search------------------------------
	//Search for a movie based on the movies title.
	//Return movie pointer if found, NULL if not found
    Movie * search(const std::string title);

	//-------------------searchClassic---------------------------
	//Search for a specific classic movie based on specified month,
	//year, and actor. Return movie pointer if found, NULL if not found
	Movie * searchClassic(const int month, const int year, const std::string actor);

	//-------------------searchComedy----------------------------
	//Search for a specific comedy movie based on specified title &
	//release year. Return movie pointer if found, NULL if not found
	Movie * searchComedy(const std::string title, const int year);

	//-------------------seachDrama-------------------------------
	//search for a specific drama movie based on specific director &
	//title. Return movie pointer if found, NULL if not found
	Movie * searchDrama(const std::string director, const std::string title);
};
#endif

