#include "manager.h"

//---------------------------------------------------------------
//File: main.cpp
//Authors: Chris Kelley & Aditya Jonany
//Created: 3/9/2018
//Last Modified: 3/14/2018
//Purpose: Main method for program
//-----------------------------------------------------------------

int main()
{
	Manager movieManager;
	movieManager.buildCustomerList();
	movieManager.buildMovieList();
	movieManager.executeCommands();
}