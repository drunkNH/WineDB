//Wine.cpp
#include "Wine.h"
#include <iostream>
#include <typeinfo>
#include <iomanip>

using namespace std;

/**
 * the defualt constructor that set price to 0
 */
Wine::Wine()
{
	price = 0;
}

/**
 * the consturctor that set the name of the class to parameter name,
 * set the vintage of the class to parameter vintage,
 * set the score of the class to parameter score,
 * set the price of the class to parameter price,
 * set the type of the class to parameter type.
 * @param name, vintage, score, price, type
 */
Wine::Wine(string name, int vintage, int score, double price, string type)
{
	this->name = name;
	this->vintage = vintage;
	this->score = score;
	this->price = price;
	this->type = type;
}

/**
 * the member function that set the name of the class to parameter name,
 * set the vintage of the class to parameter vintage,
 * set the score of the class to parameter score,
 * set the price of the class to parameter price,
 * set the type of the class to parameter type.
 * @param name, vintage, score, price, type
 */ 
void Wine::setInfo(string name, int vintage, int score, double price, string type)
{
	this->name = name;
	this->vintage = vintage;
	this->score = score;
	this->price = price;
	this->type = type;
}

/**
 * the member function that return name
 * @return name
 */
string Wine::getName() const
{
	return name;
}

/**
* the member function that return vintage
* @return vintage
*/ 
int Wine::getVintage() const
{
	return vintage;
}

/**
* the member function that return score
* @return score
*/ 	   
int Wine::getScore() const
{
	return score;
}

/**
 * the member function that return price
 * @return price
 */
double Wine::getPrice() const
{
	return price;
}

/**
* the member function that return type
* @return type
*/
string Wine::getType() const
{
	return type;
}
