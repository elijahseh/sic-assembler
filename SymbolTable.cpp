//cpp file for SymbolTable

#include "SymbolTable.h"
#include <iostream>
#include <string>

using namespace std;

FILE* sourceFile; // Global File pointer for use in grabbing characters in SYMBOLS.DAT and searchfiles
char ch;
char lookahead; // 1 position ahead of selected char
int linenum;
node* root = nullptr;
Symbol entry; // Object to store symbols + their attributes

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

void parenthPrint(node* root) // Visual aid for BST
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


/********************************************************************
*** FUNCTION insertBST
*********************************************************************
*** DESCRIPTION : Insert symbols into BST, ignores multiply defined symbols
*** INPUT ARGS : Symbol object populated from SYMBOLS.DAT, BST root node

********************************************************************/

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

/********************************************************************
*** FUNCTION inOrder
*********************************************************************
*** DESCRIPTION : Prints an alphebetic ordered traversal of the BST in table format
*** INPUT ARGS : BST root node

********************************************************************/

void inOrder(node* root)
{
	if (root != nullptr)
	{
		inOrder(root->left);

		cout << "SYMBOL: " << root->data.symbolStr << "\t"
			<< "VALUE: " << root->data.value << "\t"
			<< "RFLAG: " << root->data.rflag << "\t"
			<< "IFLAG:" << root->data.iflag << "\t"
			<< "MFLAG: " << root->data.mflag << endl;

		inOrder(root->right);
	}
}

/********************************************************************
*** FUNCTION traverse
*********************************************************************
*** DESCRIPTION : search function for BST, prints info on multiply defines symbols and raises MFLAGs
*** INPUT ARGS : symbol to search tree for (key), BST root node

********************************************************************/


bool mflag = false;

bool traverse(node* root, string key)
{

	if ((root != nullptr))
	{
		traverse(root->left, key);

		if (root->data.symbolStr == key)
		{
			root->data.mflag = true;
			mflag = true;
			cerr << key << "\t Exists in table." << endl;
		}

		else
		{
			mflag = false;
		}

		traverse(root->right, key);
		return mflag;
	}

	return mflag;
}

bool testMatch = false;



void mFlagSet() // plugs in a symbol from the object into the traversal function to find previous definiton, moves onto rflag if not a duplicate
{
	string key = entry.symbolStr;

	if (!traverse(root, key))
	{
		rFlagSet();

	}
}

void rFlagSet() // checks for valid RFlags, moves onto determining symbol value if Rflag is valid
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
		//skip();
	}
}

/********************************************************************
*** FUNCTION ProcessValue
*********************************************************************
*** DESCRIPTION : Determines an integer value from the last column in SYMBOLS.DAT, if valid the symbol object is added to the tree

********************************************************************/

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

/********************************************************************
*** FUNCTION ProcessSymbol
*********************************************************************
*** DESCRIPTION : checks symbols for illegal characters and lengths, only passes on first 6 chars of valid symbols

********************************************************************/

void ProcessSymbol()
{
	string symbolEntry;
	string wholeRead;
	bool invalid = false;

	skip();

	if (!isalpha(ch) && !isdigit(ch)) // Does not start with letter
	{
		cerr << "ERROR: Symbol does not start with letter. Line " << linenum << endl;
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
			mFlagSet();
		}
	}
}

/********************************************************************
*** FUNCTION SymTable
*********************************************************************
*** DESCRIPTION : Entry point for SYMBOLS.DAT and search file, stops and end of file and updates line number.
Uses traverse function to find matching symbol labels in BST and searchfile
*** INPUT ARGS : SYMBOLS.DAT file pointer and search file pointer
********************************************************************/
void SymTable(FILE* filePtr, FILE* testPtr) 
{
	sourceFile = filePtr;

	GetCh(); // Priming character grabber

	linenum = 1;

	while(ch != EOF)
	{
		if (ch == '\n')
		{
			linenum++;
		}
		
		GetCh();
		ProcessSymbol();
	}

	cout << endl;
	inOrder(root);

	cout << endl << "Entering Search File..." << endl;
	rewind(sourceFile);

	string key;
	ch = fgetc(testPtr);

	while (ch != EOF)
	{
		while (!isspace(ch))
		{
			key += ch;
			ch = fgetc(testPtr);
		}
		

		while (isspace(ch))
		{
			ch = fgetc(testPtr);
		}

		if (traverse(root, key))
		{
			cout << key << "\t not found in symbol table" << endl;
		}
		
		key = "";
	}
	
}
