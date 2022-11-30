Hogen4:	Hogen4.o SymbolTable.o ExpressionHandler.o LiteralTable.o Opcodes.o Pass1.o Pass2.o
	g++ Hogen4.o SymbolTable.o ExpressionHandler.cpp LiteralTable.cpp Opcodes.cpp Pass1.cpp Pass2.cpp -o Hogen4

Hogen4.o: Hogen4.cpp
	g++ -c Hogen4.cpp

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

Pass2.o: Pass2.cpp
	g++ -c Pass2.cpp

clean:
	rm *.o *.int *.obj Hogen4
