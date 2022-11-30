#pragma once

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

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
		bool bflag;
		bool pflag;

		Symbol()
		{
		value = 0;
		symbolStr = "";
		rflag = false;
		mflag = false;

		nflag = true; // N bit
		iflag = true; // I bit
		xflag = false; // X bit
		bflag = false; // B bit
		pflag = true; // P bit
		}
};

struct node
{
	Symbol data;

	struct node* left;
	struct node* right;
};

void SymTable(FILE* filePtr, FILE* testPtr);

//void mFlagSet();
void rFlagSet();
void ProcessSymbol();
void ProcessValue();
void writeSymbol(std::string s, int v);

void insertBST(node*& root, Symbol d);
void parenthPrint(node* root);
void inOrder(node* root);
Symbol traverse(node* root, std::string key);
void printSymbols();
Symbol stablookup(std::string key);
void based(std::string key);

#endif