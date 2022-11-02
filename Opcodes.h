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

