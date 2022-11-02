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

