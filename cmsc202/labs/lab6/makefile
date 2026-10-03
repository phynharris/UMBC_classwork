CXX = g++
CXXFLAGS = -Wall

proj2: lab6.cpp SodaCup.o
	$(CXX) $(CXXFLAGS) lab6.cpp SodaCup.o -o lab6

SodaCup.o: SodaCup.h SodaCup.cpp
	$(CXX) $(CXXFLAGS) -c SodaCup.cpp

run:
	./lab6

clean:
	rm *~
