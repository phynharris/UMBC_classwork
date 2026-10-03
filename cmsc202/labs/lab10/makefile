CXX = g++
CXXFLAGS = -Wall

lab10: Drink.o Coffee.o Matcha.o lab10.cpp
	$(CXX) $(CXXFLAGS) Drink.o Coffee.o Matcha.o lab10.cpp -o lab10

Drink.o: Drink.h Drink.cpp
	$(CXX) $(CXXFLAGS) -c Drink.cpp

Coffee.o: Coffee.h Coffee.cpp Drink.o
	$(CXX) $(CXXFLAGS) -c Coffee.cpp

Matcha.o: Matcha.h Matcha.cpp Drink.o
	$(CXX) $(CXXFLAGS) -c Matcha.cpp

run:
	./lab10
