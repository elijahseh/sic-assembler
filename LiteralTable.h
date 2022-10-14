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
