//print_me_first.h
#ifndef PRINT_ME_FIRST_H
#define PRINT_ME_FIRST_H
#include <string>


using namespace std;

/** 
 * Define the header information for print_me_first
 * forward declaration - tells the compiler that the function 
 * print_me_first( ) is defined else where so just go use it, and 
 * it will be resolved during the linking time. 
 * @file - print_me_first.h 
 * @author - Jeffrey Gu
**/

void print_me_first(string name, string courseInfo);
#endif
