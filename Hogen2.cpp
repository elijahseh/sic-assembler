#define _CRT_SECURE_NO_DEPRECATE
#include "SymbolTable.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        cerr << "Search File not specified" << endl;
        cerr << "Usage: " << argv[0] << " <search file name>" << endl;
    }

    else
    {
        FILE* filePtr;
        FILE* testPtr;

        filePtr = fopen("SYMBOLS.DAT", "r");
        testPtr = fopen(argv[1], "r");

        if (filePtr == NULL)
        {
            cerr << "Error opening SYMBOLS.DAT" << endl;
            exit(1);
        }

        else
        {
            int SymbolsCheck;
            fseek(filePtr, 0, SEEK_END);
            SymbolsCheck = ftell(filePtr);

            int TestCheck;
            fseek(testPtr, 0, SEEK_END);
            TestCheck = ftell(testPtr);

            if (SymbolsCheck == 0)
            {
                cerr << "SYMBOLS.DAT is empty." << endl;
                exit(0);
            }

            else if (TestCheck == 0)
            {
                cerr << argv[1] << " is empty." << endl;
                exit(0);
            }

            else //initialize symbol table
            {
                rewind(filePtr); //start at beginning of file
                cout << "LOG: SYMBOLS.DAT opened." << endl;

                rewind(testPtr);
                cout << "LOG: " << argv[1] << " opened." << endl;

                //symbol table enrty
                SymTable(filePtr, testPtr);
            }
        }

        fclose(filePtr);
        fclose(testPtr);
    }

    return 0;
}

