CXX = g++
CXXFLAGS = -Wall

lab5: Bakery.o lab5.cpp
	$(CXX) $(CXXFLAGS) Bakery.o lab5.cpp -o lab5
Bakery.o: Bakery.cpp Bakery.h
	$(CXX) $(CXXFLAGS) -c Bakery.cpp
run:
	./lab5
