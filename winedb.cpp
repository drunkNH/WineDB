//winedb.cpp
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "dbconnect.h"
#include "wineOperations.h"
#include "Wine.h"
#include "print_me_first.h"
#include <string.h>
#include <climits>
#include <string>

using namespace std;
 
/**
 * @Name - main
 * @Purpose - The purpose of this lab is to learn about using databases,
 * more specifically the MySQL database service. Databases are applicable 
 * for many situations that involve storing and retrieving data, such as 
 * a database of cars, food, and employees at a company, keeping information
 * organized and being very accessible. MySQL is used specifically as 
 * it’s a free open source database service that can handle larger 
 * databases with optimal performance. In this program, the user will 
 * have a menu of choices that’ll allow the user to display all wine within 
 * a certain score range in the database based on user inputs, display 
 * all wine within a certain price range in the database based on user 
 * inputs, display the top 10 wines in the database in terms of price 
 * starting from highest price to lowest, being able to insert a completely 
 * new wine in the database based on user input, and being able to 
 * update an existing wine’s price in the database based on the name of 
 * the wine chosen. User inputs will be validated to ensure that the user 
 * does not input an invalid input e.g. inputting -56 as a price or 
 * “five hundred” as a score.
 * @param - none
 * @return 0 - terminates program
 * @author - Jeffrey Gu
 **/
int main()
{
  MYSQL *conn;		// the connection
  MYSQL_RES *res;	// the results
  MYSQL_ROW row;	// the results row (line by line)
  struct connection_details mysqlD;
  mysqlD.server = (char *)"localhost";  // where the mysql database is
  mysqlD.user = (char *)"root";		// the root user of mysql	
  mysqlD.password = (char *)"password"; // the password of the root user in mysql
  mysqlD.database = (char *)"mysql";	// the databse to pick
 
  // connect to the mysql database
  conn = mysql_connection_setup(mysqlD);
  
  // use wine database
  res = mysql_perform_query(conn, (char *)"use wine");
  
  //While loop that shows a menu and enters functions based on user choice. while loop will end if user enters 6.
  int selection = 0;
  while (selection != 6)
  {
	  print_me_first("Jeffrey Gu", "CS-116 Lab 9 - MySQL"); 
	  
	  //prints out menu selection
	  cout << "Select an option for the wine database" << endl;
	  cout << "\t1: Display wine between two scores" << endl;
	  cout << "\t2: Display wine between two prices" << endl;
	  cout << "\t3: Display top 10 wine" << endl;
	  cout << "\t4: Insert a new wine" << endl;
	  cout << "\t5: Update an existing wine price" << endl;
	  cout << "\t6: Exit the program" << endl;
	  cin >> selection;
	  
	  //validation for menu selection, user input can not be an invalid input or outside range of 1-6
	  while (cin.fail() || selection < 1 || selection > 6)
	  {
		  cin.clear();
		  cin.ignore(1000, '\n');
		  cout << "Error: Please enter a valid option" << endl;
		  cin >> selection;
	  }
	  
	  //switch statement based on the valid user choice
	  switch (selection)
	  {
		  case 1: //if user chooses 1
		  {
			  //Calls scoreBetween() for a SQL statement modified to user input to find wine between a range of score.
			  string statement = scoreBetween(); 
			  
			  //performs a SQL query based on the modified statement and stores the result in res
			  res = mysql_perform_query(conn, (char *)statement.c_str());
			  
			  printWineInfo(res); //Prints the wineInfo result of the query
			  cout << "SQL Statement used: " << statement << "\n\n"; //prints what SQL statement was used
			  break;
		  }
		  
		  case 2: //if user chooses 2
		  {
			  //Calls priceBetween() for a SQL statement modified to user input to find wine between a range of price.
			  string statement = priceBetween();
			  
			  //performs a SQL query based on the modified statement and stores the result in res
			  res = mysql_perform_query(conn, (char *)statement.c_str());
			  printWineInfo(res); //Prints the wineInfo result of the query
			  cout << "SQL Statement used: " << statement << "\n\n"; //prints what SQL statement was used
			  break;
		  }
		  
		  case 3: //if user chooses 3
		  {
			  //Calls scoreBetween() for a SQL statement to find the top 10 wine sorted by price.
			  string statement = topTen(); 
			  
			  //performs a SQL query based on the modified statement and stores the result in res
			  res = mysql_perform_query(conn, (char *)statement.c_str());
			  printWineInfo(res); //Prints the wineInfo result of the query
			  cout << "SQL Statement used: " << statement << "\n\n"; //prints what SQL statement was used
			  break;
		  }
		  
		  case 4: //if user chooses 4
		  {
			  Wine userWine; //initialize a wine object userWine
			  userWine = newWine(); //set userWine to the info the user provides in newWine()
			  
			  //Calls insertWine for a SQL statement modified to the parameter userWine to insert a new wine to the database
			  string insertStatement = insertWine(userWine);
			  
			  //performs a SQL query based on the insertStatement
			  mysql_perform_query(conn, (char *)insertStatement.c_str());
			  
			  //Creates a SQL search statement to find the new wine that was inserted into the database
			  string searchStatement = "Select * from wineInfo where name = '"+userWine.getName()+"' and vintage = "
										+to_string(userWine.getVintage())+" and score = "+to_string(userWine.getScore())+
										" and price = "+to_string(userWine.getPrice())+" and type = '"+userWine.getType()+"'";
			  //performs a SQL query based on the searchStatement and stores the result in res
			  res = mysql_perform_query(conn, (char *)searchStatement.c_str());
			  printWineInfo(res); //Prints the wineInfo result of the query
			  cout << "SQL Statements used: " << insertStatement << "\n\t\t     " << searchStatement << "\n\n"; //prints what SQL statement was used
			  break;
		  }
		  
		  case 5: //if user chooses 5
		  {
			  Wine wineToUpdate; //initialize a wine object wineToUpdate
			  wineToUpdate = updateWineInfo(); //set wineToUpdate to the info the user provides in updateWineInfo()
			  
			  //Calls updateWine for a SQL statement modified to the parameter wineToUpdate to update an existing wine's price in the database
			  string updateStatement = updateWine(wineToUpdate);
			  
			  //performs a SQL query based on the updateStatement
			  mysql_perform_query(conn, (char *)updateStatement.c_str());
			  
			  //Creates a SQL search statement to find the existing wine that was updated in the database
			  string searchStatement = "Select * from wineInfo where name like '%"+wineToUpdate.getName()+"%'";
			  
			  //performs a SQL query based on the searchStatement and stores the result in res
			  res = mysql_perform_query(conn, (char *)searchStatement.c_str());
			  printWineInfo(res); //Prints the wineInfo result of the query
			  cout << "SQL Statements used: " << updateStatement << "\n\t\t     " << searchStatement << "\n\n"; //prints what SQL statement was used
			  break;
		  }			  
	  }
  }
  
  cout << "Program terminated: Goodbye!" << endl; //prints goodbye message
  
  /* clean up the database result set */
  mysql_free_result(res);
  /* clean up the database link */
  mysql_close(conn);
 
  return 0;
}
