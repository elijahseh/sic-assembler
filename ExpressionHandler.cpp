//

#include <iostream>
#include <string>
#include <iomanip>
#include "SymbolTable.h"
#include "ExpressionHandler.h"
#include "LiteralTable.h"

using namespace std;

FILE* exprFile;
char ex;
node* bst = nullptr;
lnode* head = nullptr;

void GetExp()
{
	ex = fgetc(exprFile);
}

void ff()
{
	while (isspace(ex))
	{
		if (ex == EOF)
			break;

		GetExp();
	}
}

string RelAbs(Symbol s)
{
	string rf;

	if (s.rflag)
		rf = "RELATIVE";
	else
		rf = "ABSOLUTE";

	return rf;
}

string GrabExp()
{
	string str = "";
	while (!isspace(ex))
	{
		if (ex == EOF)
			break;
		else if (ex == '-' || ex == '+')
		{
			str += ex;
			GetExp();
			break;
		}

		str += ex;
		GetExp();
	}

	return str;
}

bool isOp(string str)
{
	bool ops = false;
	if (str[str.size() - 1] == '+' || str[str.size() - 1] == '-')
	{
		ops = true;
	}

	return ops;
}

void PlusMinus(string str)
{
	char oper = str[str.size() - 1];
	string op2 = GrabExp();
	string fullstr = str + op2;
	string op1 = str.erase(str.size() - 1, 1);
	Symbol expression;

	int num1 = 0;
	int num2 = 0;
	int rf1 = 0; // RFlag #1
	int rf2 = 0; // RFlag #2
	int adjRflag = 0; // Adjusted RFlag (Over/underflow check)

	if (op1[0] == '@' || op1[0] == '#')
		op1.erase(0, 1);

	if (op2[op2.size() - 1] == 'X' || op2[op2.size() - 1] == 'x')
	{
		op2.erase(op2.size() - 2, 2);
	}

	/*         First operand evaluation          */
	if (isdigit(op1[0])) 
	{
		num1 = stoi(op1);
	}

	else if (op1[0] == '-')
	{
		op1.erase(0, 1);
		num1 = stoi(op1);
		num1 = num1 * -1;
	}

	else if (isalpha(op1[0]))
	{
		op1 = op1.substr(0, 6);
		FindExpr(bst, op1, expression);
		num1 = expression.value;
		rf1 = (int)expression.rflag;
	}

	/*         Second operand evaluation          */
	if (isdigit(op2[0])) 
	{
		num2 = stoi(op2);
	}

	else if (op2[0] == '-')
	{
		op2.erase(0, 1);
		num2 = stoi(op2);
		num2 = num2 * -1;
	}

	else if (isalpha(op2[0]))
	{
		op2 = op2.substr(0, 6);
		FindExpr(bst, op2, expression);
		num2 = expression.value;
		rf2 = (int)expression.rflag;
	}

	if (oper == '+')
	{
		num1 = num1 + num2;
		adjRflag = rf1 + rf2;
	}

	else if (oper == '-')
	{
		num1 = num1 - num2;
		adjRflag = rf1 - rf2;
	}

	if (str[0] == '@')
	{
		expression.nflag = true;
		expression.iflag = false;
	}

	else if (str[0] == '#')
	{
		expression.nflag = false;
		expression.iflag = true;
	}

	else if (fullstr[fullstr.size() - 2] == ',')
	{
		expression.xflag = true;
	}
		
			
	if (adjRflag < 0 || adjRflag > 1) // Under/Overflow error
	{
		cout << setw(15) << fullstr << setw(10) << "(ERROR)" << endl;
	}
		
	else
	{
		expression.value = num1;

		cout << setw(15) << fullstr <<
			setw(10) << expression.value <<
			setw(13) << RelAbs(expression) <<
			setw(7) << expression.nflag <<
			setw(7) << expression.iflag <<
			setw(7) << expression.xflag << endl;
	}
}

void ReadExpr(FILE* testPtr, node*rt)
{
	exprFile = testPtr;
	bst = rt;
	GetExp();

	cout << setw(15) << "EXPRESSION" << 
		setw(10) << "VALUE" << 
		setw(13) << "RELOCATABLE" <<
		setw(7) << "N-Bit" << 
		setw(7) << "I-Bit" << 
		setw(7) << "X-Bit" << endl;

	while (ex != EOF)
	{
		HandleExpr();
		GetExp();
	}

	LiteralTable();
}

bool FindExpr(node* rt, string key, Symbol &e)
{
	bool found = false;
	if ((rt != nullptr))
	{
		FindExpr(rt->left, key, e);

		if (rt->data.symbolStr == key)
		{
			e = rt->data;
			found = true;
		}

		FindExpr(rt->right, key, e);
	}

	return found;
}

void HandleExpr()
{
	ff();
	Symbol expression;
	string expr;
	string fullexpr;

	if (isdigit(ex) || ex == '-')
	{
		int num;
		//cout << "Absolute value found: " << endl;
		if (ex == '-')
		{
			GetExp();
			expr = GrabExp();
			if (!isOp(expr))
			{
				num = stoi(expr);
				num = num * -1;

				cout << setw(15) << num <<
					setw(10) << num <<
					setw(13) << "ABSOLUTE" <<
					setw(7) << "0" <<
					setw(7) << "1" <<
					setw(7) << "0" << endl;
			}

			else
				PlusMinus(expr);
		}

		else
		{
			expr = GrabExp();

			if (!isOp(expr))
			{
				num = stoi(expr);

				cout << setw(15) << num <<
					setw(10) << num <<
					setw(13) << "ABSOLUTE" <<
					setw(7) << "0" <<
					setw(7) << "1" <<
					setw(7) << "0" << endl;
			}

			else
				PlusMinus(expr);
		}
	}

	else if (ex == '@')
		ProcessPrefix();

	else if (ex == '#')
		ProcessPrefix();

	else if (ex == '=')
	{
		//cout << "Literal found: ";
		expr = GrabExp();
		if (expr[1] == 'C' || expr[1] == 'c')
		{
			//cout << "Reading character literal... " << expr << endl;
			charLiteral(expr);
		}
			
		else if (expr[1] == 'X' || expr[1] == 'x')
		{
			//cout << "Reading hex literal... " << expr << endl;
			hexLiteral(expr);
		}
	}

	else if (isalpha(ex))
	{
		//cout << "Normal Expression found: " << endl;
		expr = GrabExp();
		fullexpr = expr;

		if (expr[expr.size() - 2] == ',')
			ProcessIndex(expr);

		else if (isOp(expr))
		{
			//cout << "Expression symbol found... " << expr << endl;
			PlusMinus(expr);
		}

		else
		{
			expr = expr.substr(0, 6); // Only first 6 chars

			FindExpr(bst, expr, expression);

			cout << setw(15) << fullexpr << 
				setw(10) << expression.value << 
				setw(13) << RelAbs(expression) <<
				setw(7) << expression.nflag << 
				setw(7) << expression.iflag << 
				setw(7) << expression.xflag << endl;
		}
	}
}

void ProcessIndex(string str)
{
	Symbol expression;
	string fullstr = str;
	if (str[str.size() - 1] == 'X' || str[str.size() - 1] == 'x')
	{
		str.erase(str.size()-2, 2);
		str = str.substr(0, 6);

		FindExpr(bst, str, expression);
		expression.xflag = 1;

		cout << setw(15) << fullstr <<
			setw(10) << expression.value <<
			setw(13) << RelAbs(expression) <<
			setw(7) << expression.nflag <<
			setw(7) << expression.iflag <<
			setw(7) << expression.xflag << endl;
	}

	else
	{
		cout << setw(15) << fullstr << setw(10) << "(ERROR)" << endl;
	}
}

void ProcessPrefix()
{
	bool invalid = false;
	string str = "";
	string fullstr;
	Symbol expression;
	char type = ex; // Save @ or #

	while (!isspace(ex))
	{
		if (ex == EOF)
			break;
		else if (ex == ',')
			invalid = true;

		else if (ex == '-')
		{
			str += ex;
			GetExp();
			break;
		}
			
		else if (ex == '+')
		{
			str += ex;
			GetExp();
			break;
		}
			
		str += ex;
		GetExp();
	}

	//cout << "Have immediate/indirect: " << str << endl;

	if (invalid)
	{
		cout << setw(15) << str << setw(10) << "(ERROR)" << endl;
	}

	else if (type == '@')
	{
		fullstr = str;

		if (isOp(str))
		{
			//cout << "Adding indirect... " << str << endl;
			PlusMinus(str);
		}

		else
		{
			str.erase(0, 1); // Remove @ symbol
			if (isdigit(str[0]))
			{
				cout << setw(15) << fullstr <<
					setw(10) << str <<
					setw(13) << "RELATIVE" <<
					setw(7) << 1 <<
					setw(7) << 0 <<
					setw(7) << 0 << endl;
			}

			else
			{
				str = str.substr(0, 6);
				FindExpr(bst, str, expression);

				expression.nflag = 1;
				expression.iflag = 0;

				cout << setw(15) << fullstr <<
					setw(10) << expression.value <<
					setw(13) << RelAbs(expression) <<
					setw(7) << expression.nflag <<
					setw(7) << expression.iflag <<
					setw(7) << expression.xflag << endl;
			}
		}
	}

	else if (type == '#')
	{
		fullstr = str;
		
		if (isOp(str))
		{
			PlusMinus(str);
			//cout << "Adding immediate..." << endl;
		}

		else
		{
			str.erase(0, 1); // Remove # symbol
			if (isdigit(str[0]))
			{
				cout << setw(15) << fullstr <<
					setw(10) << str <<
					setw(13) << "ABSOLUTE" <<
					setw(7) << 0 <<
					setw(7) << 1 <<
					setw(7) << 0 << endl;
			}

			else
			{
				str = str.substr(0, 6);
				FindExpr(bst, str, expression);

				expression.nflag = 0;
				expression.iflag = 1;

				cout << setw(15) << fullstr <<
					setw(10) << expression.value <<
					setw(13) << RelAbs(expression) <<
					setw(7) << expression.nflag <<
					setw(7) << expression.iflag <<
					setw(7) << expression.xflag << endl;
			}
		}
	}
}