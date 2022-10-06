//Wine.h
#ifndef WINE_H
#define WINE_H

#include <iostream>
#include <typeinfo>
#include <iomanip>

using namespace std;

/**
 * Defines the header information for the 
 * class object Wine with its data members and methods
 * @file - Wine.h
**/
class Wine
{
	private:
	/**
	 * private access variables with various data types that contains
	 * the information for a wine object
	 **/
	   string name;
	   int vintage;
	   int score;
	   double price;
	   string type;
	   
	public:
	/**
	 * the default constructor that set price to 0
	 */
	   Wine();
	/**
	 * the consturctor that set the name of the class to parameter name,
	 * set the vintage of the class to parameter vintage,
	 * set the score of the class to parameter score,
	 * set the price of the class to parameter price,
	 * set the type of the class to parameter type.
	 * @param name, vintage, score, price, type
	 */
	   Wine(string name, int vintage, int score, double price, string type);
	/**
	 * the member function that set the name of the class to parameter name,
	 * set the vintage of the class to parameter vintage,
	 * set the score of the class to parameter score,
	 * set the price of the class to parameter price,
	 * set the type of the class to parameter type.
	 * @param name, vintage, score, price, type
	 */
	   void setInfo(string name, int vintage, int score, double price, string type);
	   
	/**
	 * the member function that return name
	 * @return name
	 */ 
	   string getName() const;
	   
	/**
	 * the member function that return vintage
	 * @return vintage
	 */ 
	   int getVintage() const;
	   
	/**
	 * the member function that return score
	 * @return score
	 */ 
	   int getScore() const;
	   
	   /**
		 * the member function that return price
		 * @return price
		 */
	   double getPrice() const; 
	   
	   /**
		 * the member function that return type
		 * @return type
		 */
	   string getType() const; 
	   
};

#endif
