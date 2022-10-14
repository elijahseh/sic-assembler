/******************************************************************** 
*** NAME : Elijah Hogen
*** CLASS : CSc 354 *** 
*** ASSIGNMENT : Assignment 2 Expression Evaluation 
*** DUE DATE : 10/14/22 
*** INSTRUCTOR : GAMRADT *** 
********************************************************************* 
*** DESCRIPTION : Contains the linked list for the literal table and 
basic literal analysis and evaluation
********************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
//#include "SymbolTable.h"
#include "ExpressionHandler.h"
#include "LiteralTable.h"

using namespace std;

lnode* hd = nullptr;
int pos = 0;

void insertLiteral(lnode*& head, Literal d)
{
	if (head == nullptr)
	{
		head = new lnode;
		head->data = d;
		head->next = nullptr;
	}

	else if (d.address > head->data.address)
	{
		insertLiteral(head->next, d);
	}
}

void printLiterals(lnode* head)
{
	if (head != nullptr)
	{
		printLiterals(head->next);

		cout << setw(15) << head->data.name <<
			setw(25) << head->data.value <<
			setw(10) << head->data.length <<
			setw(10) << head->data.address << endl;
	}
}

void charLiteral(string c)
{
	//cout << "Evaluating character literal: " << c << endl;
	Literal chr;
	string cfull = c;
	c.erase(0, 3);
	c.erase(c.size() - 1, 1);
	chr.length = c.size();
	chr.name = cfull;
	stringstream ss;

	for (const auto& item : c) {
		ss << hex << int(item);
	}
	chr.value = ss.str();
	chr.address = pos++;
	insertLiteral(hd, chr);

}

void hexLiteral(string h)
{
	//cout << "Evaluating hex literal: " << h << endl;
	Literal hex;
	string hfull = h;
	h.erase(0, 3);
	h.erase(h.size() - 1, 1);
	hex.length = h.size() / 2;
	hex.name = hfull;

	if (all_of(h.begin(), h.end(), ::isxdigit)) 
	{
		hex.value = h;
		hex.address = pos++;
		insertLiteral(hd, hex);
	}
}

void LiteralTable()
{
	cout << setw(15) << "NAME" <<
		setw(25) << "VALUE" <<
		setw(10) << "LENGTH" <<
		setw(10) << "ADDRESS" << endl;

	printLiterals(hd);
}