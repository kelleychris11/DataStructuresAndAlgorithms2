#include "movie.h"

//---------------------------------------------------------------
//File: movie.cpp
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Contains movie class. Used for storing information
//		on each specific movie.
//-----------------------------------------------------------------

//TODO add const to methods

//-------------------------------------------
//Movie instantiation
//-------------------------------------------

Movie::~Movie() {}

char Movie::getGenre() const
{
	return genre;
}

std::string Movie::getDirector() const
{
	return director;
}

std::string Movie::getTitle() const
{
	return title;
}

int Movie::getStock() const
{
	return stock;
}

bool Movie::incrementStock() {
	this->stock++;
	return true;
}

bool Movie::decrementStock() {
	if (this->stock == 0) {
		return false;
	}
	this->stock--;
	return true;
}

char Movie::getGenre()
{
	return genre;
}


//---------------------------------------
//Classic instantiation
//---------------------------------------
void Classic::setData(std::ifstream& input) {
	
	checkFileInput(input);
	input >> this->stock;

	checkFileInput(input);
	getline(input, this->director, ',');

	checkFileInput(input);
	getline(input, this->title, ',');

	std::string first;
	std::string second;
	checkFileInput(input);
	input >> first;
	checkFileInput(input);
	input >> second;
	actor = first + " " + second;

	input >> this->releaseMonth;
	input >> this->releaseYear;
}

int Classic::getReleaseMonth() const
{
	return releaseMonth;
}

int Classic::getReleaseYear() const
{
	return releaseYear;
}

std::string Classic::getActor() const
{
	return actor;
}

int Classic::getKey() 
{
	int asciiValue = 0;
	for (int i = 0; i < actor.size(); i++)
	{
		asciiValue += (int)actor[i];
	}
	return ((releaseMonth + releaseYear) % 23) * asciiValue;
}

void Classic::print() const
{
	std::cout << genre << ", " << stock << ", " << director << ", "
		<< title << ", " << actor << ", " << releaseMonth << ", "
		<< releaseYear << std::endl;
}

//---------------------------------------------
//Comedy instantiation
//---------------------------------------------
void Comedy::setData(std::ifstream& input) 
{

	checkFileInput(input);
	input >> this->stock;

	checkFileInput(input);
	getline(input, this->director, ',');

	checkFileInput(input);
	getline(input, this->title, ',');

	input >> this->releaseDate;
}

void Comedy::print() const
{
	std::cout << genre << ", " << stock << ", " << director << ", " 
	<< title << ", " << releaseDate << std::endl;
}

int Comedy::getKey() {
	char * stringArray = new char[title.length() + 1];
	strcpy(stringArray, title.c_str());
	int titleAscii = 0;
	for (int i = 0; i < title.size(); i++) {
		titleAscii = titleAscii + int(stringArray[i]);
	}
	delete[] stringArray;
	// return the key to a movie with comedy genre
	return titleAscii * (releaseDate % 17); 
}

int Comedy::getReleaseDate() const
{
	return releaseDate;
}

//----------------------------------------------
//Drama instantiation
//----------------------------------------------
void Drama::setData(std::ifstream& input) 
{

	checkFileInput(input);
	input >> this->stock;

	checkFileInput(input);
	getline(input, this->director, ',');

	checkFileInput(input);
	getline(input, this->title, ',');

	checkFileInput(input);
	input >> this->releaseDate;
}

void Drama::print() const
{
	std::cout << genre << ", " << stock << ", " << director << ", " 
	<< title << ", " << releaseDate << std::endl;
}

int Drama::getKey() 
{
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
	delete[] directorArray;
	delete[] titleArray;
	// return the key to a movie with drama genre
	return (directorAscii % 15) * (titleAscii % 17); 
}

int Drama::getReleaseDate() const
{
	return releaseDate;
}


//------------------------------------------------------
//MovieFactory initialization
//------------------------------------------------------
Movie * MovieFactory::createMovie(char type)
{
	switch (type)
	{
	case 'F': return new Comedy;
		break;
	case 'D': return new Drama;
		break;
	case 'C': return new Classic;
		break;
	default: return NULL;
	}
}
