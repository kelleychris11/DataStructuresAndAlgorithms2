#ifndef POLY_H
#define POLY_H
#include <iostream>

////////////////////////////////////////////////////////////////////
// File:			poly.h
// Author:			Chris Kelley
// Course:			CSS 343B
// Creation Date:	1/5/2018
// Last Update:		1/14/2018
// Project:			Assignment #1 - Polynomial Class
// Purpose:			The program purpose is to create a class that
//					contains, and acts as, a polynomial. Operatons 
//					may be performed on polynomial objects(+, -, *)
//					to create new polynomials. 
// Notes:			Each term in the polynomial must have a power
//					greater than zero. The underlying ADT is an
//					array, which grows dynamically as it is needed.
//////////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////
// Poly Class
//     ADT that holds a polynomial stored in
//	   an array. Polynomials may be updated.
//     Operations may be performed on multiple
//     polynomials.
//
//     Powers of terms in each polynomial must
//	   be greater than 0;
///////////////////////////////////////////////

const int DEFAULT_ARRAY_SIZE = 1;

class Poly
{
	friend std::ostream& operator << (std::ostream& output, const Poly& poly);
	friend std::istream& operator >> (std::istream& input, Poly& poly);

private:

	int * polyArray;
	int degree = 0;

	//Grow array size to accomodate new polynomial degree
	void growArray(const int newDegree);

public:

	//default constructor, contains 0x^0 polynomial
	Poly();

	//constructor defining Poly specified coefficient to
	//power of 0
	Poly(const int coefficient);

	//constructor defining Poly as specified coefficient to
	//specified power
	Poly(const int coefficient, const int power);
	
	Poly(const Poly& rhs);

	//virtual ~Poly();

	////////////////////////////////
	// Overloaded Operators
	////////////////////////////////

	//Poly operands
	Poly operator= (const Poly& rhs);
	Poly operator+ (const Poly& rhs) const;
	Poly operator-(const Poly& rhs) const;
	Poly operator*(const Poly& rhs)const;
	Poly& operator+=(const Poly& rhs);
	Poly& operator-=(const Poly& rhs);
	Poly& operator*=(const Poly& rhs);
	bool operator==(const Poly& rhs) const;
	bool operator!=(const Poly& rhs) const;

	//Poly and int operands
	Poly operator+ (const int rhs) const;
	Poly operator- (const int rhs) const;
	Poly operator* (const int rhs) const;
	Poly operator+= (const int rhs);
	Poly operator-= (const int rhs);
	Poly operator*= (const int rhs);

	//////////////////////////
	// Accessors
	/////////////////////////

	//get the coefficient of the specified power
	int getCoeff(const int power) const;

	/////////////////////////
	// Mutators
	/////////////////////////

	//set specified power to specified coefficient
	void setCoeff(const int coefficient, const int power);


};

#endif

