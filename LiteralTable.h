/******************************************************************** 
*** NAME : Elijah Hogen
*** CLASS : CSc 354 *** 
*** ASSIGNMENT : Assignment 2 Expression Evaluation 
*** DUE DATE : 10/14/22 
*** INSTRUCTOR : GAMRADT *** 
********************************************************************* 
*** DESCRIPTION : Contains the data type for the Literal Table, 
basic node structure for the literal table's linked list, and 
function prototypes for LiteralTable.cpp
********************************************************************/

#pragma once
#ifndef LITERALTABLE_H	
#define LITERALTABLE_H

#include <string>
#include "SymbolTable.h"

class Literal
{
public:
	std::string value;
	std::string name;
	int length;
	int address;

	Literal()
	{
		value = "";
		name = "";
		length = 0;
		address = 0;
	}
};
struct lnode
{
	Literal data;
	struct lnode* next;
};

void insertLiteral(lnode*& head, Literal d);
void charLiteral(std::string c);
void hexLiteral(std::string h);
void LiteralTable();
#endif
