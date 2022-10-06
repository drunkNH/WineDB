//wineOperations.cpp
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "dbconnect.h"
#include "wineOperations.h"
#include "Wine.h"
#include <string.h>
#include <climits>
#include <string>

using namespace std;

/**
   * @Purpose - Prints out the wine header at the start of each wineInfo output
   * @param - none     
   * @return - none 
   * @author Jeffrey Gu 
**/
void printWineHeader()
{
    cout << "   " << setw(32) << left << "Wine Name"
    << setw(9) << "Vintage"
	<< setw(9) << "Rating"
	<< setw(8) << "Price"
	<< setw(3) << " " << "Type" << endl;
	
	cout << "   " << setw(32) << left << "---------"
    << setw(9) << "-------"
	<< setw(9) << "------"
	<< setw(8) << "-----"
	<< setw(3) << " " << "----" << endl;
}

/**
   * @Purpose - Prints out the contained wine information from the result 
   * of the mysql query statement that was used.
   * @param *res - the stored wine information result to be displayed     
   * @return - none 
   * @author Jeffrey Gu 
**/
void printWineInfo(MYSQL_RES *res)
{
	MYSQL_ROW row; // the results row (line by line)
	int count = 0; //counts total amount of wine
	double price = 0; //the price of all wine combined in the table
	int score = 0; //the score of all wine combined in the table
	int redWine = 0; //counts total amount of red wine
	int redScore = 0; //the score of all red wine combined in the table
	double redPrice = 0; //the price of all red wine combined in the table
	int whiteWine = 0; //counts total amount of white wine
	int whiteScore = 0; //the score of all white wine combined in the table
	double whitePrice = 0; //the price of all white wine combined in the table
		
	printWineHeader(); //prints wineHeader 
		
	//prints out the result of the SQL query.
	while ((row = mysql_fetch_row(res)) !=NULL) 
	{
		count++; //increase wine count everytime a wine is printed
		score += stod(row[2]); //add score of current wine to the combined total of all wine scores
		price += stod(row[3]); //add price of current wine to the combined total of all wine prices
		string type = row[4]; //reads the type of the current wine
		if (type == "Red " || type == "Red") //if wine type is Red
		{
			redWine++; //increase red wine count everytime a red wine is printed
			redScore += stod(row[2]); //add score of current red wine to the combined total of all red wine scores
			redPrice += stod(row[3]); //add price of current red wine to the combined total of all red wine prices
		}
		if (type == "White " || type == "White") //if wine type is White
		{
			whiteWine++; //increase white wine count everytime a white wine is printed
			whiteScore += stod(row[2]); //add score of current white wine to the combined total of all white wine scores
			whitePrice += stod(row[3]); //add price of current white wine to the combined total of all white wine prices
		}
		
		//prints out the current wine row.
		cout << "   " << setw(32) << left << row[0]  << " " // coulumn (field) #1 - Wine Name
		<< setw(8) << row[1] << "  " // field #2 - Vintage
		<< setw(6) << row[2] << "  " // field #3 - Rating/Score
		<< setw(8)	<< row[3] << "  " // field #4 - Price
		<< setw(8)	 << row[4] << "  " // field #5 - Wine type
		<< endl; 
	}
	
	//prints the total amount of wine, average price and score of all wine
	cout <<"\n________________________________________________\n"<<endl;
	cout <<"Number of wines: "<<count<<"    Average price: $"
	<< fixed << setprecision(2) << price/count << "    Average score/rating: " << score/count << endl;
	
	//If there is only red wines that was printed
	if (redWine != 0 && whiteWine == 0)
	{
		//prints the total amount of wine, average price and score of red wine, sets white wine averages to all 0's
		cout <<"Number of Red wines: "<<redWine<<"    Average Red wines price: $"
		<< fixed << setprecision(2) << redPrice/redWine << "    Average Red wine score/rating: " << redScore/redWine << endl;
		cout <<"Number of White wines: "<< "0" <<"    Average White wines price: $"
		<< fixed << setprecision(2) << "0" << "    Average White wine score/rating: " << "0" << endl;
	}
	
	//If there is only white wines that was printed
	else if (whiteWine != 0 && redWine == 0)
	{
		//prints the total amount of wine, average price and score of white wine, sets red wine averages to all 0's
		cout <<"Number of Red wines: "<<"0"<<"    Average Red wines price: $"
		<< fixed << setprecision(2) << "0" << "    Average Red wine score/rating: " << "0" << endl;
		cout <<"Number of White wines: "<<whiteWine<<"    Average White wines price: $"
		<< fixed << setprecision(2) << whitePrice/whiteWine << "    Average White wine score/rating: " << whiteScore/whiteWine << endl;
	}
	
	//If both red and white wines were printed
	else if (whiteWine != 0 && redWine != 0)
	{
		//prints the total amount of wine, average price and score of red wine and white wine.
		cout <<"Number of Red wines: "<<redWine<<"    Average Red wines price: $"
		<< fixed << setprecision(2) << redPrice/redWine << "    Average Red wine score/rating: " << redScore/redWine << endl;
		cout <<"Number of White wines: "<<whiteWine<<"    Average White wines price: $"
		<< fixed << setprecision(2) << whitePrice/whiteWine << "    Average White wine score/rating: " << whiteScore/whiteWine << endl;
	}
	cout <<"________________________________________________\n" << endl << endl;
}

/**
   * @Purpose - Reads user input on what two scores they want to use
   * to display wine in the range of the two input scores, and uses the
   * user input scores in a SQL statement to be used in a MySQL query.
   * @param - none   
   * @return scoreBetweenStatement - statement that will be used in a SQL query to find wine in score range
   * @author Jeffrey Gu 
**/
string scoreBetween()
{
	int x, y = 0; //initialize first and second score to 0
	cout << "Enter the first score you want to use between 0-100: ";
	cin >> x; //User sets first score
	//Validation for first score, can not be invalid input or outside range of 1-100
	while (cin.fail() || x < 1 || x > 100) 
	{
		cin.clear();
		cin.ignore(10000, '\n');
		if (x < 1 || x > 100) //Determines which error message to display
			{cout << "Error: Please enter a score between 1-100" << endl;}
		else
			{cout << "Error: Please enter a valid option" << endl;}
		cin >> x;
	}
	
	cout << "Enter the second score you want to use between 0-100: ";
	cin >> y; //User sets second score
	//Validation for second score, can not be invalid input or outside range of 1-100
	while (cin.fail() || y < 1 || y > 100)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		if (y < 1 || y > 100) //Determines which error message to display
			{cout << "Error: Please enter a score between 1-100" << endl;}
		else
			{cout << "Error: Please enter a valid option" << endl;}
		cin >> y;
	}
	/*
	 * Sets the SQL statement used for the query, ensures that if
	 * the second score is greater than the first score that the program
	 * will readjust so that the SQL statement is from lower score to 
	 * higher score. Returns the SQL statement afterwards.
	 */ 
	string scoreBetweenStatement;
	if (x < y)
		{scoreBetweenStatement = "Select * from wineInfo where score >= "+ to_string(x) +" and score <= " + to_string(y) + " order by score";}
	else
		{scoreBetweenStatement = "Select * from wineInfo where score >= "+ to_string(y) +" and score <= " + to_string(x) + " order by score";}
	return scoreBetweenStatement;
}

/**
   * @Purpose - Reads user input on what two prices they want to use
   * to display wine in the range of the two input prices, and uses the
   * user input scores in a SQL statement to be used in a MySQL query.
   * @param - none   
   * @return priceBetweenStatement - statement that will be used in a SQL query to find wine in price range
   * @author Jeffrey Gu 
**/
string priceBetween()
{
	int x, y = 0; //initialize first and second price to 0
	cout << "Enter the first price you want to use: ";
	cin >> x;  //User sets first price
	//Validation for first price, can not be invalid input or a negative price
	while (cin.fail() || x < 0)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		if (x < 0) //Determines which error message to display
			{cout << "Error: Please enter a positive price" << endl;}
		else
			{cout << "Error: Please enter a valid option" << endl;}
		cin >> x;
	}
	cout << "Enter the second price you want to use: ";
	cin >> y; //User sets second price
	//Validation for second price, can not be invalid input or a negative price
	while (cin.fail() || y < 0)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		if (y < 0) //Determines which error message to display
			{cout << "Error: Please enter a positive price" << endl;}
		else
			{cout << "Error: Please enter a valid option" << endl;}
		cin >> y;
	}
	
	/*
	 * Sets the SQL statement used for the query, ensures that if
	 * the second price is greater than the first price that the program
	 * will readjust so that the SQL statement is from lower price to 
	 * higher price. Returns the SQL statement afterwards.
	 */ 
	string priceBetweenStatement;
	if (x < y)
		{priceBetweenStatement = "Select * from wineInfo where price >= "+ to_string(x) +" and price <= " + to_string(y)+ " order by price desc";}
	else
		{priceBetweenStatement = "Select * from wineInfo where price >= "+ to_string(y) +" and price <= " + to_string(x) + " order by price desc";}
	return priceBetweenStatement;
}

/**
   * @Purpose - Returns a SQL statement used to display the top 10 
   * wine based on price for a MySQL query.
   * @param - none   
   * @return topTenStatement - statement that will be used in a SQL query to display top 10 wine
   * @author Jeffrey Gu 
**/
string topTen()
{
	//sets SQL statement to find top 10 wine ordered by price and returns it
	string topTenStatement = "Select * from wineInfo order by price desc limit 10";
	return topTenStatement;
}

/**
   * @Purpose - Collects user data for a new wine object, collecting 
   * name of the wine, vintage, score, price, and type so that it may
   * be inserted into the wine database.
   * @param - none   
   * @return createdWine - New wine that the user has created
   * @author Jeffrey Gu 
**/
Wine newWine()
{
	//Initialize variables used for a new wine object
	string name, type;
	int vintage, score = 0;
	double price = 0;
	
	cout << "Enter Wine name: ";
	cin.ignore();
	getline(cin, name); //User enters a new Wine name
	
	cout << "Enter Vintage: ";
	cin >> vintage; //User enters a new vintage
	while (cin.fail() || vintage < 1900) //validation for vintage, can not be invalid input or older than 1900
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error: Please enter a valid vintage" << endl;
		cin >> vintage;
	}
	
	cout << "Enter Rating/Score between 1-100: ";
	cin >> score; //User enters new score
	//Validation for score, can not be invalid input or out of range of 1-100
	while (cin.fail() || score < 1 || score > 100) 
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error: Please enter a valid input score between 1-100" << endl;
		cin >> score;
	}
	
	cout << "Enter Price: ";
	cin >> price; //User enters new price
	//Validation for price, can not be invalid input or a negative price
	while (cin.fail() || price < 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		if (price < 0) //Determines which error message to display
			{cout << "Error: Please enter a positive price" << endl;}
		else
			{cout << "Error: Please enter a valid option" << endl;}
		cin >> price;
	}
	
	cout << "Enter type (Red/White): ";
	cin >> type; //User enters type of wine
	//Validation for type, user must enter either red or white
	while (type != "Red" && type != "White" && type != "red" && type != "white")
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error: Please enter a valid type (Red/White)" << endl;
		cin >> type;
	}
	
	/* 
	 * If user had entered a lowercase first character for either red or white,
	 * changes the first character to uppercase
	 */ 
	if (type == "red")
		{type = "Red";}
	else if (type == "white")
		{type = "White";}
	
	//creates new wine object based on user inputs and returns the new wine object
	Wine createdWine(name, vintage, score, price, type);
	return createdWine;
}

/**
   * @Purpose - Returns a SQL statement that inserts a new wine into
   * the database based on the new wine data the user inputs for the
   * SQL query.
   * @param userWine - the wine the user wants to insert to the database   
   * @return insertStatement - statement that will be used in a SQL query to insert a new wine based on the used data
   * @author Jeffrey Gu 
**/
string insertWine(Wine userWine)
{
	/*
	 * uses the created userWine in a modified SQL statement that inserts
	 * a new wine to the database based on the information in userWine.
	 * Returns the insertStatement to be used in a SQL query
	*/
	string insertStatement = "Insert into wineInfo Values ('"
							 +userWine.getName()+"', "+to_string(userWine.getVintage())+", "
							 +to_string(userWine.getScore())+", "+to_string(userWine.getPrice())+", '"
							 +userWine.getType()+"', NULL)";
	return insertStatement;
}

/**
   * @Purpose - Collects user data for a wine they like to update, requring
   * name to search the wine they wish to update and the price to update
   * the price of the searched wine.
   * @param - none   
   * @return createdWine - Wine that contains the information to search and update the price of the wine.
   * @author Jeffrey Gu 
**/
Wine updateWineInfo()
{
	//Initialize variables to be stored in a wine object
	string name;
	double price = 0;
	
	cout << "Enter Wine name: ";
	cin.ignore();
	getline(cin, name); //User enters the wine they wish to update
	
	cout << "Enter update price: ";
	cin >> price; //User enters the new price to be updated
	//Validation for price, can not be invalid input or a negative price
	while (cin.fail() || price < 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		if (price < 0) //Determines which error message to print to the user
			{cout << "Error: Please enter a positive price" << endl;}
		else
			{cout << "Error: Please enter a valid option" << endl;}
		cin >> price;
	}
	
	/*
	 * Creates a wine object based on user input, assigns blank information
	 * to the other variables in the wine class as they are not needed
	 * returns the wine object to be used in SQL statements
	 */
	Wine createdWine(name, 0, 0, price, "N/A");
	return createdWine;
}

/**
   * @Purpose - Returns a SQL statement that updates an existing wine price
   * to a new price in the database. Uses the existing name to search
   * the existing wine.
   * @param wineToUpdate - the wine the user wants to update for t he database   
   * @return insertStatement - statement that will be used in a SQL query to update an existing wine's price based on the name
   * @author Jeffrey Gu 
**/
string updateWine(Wine wineToUpdate)
{
	/*
	 * uses the created wineToUpdate in a modified SQL statement that updates
	 * an existing wine's price in the database based on the name variable in wineToUpdate;
	 * Returns the updateStatement to be used in a SQL query
	*/
	string updateStatement = "Update wineInfo set price = "+to_string(wineToUpdate.getPrice())+" where name like '%" + wineToUpdate.getName() + "%'";
	return updateStatement;
}
