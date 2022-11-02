/******************************************************************** 
*** NAME : Elijah Hogen
*** CLASS : CSc 354 *** 
*** ASSIGNMENT : Assignment 3 Pass 1 
*** DUE DATE : 11/2/22
*** INSTRUCTOR : GAMRADT *** 
********************************************************************* 
*** DESCRIPTION : Contains function prototypes for Pass 1 location counter
********************************************************************/

#pragma once

#ifndef PASS1_H
#define PASS1_H

#include <string>
#include <vector>

void Pass1(char* progname);
void Col1(std::string s);
void Col2(std::string s);
void makeInt();
bool isSymbol(std::string s);
bool dir(std::string s);
void writeInt(int col);
void EQU();
std::vector<std::string> ExpParse(std::string s, char op);

#endif // !PASS1_H

