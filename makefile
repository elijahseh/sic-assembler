Hogen2: Hogen2.o SymbolTable.o ExpressionHandler.o LiteralTable.o
	g++  Hogen2.o SymbolTable.o ExpressionHandler.o LiteralTable.o -o Hogen2

Hogen2.o: Hogen2.cpp
	g++ -c Hogen2.cpp

SymbolTable.o: SymbolTable.cpp
	g++ -c SymbolTable.cpp

ExpressionHandler.o: ExpressionHandler.cpp
	g++ -c ExpressionHandler.cpp

LiteralTable.o: LiteralTable.cpp
	g++ -c LiteralTable.cpp

clean:
	rm *.o Hogen2
