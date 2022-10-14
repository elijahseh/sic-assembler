/******************************************************************** 
*** NAME : Elijah Hogen
*** CLASS : CSc 354 *** 
*** ASSIGNMENT : Assignment 2 Expression Evaluation 
*** DUE DATE : 10/14/22 
*** INSTRUCTOR : GAMRADT *** 
********************************************************************* 
*** DESCRIPTION : Contains prototypes for ExpressionHandler.cpp functions,
in case any functions needed to be used externally in later development 
********************************************************************/

#pragma once

#ifndef EXPRESSIONHANDLER_H	
#define EXPRESSIONHANDLER_H         // ExpressionHandler.h

#include <string>
#include "SymbolTable.h"

void ReadExpr(FILE* testPtr, node* bst);
void HandleExpr();
void ProcessPrefix();
void ProcessIndex(std::string str);
void PlusMinus(std::string str);
bool FindExpr(node* rt, std::string key, Symbol& e);
#endif
