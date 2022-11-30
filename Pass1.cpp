//
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include "Pass1.h"
#include "Pass2.h"
#include "SymbolTable.h"		// Column 1
#include "Opcodes.h"			// Column 2
#include "ExpressionHandler.h"	// Column 3

using namespace std;

int linen = 1; // Line number
int LC = 0; // Location Counter

ifstream p; // Input: program file
ofstream inter; // Output: intermediate file;

// Buffers for: Column 1 (Symbols/Labels)	Column 2 (Operations)	Column 3 (Operands)
string c1, c2, c3;
string filename;
string buffer;

string nextLine()
{
	getline(p, buffer);
	linen++;

	return buffer;
}

void makeInt() // Creates intermediate file with template
{
	p >> c1;
	if (c1[0] == ';')
	{
		nextLine();
		p >> c1;
	}

	if (isSymbol(c1))
	{
		filename = c1;
		filename.pop_back(); // Remove : from program name
		filename += ".int";
		inter.open(filename, ios::out);

		inter << "INTERMEDIATE FILE FOR " << c1 << endl << endl;
		inter << setw(4) << "LINE" << setw(5) << "LC"
		<< setw(15) << "LABEL" << setw(15) << "OPERATION"
		<< setw(15) << "OPERAND" << endl << endl;

		p >> c2;

		if (c2.compare("START") == 0)
		{
			p >> c3;
			LC = stoi(c3);

			writeInt(-1);
			writeInt(0);
			writeInt(1);
			writeInt(2);
			writeInt(3);
			nextLine();
		}

		else
			cerr << "ERROR: expecting START directive." << endl;
	

	}

	else
		cerr << "ERROR: Invalid program name '" << c1 << "'" << endl;
	
}

void writeInt(int col)
{
	if (col == -1) // Line numbers
		inter << setw(4) << (int)linen;

	else if (col == 0) // Location counter
		inter << setw(5) << hex << LC; 

	else if (col == 1) // Column 1, symbols
		inter << setw(15) << c1;

	else if (col == 2) // Column 2, operations
		inter << setw(15) << c2;

	else if (col == 3) // column 3, operands
		inter << setw(15) << c3 << endl;
}

void Pass1(char* progname) // Beginning and end point for Pass 1
{
	p.open(progname);

	if (p.is_open())
	{
		makeInt();

		while (!p.eof())
		{
			p >> c1;

			if (c1 != "")
				Col1(c1);
		}
	}

	else
	{
		cerr << "ERROR:" << progname << " not found!" << endl;
		exit(1);
	}

	printSymbols();

	p.close();
	inter.close();

	Pass2(filename);
}

bool isSymbol(string s)
{
	bool found = false;

	if (s.back() == ':')
	{
		writeSymbol(s, LC);
		c1 = s;
		found = true;
	}

	return found;
}

void Col1(string s)
{
	if (c1[0] == ';')
		nextLine();

	else if (isSymbol(s))
	{
		writeInt(-1);
		writeInt(0);
		writeInt(1);

		p >> c2;
		Col2(c2);
	}

	else
	{
		c2 = c1;
		c1 = "";

		writeInt(-1);
		writeInt(0);
		writeInt(1);

		Col2(c2);
	}
}

void Col2(string s)
{
	if (s[0] == ';') // Comment found after Col 2
		nextLine();

	else if (dir(s))
	{
		//cout << "Directive found: " << s << endl;
	}

	else
	{
		Instr op = oplookup(s);
		LC = LC + stoi(op.format);

		writeInt(2);

		if (op.format == "1")
		{
			c3 = "";
			writeInt(3);
			nextLine();
		}

		else
		{
			p >> c3;
			writeInt(3);
			nextLine();
		}	
	}
}

bool dir(string s)
{
	bool found = false;

	if (s.compare("BASE") == 0)
	{
		found = true;
		writeInt(2);
		p >> c3;
		writeInt(3);
		nextLine();
	}

	else if (s.compare("BYTE") == 0)
	{
		found = true;
		writeInt(2);
		p >> c3;
		// Evaluate Expression
		writeInt(3);
		LC = LC + 1;
		nextLine();
	}

	else if (s.compare("END") == 0)
	{
		found = true;
		writeInt(2);
		p >> c3;
		writeInt(3);
		nextLine();
	}

	else if (s.compare("EQU") == 0)
	{
		found = true;
		EQU();
		
	}

	else if (s.compare("EXTDEF") == 0)
	{
		found = true;
		writeInt(2);
		p >> c3;
		writeInt(3);
		nextLine();
	}

	else if (s.compare("EXTREF") == 0)
	{
		found = true;
		writeInt(2);
		p >> c3;
		writeInt(3);
		nextLine();
	}

	else if (s.compare("RESB") == 0)
	{
		found = true;
		writeInt(2);
		p >> c3;
		int resb = stoi(c3);
		LC = LC + resb;
		writeInt(3);
		nextLine();
	}

	else if (s.compare("RESW") == 0)
	{
		found = true;
		writeInt(2);
		p >> c3;
		int resb = stoi(c3);
		LC = LC + (resb * 3);
		writeInt(3);
		nextLine();
	}

	else if (s.compare("WORD") == 0)
	{
		found = true;
		writeInt(2);
		p >> c3;
		// Evaluate
		LC = LC + 3;
		writeInt(3);
		nextLine();
	}

	return found;
}

void EQU()
{
	writeInt(2);
	p >> c3;

	int size;

	if (isdigit(c3[0]))
	{
		size = stoi(c3);
		LC = LC + size;
	}

	else if (isalpha(c3[0]))
	{
		size_t plus = c3.find('+');
		size_t minus = c3.find('-');
		string op1, op2;
		vector<string> expression; 

		if (plus != string::npos)
		{
			expression = ExpParse(c3, '+');
			op1 = expression[0];
			op2 = expression[1];
			//cout << "Evaluating " << op1 << " + " << op2 << endl;
		}
			
		

		else if (plus != string::npos)
		{
			expression = ExpParse(c3, '-');
			op1 = expression[0];
			op2 = expression[1];
			//cout << "Evaluating " << op1 << " - " << op2 << endl;
		}
	}

	writeInt(3);
	nextLine();
}

vector<string> ExpParse(string s, char op)
{
	stringstream eqx(s);
	string eq;
	vector<string> ex;

	while (getline(eqx, eq, op))
	{
		ex.push_back(eq);
	}

	return ex;
}

