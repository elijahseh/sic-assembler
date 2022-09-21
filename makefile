Hogen1:	Hogen1.o SymbolTable.o
	g++ Hogen1.o SymbolTable.o -o Hogen1

Hogen1.o: Hogen1.cpp
	g++ -c Hogen1.cpp

SymbolTable.o: SymbolTable.cpp
	g++ -c SymbolTable.cpp

clean:
	rm *.o Hogen1