labb1 : labb1.o
	g++ -o labb1 labb1.o
labb1.o : labb1.cpp
	g++ -c labb1.cpp