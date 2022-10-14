/******************************************************************** 
*** NAME : Elijah Hogen
*** CLASS : CSc 354 *** 
*** ASSIGNMENT : Assignment 2 Expression Evaluation 
*** DUE DATE : 10/14/22 
*** INSTRUCTOR : GAMRADT *** 
********************************************************************* 
*** DESCRIPTION : Contains the main Symbol data type for the 
symbol table, node structer for BST, and function prototypes for SymbolTable.cpp
********************************************************************/

#pragma once

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H		//SymbolTable.h

#include <string>

class Symbol
{
public:
		int value;
		std::string symbolStr;
		bool rflag;
		bool mflag;

		bool nflag;
		bool iflag;
		bool xflag;

		Symbol()
		{
		value = 0;
		symbolStr = "";
		rflag = false;
		mflag = false;

		nflag = true; // N bit
		iflag = true; // I bit
		xflag = false; // X bit
		}
};

struct node
{
	Symbol data;

	struct node* left;
	struct node* right;
};

void SymTable(FILE* filePtr, FILE* testPtr);

void mFlagSet();
void rFlagSet();
void ProcessSymbol();
void ProcessValue();

void insertBST(node*& root, Symbol d);
void parenthPrint(node* root);
void inOrder(node* root);
bool traverse(node* root, std::string key);

#endif