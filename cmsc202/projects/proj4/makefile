CXX = g++
CXXFLAGS = -Wall -g

proj4: proj4.cpp Farm.o AgItem.o Animal.o Tree.o Fruit.o Vegetable.o
	$(CXX) $(CXXFLAGS) proj4.cpp Farm.o AgItem.o Animal.o Tree.o Fruit.o Vegetable.o -o proj4

Farm.o: Farm.h Farm.cpp AgItem.o Animal.o Tree.o Fruit.o Vegetable.o
	$(CXX) $(CXXFLAGS) -c Farm.cpp

AgItem.o: AgItem.h AgItem.cpp
	$(CXX) $(CXXFLAGS) -c AgItem.cpp

Animal.o: Animal.h Animal.cpp AgItem.o
	$(CXX) $(CXXFLAGS) -c Animal.cpp

Tree.o: Tree.h Tree.cpp AgItem.o Fruit.o
	$(CXX) $(CXXFLAGS) -c Tree.cpp

Fruit.o: Fruit.h Fruit.cpp
	$(CXX) $(CXXFLAGS) -c Fruit.cpp

Vegetable.o: Vegetable.h Vegetable.cpp AgItem.o
	$(CXX) $(CXXFLAGS) -c Vegetable.cpp

run:
	./proj4

clean:
	rm *~
	rm *.o

val:
	valgrind ./proj4

submit:
	cp AgItem.cpp Animal.cpp Farm.cpp Fruit.cpp proj4.cpp  Tree.h Vegetable.h AgItem.h Animal.h Farm.h Fruit.h Tree.cpp Vegetable.cpp ~/cs202proj/proj4
