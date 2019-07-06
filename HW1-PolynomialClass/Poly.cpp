#include "poly.h"
using namespace std;

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

//default constructor sets value to 0x^0
Poly::Poly()
{
	polyArray = new int[DEFAULT_ARRAY_SIZE];
	polyArray[0] = 0;
	degree = 0;
}

//constructor sets value to (coefficient(x)^0)
Poly::Poly(const int coefficient)
{
	polyArray = new int[DEFAULT_ARRAY_SIZE];
	polyArray[0] = coefficient;
	degree = 0;
}

//constructor sets value to (coefficient(x)^power)
Poly::Poly(const int coefficient, const int power)
{
	polyArray = new int[power + 1];

	//initialize all values in array to zero
	for(int i = 0; i <= power; i++)
	{
		polyArray[i] = 0;
	}
	polyArray[power] = coefficient;
	degree = power;
}

//copy constructor
Poly::Poly(const Poly& rhs)
{
	//check if both Poly operands are the
	//same object
	if(this == &rhs)
	{
		return;
	}

	polyArray = new int[rhs.degree + 1];
	for (int i = 0; i <= rhs.degree; i++)
	{
		setCoeff(rhs.getCoeff(i), i);
	}
	degree = rhs.degree;
}

////destructor
//Poly::~Poly()
//{
//	delete[] polyArray;
//}

//////////////////////////////////
// Overloaded Operators
//////////////////////////////////

Poly Poly::operator= (const Poly& rhs)
{
	if(this == &rhs)
	{
		return *this;
	}

	polyArray = new int[rhs.degree + 1];

	for (int i = 0; i <= rhs.degree; i++)
	{
		setCoeff(rhs.getCoeff(i), i);
	}

	degree = rhs.degree;
	return *this;
}

Poly Poly::operator+ (const Poly& rhs) const
{
	int higherDegree = 0;
	int lowerDegree = 0;
	bool rhsDegreeIsHigher = false;

	//find which Poly has the highest degree
	if(degree > rhs.degree)
	{
		higherDegree = degree;
		lowerDegree = rhs.degree;
	}
	else
	{
		higherDegree = rhs.degree;
		lowerDegree = degree;
		rhsDegreeIsHigher = true;
	}

	Poly * polySum = new Poly(0, higherDegree);

	for(int i = 0; i <= lowerDegree; i++)
	{
		polySum->polyArray[i] = polyArray[i] + rhs.polyArray[i];
	}

	//if the degrees of the lhs and rhs values are not equal
	//then the x values in the array, (where: (lowerDegree < x <= higherDegree))
	//will only use the poly with the higher degree
	if(lowerDegree != higherDegree)
	{
		for(int i = lowerDegree + 1; i <= higherDegree; i++)
		{
			if(rhsDegreeIsHigher)
			{
				polySum->polyArray[i] = rhs.polyArray[i];
			}
			else
			{
				polySum->polyArray[i] = polyArray[i];
			}
		}
	}
	return *polySum;
}

Poly Poly::operator- (const Poly& rhs) const
{
	int higherDegree = 0;
	int lowerDegree = 0;
	bool rhsDegreeIsHigher = false;

	//find which Poly has the highest degree
	if (degree > rhs.degree)
	{
		higherDegree = degree;
		lowerDegree = rhs.degree;
	}
	else
	{
		higherDegree = rhs.degree;
		lowerDegree = degree;
		rhsDegreeIsHigher = true;
	}

	Poly * polySum = new Poly(0, higherDegree);

	for (int i = 0; i <= lowerDegree; i++)
	{
		polySum->polyArray[i] = polyArray[i] - rhs.polyArray[i];
	}

	//if the degrees of the lhs and rhs values are not equal
	//then the x values in the array, (where: (lowerDegree < x <= higherDegree))
	//will only use the poly with the higher degree
	if (lowerDegree != higherDegree)
	{
		for (int i = lowerDegree + 1; i <= higherDegree; i++)
		{
			if (rhsDegreeIsHigher)
			{
				polySum->polyArray[i] = rhs.polyArray[i] * -1;
			}
			else
			{
				polySum->polyArray[i] = polyArray[i];
			}
		}
	}
	return *polySum;
}

Poly Poly::operator* (const Poly& rhs) const
{
	int newDegree = degree + rhs.degree;
	
	Poly * productPoly = new Poly(0, newDegree);

	//multiply each non-zero value in rhs by each non-zero value
	//in lhs
	for(int i = 0; i <= degree; i++)
	{
		if(polyArray[i] != 0)
		{
			for(int j = 0; j <= rhs.degree; j++)
			{
				if(rhs.polyArray[j] != 0)
				{
					productPoly->polyArray[i + j] += polyArray[i] * rhs.polyArray[j];
				}
			}
		}
	}
	return *productPoly;
}

Poly& Poly::operator+= (const Poly& rhs)
{
	int higherDegree = 0;
	int lowerDegree = 0;
	bool rhsDegreeIsHigher = false;

	//find which Poly has the highest degree
	if (degree > rhs.degree)
	{
		higherDegree = degree;
		lowerDegree = rhs.degree;
	}
	else
	{
		higherDegree = rhs.degree;
		lowerDegree = degree;
		rhsDegreeIsHigher = true;
		growArray(rhs.degree);
	}

	for (int i = 0; i <= lowerDegree; i++)
	{
		polyArray[i] += rhs.polyArray[i];
	}

	//if the degrees of the lhs and rhs values are not equal
	//then the x values in the array, (where: (lowerDegree < x <= higherDegree))
	//will only use the poly with the higher degree
	if (lowerDegree != higherDegree)
	{
		for (int i = lowerDegree + 1; i <= higherDegree; i++)
		{
			if (rhsDegreeIsHigher)
			{
				polyArray[i] = rhs.polyArray[i];
			}
		}
	}
	return *this;
}

Poly& Poly::operator-= (const Poly& rhs)
{
	int higherDegree = 0;
	int lowerDegree = 0;
	bool rhsDegreeIsHigher = false;

	//find which Poly has the highest degree
	if (degree > rhs.degree)
	{
		higherDegree = degree;
		lowerDegree = rhs.degree;
	}
	else
	{
		higherDegree = rhs.degree;
		lowerDegree = degree;
		rhsDegreeIsHigher = true;
		growArray(rhs.degree);
	}

	for (int i = 0; i <= lowerDegree; i++)
	{
		polyArray[i] -= rhs.polyArray[i];
	}

	//if the degrees of the lhs and rhs values are not equal
	//then the x values in the array, (where: (lowerDegree < x <= higherDegree))
	//will only use the poly with the higher degree
	if (lowerDegree != higherDegree)
	{
		for (int i = lowerDegree + 1; i <= higherDegree; i++)
		{
			if (rhsDegreeIsHigher)
			{
				polyArray[i] = -rhs.polyArray[i];
			}
		}
	}
	return *this;
}

Poly& Poly::operator *= (const Poly& rhs)
{
	int newDegree = degree + rhs.degree;
	int * tempArray = new int[newDegree + 1];

	//initialize tempArray to zero
	for(int i = 0; i <= newDegree; i++)
	{
		tempArray[i] = 0;
	}

	if(newDegree > degree)
	{
		growArray(newDegree);
	}

	//multiply each non-zero value in rhs by each non-zero value
	//in lhs
	for (int i = 0; i <= degree; i++)
	{
		if (polyArray[i] != 0)
		{
			for (int j = 0; j <= rhs.degree; j++)
			{
				if (rhs.polyArray[j] != 0)
				{
					tempArray[i + j] += polyArray[i] * rhs.polyArray[j];
				}
			}
		}
	}
	for(int i = 0; i <= newDegree; i++)
	{
		polyArray[i] = tempArray[i];
	}

	return *this;
}

bool Poly::operator== (const Poly& rhs) const
{
	bool isEqual = true;

	if(degree != rhs.degree)
	{
		isEqual = false;
	}

	if(isEqual)
	{
		for(int i = 0; i <= degree; i++)
		{
			if(polyArray[i] != rhs.polyArray[i])
			{
				isEqual = false;
			}
		}
	}
	return isEqual;
}

bool Poly::operator!= (const Poly& rhs) const
{
	return !(*this == rhs);
}

Poly Poly::operator+ (const int rhs) const
{
	Poly  newPoly = *this;
	newPoly.polyArray[0] += rhs;
	return newPoly;
}

Poly Poly::operator- (const int rhs) const
{
	Poly  newPoly = *this;
	newPoly.polyArray[0] -= rhs;
	return newPoly;
}

Poly Poly::operator* (const int rhs) const
{
	Poly newPoly = *this;
	for(int i = 0; i <= degree; i++)
	{
		if(newPoly.polyArray[i] != 0)
		{
			newPoly.polyArray[i] *= rhs;
		}
	}
	return newPoly;
}

Poly Poly::operator+= (const int rhs)
{
	polyArray[0] += rhs;
	return *this;
}

Poly Poly::operator-= (const int rhs)
{
	polyArray[0] -= rhs;
	return *this;
}
Poly Poly::operator*= (const int rhs)
{
	for(int i = 0; i <= degree; i++)
	{
		polyArray[i] *= rhs;
	}
	return *this;
}

int Poly::getCoeff(const int power) const
{
	if(power > degree || power < 0)
	{
		return 0;
	}
	return polyArray[power];
}

void Poly::setCoeff(const int coefficient, const int power)
{
	if(power < 0)
	{
		return;
	}

	if(power > degree)
	{
		growArray(power);
	}

	polyArray[power] = coefficient;
}

void Poly::growArray(const int newDegree)
{
	
	int * newArray = new int[newDegree + 1];

	//put values into new array
	for(int i = 0; i <= degree; i++)
	{
		newArray[i] = polyArray[i];
	}

	//intitialize remaining items to zero
	for(int i = degree + 1; i <= newDegree; i++)
	{
		newArray[i] = 0;
	}
	//delete polyArray;

	degree = newDegree;
	polyArray = newArray;
}

std::ostream & operator<<(std::ostream & output, const Poly & poly)
{
	bool zeroPoly = true;
	for (int i = poly.degree; i >=0; i--)
	{
		//check that coefficient is not zero
		if(poly.polyArray[i] != 0)
		{
			//the polynomial is not == 0
			zeroPoly = false;
			//check for power of zero
			if (i == 0)
			{
				//if coefficient of i is positive
				if (poly.polyArray[i] > 0)
				{
					output << " +" << poly.polyArray[i];
				}
				//if coefficient of i is negative
				else
				{
					output << " " << poly.polyArray[i];
				}
			}
			//check for power of 1
			//TODO may want to update so output is x^4 instead of 1x^4
			else if(i == 1)
			{
				//if coefficient of i is positive
				if(poly.polyArray[i] > 0)
				{
					output << " +" << poly.polyArray[i] << "x";
				}
				//if coefficient of i is negative
				else
				{
					output << " " << poly.polyArray[i] << "x";
				}
			}
			//for all other cases where power is not 0 or 1 and 
			//coefficient is not zero
			else
			{
				//if coefficient i is positive
				if(poly.polyArray[i] > 0)
				{
					output << " +" << poly.polyArray[i] << "x^" << i;
				}
				//if coefficient i is negative
				else
				{
					output << " " << poly.polyArray[i] << "x^" << i;
				}
			}
		}
	}
	//if there were no non-zero coefficients found, polynomial == 0
	if (zeroPoly)
	{
		output << 0;
	}
	return output;
}

std::istream & operator>>(std::istream & input, Poly & poly)
{
	int count = 0;
	int coefficient;
	int power;

	input >> coefficient;
	input >> power;

	do
	{
		if(power == -1)
		{
			break;
		}	
		poly.setCoeff(coefficient, power);
		input >> coefficient;
		input >> power;
	} while (power != -1);

	//////do 
	//////{
	//////	poly.setCoeff(coefficient, power);
	//////	input >> coefficient;
	//////	input >> power;

	//////} while (power != -1);

	//clear buffer
	input.clear();
	return input;
}

