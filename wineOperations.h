//wineOperations.h
#ifndef WINEOPERATIONS_H
#define WINEOPERATIONS_H
#include <string>
#include "Wine.h"

using namespace std;

/** 
 * Define the header information for following used functions in
 * wineOperations.cpp
 * @file - wineOperations.h 
 * @author - Jeffrey Gu
**/
void printWineHeader();
void printWineInfo(MYSQL_RES *res);
string scoreBetween();
string priceBetween();
string topTen();
Wine newWine();
string insertWine(Wine userWine);
Wine updateWineInfo();
string updateWine(Wine wineToUpdate);

#endif
