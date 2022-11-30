//	Operation code lookup table
//  Handles SIC/XE Instruction set
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Opcodes.h"
#include "Pass1.h"

using namespace std; 
ifstream table; // File stream for Instruction Table

Instr oplookup(string s) // Lookup function for opcodes
{
	table.open("Instr.txt");
	Instr i;

	if (table.is_open())
	{
		string o, buffer;
		string key = s;
		bool format4 = false;

		if (s[0] == '+')
		{
			format4 = true;
			key.erase(0, 1); // Remove + symbol for searching purposes
		}

		while (!table.eof())
		{
			table >> o; // Read in name of operation 

			if (o.compare(key) == 0)
			{
				i.name = o;

				table >> o;
				i.format = o;

				table >> o;
				i.opcode = o;

				break;
			}

			else if(!table.eof())
			{
				getline(table, buffer); // Skip to next line if name doens't match
			}
		}

		if (format4 == true)
		{
			//cout << "Format 4 found!!" << endl;
			i.format = "4";
			i.name = s;
		}
	}

	table.close();
	return i;
}
