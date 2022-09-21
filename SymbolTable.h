#pragma once

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <vector>

class Symbol
{
public:
		int value;
		std::string symbolStr;
		bool rflag;
		bool mflag;
		bool iflag;

		Symbol()
		{
		value = 0;
		symbolStr = "";
		rflag = false; 
		mflag = false;
		iflag = true;
		}
};

struct node
{
	Symbol data;

	struct node* left;
	struct node* right;
};

void SymTable(FILE* filePtr, FILE* testPtr);
void GetCh();

void mFlagSet();
void rFlagSet();
void ProcessSymbol();
void ProcessValue();


void insertBST(node*& root, Symbol d);
void parenthPrint(node* root);
void inOrder(node* root);
bool traverse(node* root, std::string key);
bool testSearch(node* root, std::string key);

#endif