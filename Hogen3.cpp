/********************************************************************
*** NAME : ELijah Hogen
*** CLASS : CSc 354
*** ASSIGNMENT : Assignment 3 Pass 1
*** DUE DATE : 11/2/22
*** INSTRUCTOR : GAMRADT
*********************************************************************
*** DESCRIPTION : Perfom the first pass of SIC/XE assembly. 
Output is Location Counter values written to a intermediate file.
This is the main entry file, handles command line args. 
Input/output files are handled in Pass1.cpp
********************************************************************/


#include "SymbolTable.h"
#include "Opcodes.h"
#include "Pass1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        cerr << "Program File not specified" << endl;
        cerr << "Usage: " << argv[0] << " <program file name>" << endl;
    }
     
    else
        Pass1(argv[1]);
        
        return 0;
}

