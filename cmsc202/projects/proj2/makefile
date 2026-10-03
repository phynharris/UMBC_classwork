CXX = g++
CXXFLAGS = -Wall

proj2: proj2.cpp Game.o Squad.o Unit.o
	$(CXX) $(CXXFLAGS) proj2.cpp Game.o Squad.o Unit.o -o proj2

Game.o: Game.h Game.cpp Squad.o Unit.o
	$(CXX) $(CXXFLAGS) -c Game.cpp

Squad.o: Unit.o Squad.h Squad.cpp
	$(CXX) $(CXXFLAGS) -c Squad.cpp

Unit.o: Unit.h Unit.cpp
	$(CXX) $(CXXFLAGS) -c Unit.cpp

run:
	./proj2

clean:
	rm *~
