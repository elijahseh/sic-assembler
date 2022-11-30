#pragma once

#ifndef EXPRESSIONHANDLER_H	
#define EXPRESSIONHANDLER_H

#include <string>
#include "SymbolTable.h"

void ReadExpr(FILE* testPtr, node* bst);
void HandleExpr();
void ProcessPrefix();
void ProcessIndex(std::string str);
void PlusMinus(std::string str);
bool FindExpr(node* rt, std::string key, Symbol& e);
#endif
