//cpp file for SymTable

#include <iostream>
#include <string>
#include <iomanip>
#include "SymbolTable.h"
#include "ExpressionHandler.h"

using namespace std;

FILE* sourceFile;
char ch;
char lookahead;
int linenum;
node* root = nullptr;
Symbol entry;
bool search = false;

void writeSymbol(string s, int v)
{
	s.pop_back(); // Remove ':' from symbol name

	entry.symbolStr = s;
	entry.value = v;
	insertBST(root, entry);
}

void GetCh() // Main character grabbing fucntion for SYMBOLS.DAT
{
	ch = lookahead;
	lookahead = fgetc(sourceFile);
}

void skip() // Skips possible whitespace
{
	while (isspace(ch))
	{
		GetCh();
	}
}

void parenthPrint(node* root)
{
	if (root != nullptr)
	{
		cout << root->data.value << " ";
		if (root->left != nullptr || root->right != nullptr)
		{
			cout << "( ";
			parenthPrint(root->left);
			parenthPrint(root->right);
			cout << ") ";
		}
	}
}

void insertBST(node*& root, Symbol d)
{
	if (root == nullptr)
	{
		root = new node;
		root->data = d;
		root->left = nullptr;
		root->right = nullptr;
	}

	else if (d.symbolStr < root->data.symbolStr)
	{
		insertBST(root->left, d);
	}

	else if (d.symbolStr > root->data.symbolStr)
	{
		insertBST(root->right, d);
	}
}

void inOrder(node* root)
{
	if (root != nullptr)
	{
		inOrder(root->left);

		cout << setw(15) << root->data.symbolStr 
			<< setw(7) << hex << root->data.value
			<< setw(7) << root->data.rflag
			<< setw(7) << root->data.iflag
			<< setw(7) << root->data.mflag << endl;

		inOrder(root->right);
	}
}

void printSymbols()
{
	cout << endl << "********* Symbol Table *********" << endl << endl;
	cout << setw(15) << "SYMBOL"
		<< setw(7) << "VALUE"
		<< setw(7) << "RFLAG"
		<< setw(7) << "IFLAG"
		<< setw(7) << "MFLAG" << endl;

	inOrder(root);
}


bool mflag = false;

Symbol traverse(node* root, string key)
{

	if ((root != nullptr))
	{
		traverse(root->left, key);

		if (root->data.symbolStr == key)
		{

			//root->data.mflag = true;
			//mflag = true;

			
			cerr << key << "\t Exists in table." << endl;
		}

		else
		{
			//mflag = false;
		}

		traverse(root->right, key);
		//return mflag;
	}

	return root->data;
}

void rFlagSet()
{
	string flagCheck;
	bool invalid = false;
	
	while (isspace(ch))
	{
		GetCh();
	}

	while (!isspace(ch))
	{
		flagCheck += ch;
		GetCh();
	}

	if (flagCheck.compare("false") == 0 || flagCheck.compare("0") == 0)
	{
		entry.rflag = false;
		ProcessValue();
	}

	else if (flagCheck.compare("true") == 0 || flagCheck.compare("1") == 0)
	{
		entry.rflag = true;
		ProcessValue();
	}

	else
	{
		cerr << "ERROR: Invalid RFlag. Line " << linenum << endl;
		skip();
	}
}


void ProcessValue()
{
	skip();
	int valueAppend = 0;

	if (ch == '-')
	{
		valueAppend += ch;
		GetCh();
	}

	if (isdigit(ch))
	{
			
		valueAppend = ch - '0'; // convert input stream char to int for Symbol value
		int valueEntry = valueAppend;
		GetCh();

		while (isdigit(ch))
		{
			valueAppend = ch - '0';
			valueEntry = (valueEntry * 10) + valueAppend;
			GetCh();
		}

		if (isspace(ch) || ch == '\n' || ch == EOF)
		{
			entry.value = valueEntry;
			insertBST(root, entry);
		}
	}
}

void ProcessSymbol()
{
	string symbolEntry;
	string wholeRead;
	bool invalid = false;

	skip();

	if (!isalpha(ch) && !isdigit(ch)) // Does not start with letter
	{
		//cerr << "ERROR: Symbol does not start with letter. Line " << linenum << endl;
	}

	else
	{
		for (int i = 0; i <= 12; i++) // i <= 12 to count 1 above length limit to detect over-max-length symbols
		{
			if (isalpha(ch) || isdigit(ch)) // Only letters and numbers
			{
				wholeRead += ch;
				GetCh();
			}

			else if (ch == ':') // End of symbol reached
			{
				GetCh();
				break;
			}

			else
			{
				invalid = true;
				break;
			}
		}

		if (wholeRead.length() > 12)
		{
			cerr << "ERROR: Symbol Exceeds Max Length (12 characters). Line " << linenum << endl;

			while (!isspace(ch))
				GetCh();
		}

		else if (invalid == true)
		{
			cerr << "ERROR: Symbol contains illegal characters. Line " << linenum << endl;

			while (!isspace(ch))
				GetCh();
		}

		else // Symbol: starts with letter, only has letters and #'s, 12 chars or less long
		{
			symbolEntry = wholeRead.substr(0, 6); // Save first 6 characters only
			entry.symbolStr = symbolEntry;
			//mFlagSet();
		}
	}
}

void SymTable(FILE* filePtr, FILE* testPtr)
{
	sourceFile = filePtr;

	GetCh(); // Priming character grabber

	linenum = 1;

	while(ch != EOF)
	{
		if (ch == '\n')
			linenum++;
		

		GetCh();
		ProcessSymbol();
	}

	cout << endl;
	inOrder(root);

	cout << endl << "Entering Search File..." << endl << endl;;
	rewind(sourceFile);

	ReadExpr(testPtr, root); // Expression Evaluation entry	
}
