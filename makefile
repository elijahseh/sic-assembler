Hogen3:	Hogen3.o SymbolTable.o ExpressionHandler.o LiteralTable.o Opcodes.o Pass1.o
	g++ Hogen3.o SymbolTable.o ExpressionHandler.o LiteralTable.o Opcodes.o Pass1.o -o Hogen3

Hogen3.o: Hogen3.cpp
	g++ -c Hogen3.cpp

SymbolTable.o: SymbolTable.cpp
	g++ -c SymbolTable.cpp

ExpressionHandler.o: ExpressionHandler.cpp
	g++ -c ExpressionHandler.cpp

LiteralTable.o: LiteralTable.cpp
	g++ -c LiteralTable.cpp

Opcodes.o: Opcodes.cpp
	g++ -c Opcodes.cpp

Pass1.o: Pass1.cpp
	g++ -c Pass1.cpp

clean:
	rm -f *.o $(objects) Hogen3
	rm -f *.int Hogen3
