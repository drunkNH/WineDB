//print_me_first.cpp
#include <iostream> 
#include <string> 
#include <iomanip> 
#include <ctime>
#include "print_me_first.h"

/**
    * @Purpose - Print out the programmer’s information such as name, class information    
    * and date/time the program is run 
    * @param name -  the name of the programmer    
    * @param courseInfo -  the name of the course    
    * @return - none 
    * @author Jeffrey Gu
**/ 

void print_me_first(string name, string courseInfo) 
{ 
	cout << " Program written by: " << name << endl; // prints message and name
	cout << " Course info: "<< courseInfo << endl; // prints message and course info
	time_t now = time(0);  // current date/time based on current system 
	char* dt = ctime(&now); // convert now to string for    
	cout << " Date: " << dt << endl; //prints date/time
} 
