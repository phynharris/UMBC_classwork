CXX = g++
CXXFLAGS = -Wall

lab9: Housing.o Apartment.o Cabin.o lab9.cpp
	$(CXX) $(CXXFLAGS) Housing.o Apartment.o Cabin.o lab9.cpp -o lab9

Housing.o: Housing.h Housing.cpp
	$(CXX) $(CXXFLAGS) -c Housing.cpp

Apartment.o: Apartment.h Apartment.cpp Housing.o
	$(CXX) $(CXXFLAGS) -c Apartment.cpp

Cabin.o: Cabin.h Cabin.cpp Housing.o
	$(CXX) $(CXXFLAGS) -c Cabin.cpp

run:
	./lab9

clean:
	rm *~
	rm *.o
