//
// 

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include "Pass1.h"
#include "Opcodes.h"
#include "SymbolTable.h"
#include "LiteralTable.h"

using namespace std;

int linein = 0, lineout = 1;
int PC = 0;
int Length;
int First;
vector<int> tr;

ifstream in;
ofstream objfile;
ofstream txtfile;
string interscan;
string progname;

// NIXBPE Flag index
const int n = 0, ii = 1, x = 2, b = 3, p = 4, e = 5;

// Flag values in base 2
const int n2 = 2, i2 = 1, x2 = 8, b2 = 4, p2 = 2, e2 = 1; 

bool flags[6];


string nextLinein()
{
	if (linein == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			getline(in, interscan);
			linein++;
			
		}
	}

	else
	{
		getline(in, interscan);
		linein++;
	}

	return interscan;
}

int fromhex(string decimal)
{
	int number = 0;
	number = stoi(decimal, 0, 16);

	return number;
}

int setflags(int format)
{
	int ni = 0;
	int xbpe = 0;

	if (flags[n])
		ni = n2;

	if (flags[ii])
		ni += i2;

	if (flags[x])
		xbpe = x2;

	if (flags[b])
		xbpe += b2;

	if (flags[p])
		xbpe += p2;

	if (flags[e])
		xbpe += e2;

	if (format == 3)
	{
		ni = ni * 65536;
		//cout << "NI= " << ni << endl;
		xbpe = xbpe * 4096;
		//cout << "XBPE = " << xbpe << endl;
	}

	return ni + xbpe;
}

void nixbpe(string operand, string opcode, int format)
{
	Symbol label;
	int TA = 0;
	int nextPC = PC + format;
	// Set defaults
	flags[n] = 1;
	flags[ii] = 1;
	flags[x] = 0;
	flags[b] = 0;
	flags[p] = 1;
	flags[e] = 0;

	if (operand[0] == '#')
	{
		string k = operand;
		flags[n] = 0;
		k.erase(0, 1);
		nextPC = 0;

		if (isalpha(k[0]))
		{
			label = stablookup(k);
			TA = label.value;
			flags[b] = label.bflag;
		}

		else
		{
			TA = stoi(k);
			//cout << "Target Addr: " << TA << endl;
		}
	}

	else if (operand[operand.size() - 2] == ',')
	{
		flags[x] = 1;
		//cout << "Indexing found..." << endl;
		string k = operand;
		k.erase(k.size() - 2, 2);
		//cout << "Looking up: " << k << endl;
		label = stablookup(k);
		TA = label.value;
		flags[b] = label.bflag;
		flags[p] = label.pflag;
	}

	else if (operand[0] == '@')
	{
		flags[ii] = 0;
		//cout << "Indirect found..." << endl;
		string k = operand;
		k.erase(0, 1);
		label = stablookup(k);
		TA = label.value;
		flags[b] = label.bflag;
		flags[p] = label.pflag;
	}

	else
	{
		label = stablookup(operand);
		TA = label.value;
		flags[b] = label.bflag;
		flags[p] = label.pflag;
	}

	if (format == 3)
	{
		int f = setflags(3);
		//cout << f << endl;

		int obj;

		obj = fromhex(opcode) * 65536; // Opcode + space for remaining 5 bytes
		obj += f;
		//cout << obj << endl;
		obj += TA - nextPC;

		cout << '\t' << operand << '\t' << obj << endl;
		txtfile << '\t' << operand << '\t' << obj << endl;
		tr.push_back(obj);

	}
}

bool ProcessLine()
{
	bool end = false;
	Instr mnemonic;
	Symbol label;
	string op;
	string operand;


	in >> op; // Skip line no.
	linein = fromhex(op);
	in >> op; // Skip current LC
	PC = fromhex(op);
	in >> op;

	//cout << "Processing: " << op << endl;
	//cout << "Program Counter = " << PC << endl;
	cout << linein << '\t' << hex << PC << '\t';
	txtfile << linein << '\t' << hex << PC << '\t';

	if (op[op.size() - 1] == ':')
	{
		cout << op << '\t';
		txtfile << op << '\t';
		in >> op; // Skip symbol

		mnemonic = oplookup(op);
		cout << mnemonic.name;
		txtfile << mnemonic.name;
	}

	else
	{
		mnemonic = oplookup(op);
		cout << '\t' << mnemonic.name;
		txtfile << '\t' << mnemonic.name;
	}
	
	in >> operand;

	if (op.compare("START") == 0)
	{
		cout << op << '\t' << operand << endl;
		txtfile << op << '\t' << operand << endl;

		First = fromhex(operand);
		progname = mnemonic.name;

		
	}

	else if (op.compare("BASE") == 0)
	{
		cout << op << '\t' << operand << endl;
		txtfile << op << '\t' << operand << endl;
		based(operand);
		label = stablookup(operand);
		//cout << op << " is " << label.bflag << endl;
	}

	else if (op.compare("RESW") == 0 || op.compare("RESB") == 0)
	{
		cout << op << '\t' << operand << endl;
		txtfile << op << '\t' << operand << endl;
	}

	else if (op.compare("END") == 0)
	{
		cout << op << '\t' << operand << endl;
		txtfile << op << '\t' << operand << endl;
		Length = PC;
		end = true;
	}

	else if (mnemonic.format == "1")
	{
		cout << '\t' << operand << '\t' << mnemonic.opcode << endl;
		txtfile << '\t' << operand << '\t' << mnemonic.opcode << endl;
	}

	else if (mnemonic.format == "2")
	{
		int obj;
		obj = fromhex(mnemonic.opcode)*256;

		if (isalpha(operand[0]))
			obj += 0;

		else
			obj += fromhex(operand);

		cout << '\t' << operand << '\t' << obj << endl;
		txtfile << '\t' << operand << '\t' << obj << endl;
		tr.push_back(obj);
	}

	else if (mnemonic.format == "3")
	{
		nixbpe(operand, mnemonic.opcode, 3);
	}

	else if (mnemonic.format == "4")
	{
		
	}

	return end;
}

void Pass2(string filename)
{
	in.open(filename);

	filename.erase(filename.size() - 4, 4);
	string textfile = filename + ".txt";
	string objectfile = filename + ".obj";

	txtfile.open(textfile, ios::out);
	objfile.open(objectfile, ios::out);

	nextLinein();

	cout << endl << endl;



	cout << "LINE" << '\t' << "LC" << '\t' << "LABEL" << '\t'
		<< "OPER." << '\t' << "OPERAND" << '\t' << "OBJ. CODE" << endl << endl;

	txtfile << "LINE" << '\t' << "LC" << '\t' << "LABEL" << '\t'
		<< "OPER." << '\t' << "OPERAND" << '\t' << "OBJ. CODE" << endl << endl;
	
	while (!ProcessLine())
	{ }

	objfile << "H " << filename << " " << setfill('0') << setw(6)
		<< hex << uppercase << First << " " << setfill('0') << setw(6)
		<< Length << endl;

	objfile << "T " << setfill('0') << setw(6) << hex << uppercase
		<< First << " " << Length << " ";

	for (int i = 0; i < tr.size(); i++)
	{
		objfile << setfill('0') << setw(6) << tr.at(i) << " ";
	}

	objfile << endl << "E " << setfill('0') << setw(6) << First << endl;
	
	in.close();
	txtfile.close();
	objfile.close();
}