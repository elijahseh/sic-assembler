#define _CRT_SECURE_NO_DEPRECATE
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
    {
        Pass1(argv[1]);
        //Pass2();
        //FILE* filePtr;
        //FILE* testPtr;

        //filePtr = fopen("SYMBOLS.DAT", "r");
        //testPtr = fopen(argv[1], "r");
        //ifstream prog;
        //prog.open(argv[1]);

        //if (prog.is_open())
        //{
            // Read program file
        //}

        //else
        //{
           // cerr << "ERROR: " << argv[1] << " not found." << endl;
           //e//xit(1);
        //}

        /*
        if (filePtr == NULL)
        {
            cerr << "Error opening SYMBOLS.DAT" << endl;
            //exit(1);
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
                //exit(0);
            }

            else if (TestCheck == 0)
            {
                cerr << argv[1] << " is empty." << endl;
                //exit(0);
            }

            else //initialize symbol table
            {
                rewind(filePtr); //start at beginning of file
                cout << "LOG: SYMBOLS.DAT opened." << endl;

                rewind(testPtr);
                cout << "LOG: " << argv[1] << " opened." << endl;

                //symbol table enrty
                //SymTable(filePtr, testPtr);

            }
        }

        fclose(filePtr);
        fclose(testPtr);

        */
    }

    //optable();
    //writeInt();

    return 0;
}

