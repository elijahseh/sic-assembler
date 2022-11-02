/******************************************************************** 
*** NAME : Elijah Hogen
*** CLASS : CSc 354 *** 
*** ASSIGNMENT : Assignment 3 Pass 1 
*** DUE DATE : 11/2/22
*** INSTRUCTOR : GAMRADT *** 
********************************************************************* 
*** DESCRIPTION : Creates class for instructions to store and pass 
each operation's attributes
********************************************************************/

#pragma once

#ifndef OPCODES_H
#define OPCODES_H

#include <string>

class Instr
{
public:
	std::string name;
	std::string format;
	std::string opcode;

	Instr()
	{
		name = "";
		format = "";
		opcode = "";
	}
};

void optable(std::string key);
Instr oplookup(std::string key);
std::string stringHex(std::string s);

#endif // !OPCODES_H

