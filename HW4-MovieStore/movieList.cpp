#include "movieList.h"
#include <iterator>

//---------------------------------------------------------------
//File: movielist.cpp
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Conatins MovieList class which stores a list of Movie objects.
//-----------------------------------------------------------------

MovieList::~MovieList()
{
	for (int i = 0; i < movieList.size(); i++)
	{
		if (movieList[i] != NULL)
		{
			delete movieList[i];
		}
	}
}


void MovieList::add(Movie * movie)
{
	//insert movie sorted by uniqe key value based on
	//member attribute1 and attribute2
	std::vector<Movie*>::iterator ptr;
	//----------------------------------
	for(ptr = movieList.begin(); ptr < movieList.end(); ptr++)
	{
		if((*ptr)->getKey() > movie->getKey())
		{
			movieList.insert(ptr, movie);
			size++;
			return;
		}
	}
	movieList.push_back(movie);
	size++;
}

int MovieList::getSize() const
{
	return size;
}

Movie* MovieList::get(const int index)
{
	return movieList[index];
}

Movie * MovieList::search(std::string title) {
    for (int i = 0; i < movieList.size(); i++) {
        if (movieList[i]->getTitle() == title) {
            return movieList[i];
        }
    }
    return NULL;
}

Movie * MovieList::searchClassic(const int month, const int year, 
	const std::string actor)
{
	int asciiValue = 0;
	for (int i = 0; i < actor.size(); i++)
	{
		asciiValue += (int)actor[i];
	}

	asciiValue -= 13; //subtract newline value at end of line

	 // return the key to movies with classic genre
	int thisKey = ((month + year) % 23) * asciiValue; 

	for(int i = 0; i < size; i++)
	{
		if(movieList[i]->getGenre() == 'C')
		{
			if(thisKey == movieList[i]->getKey())
			{
				return movieList[i];	
			}
		}
	}
	//movie not found
	return NULL;
}

Movie * MovieList::searchComedy(const std::string title, const int year)
{
	//get key of movie to find
	char * stringArray = new char[title.length() + 1];
	strcpy(stringArray, title.c_str());
	int titleAscii = 0;
	for (int i = 0; i < title.size(); i++) {
		titleAscii = titleAscii + int(stringArray[i]);
	}

	// return the key to a movie with comedy genre
	int thisKey =  titleAscii * (year % 17); 

	delete[] stringArray;

	for(int i = 0; i < movieList.size(); i++)
	{
		if(movieList[i]->genre == 'F')
		{
			if(thisKey == movieList[i]->getKey())
			{
				return movieList[i];
			}
		}
	}
	//movie not found
	return NULL;
}

Movie * MovieList::searchDrama(const std::string director, 
	const std::string title)
{
	//get key of movie to find
	char * directorArray = new char[director.length() + 1];
	strcpy(directorArray, director.c_str());
	int directorAscii = 0;
	for (int i = 0; i < director.size(); i++) {
		directorAscii = directorAscii + int(directorArray[i]);
	}

	char * titleArray = new char[title.length() + 1];
	strcpy(titleArray, title.c_str());
	int titleAscii = 0;
	for (int i = 0; i < title.size(); i++) {
		titleAscii = titleAscii + int(titleArray[i]);
	}

	// return the key to a movie with drama genre
	int thisKey =  (directorAscii % 15) * (titleAscii % 17); 

	delete [] directorArray;
	delete[] titleArray;

	for(int i = 0; i < size; i++)
	{
		if(movieList[i]->genre == 'D')
		{
			if(thisKey == movieList[i]->getKey())
			{
				return movieList[i];
			}
		}
	}
	//movie not found
	return NULL;
}
