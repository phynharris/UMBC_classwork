CXX = g++
CXXFLAGS = -Wall -g

proj3: shop.o driver.cpp
	$(CXX) $(CXXFLAGS) shop.o driver.cpp -o proj3

test3: shop.o mytest.cpp
	$(CXX) $(CXXFLAGS) shop.o mytest.cpp -o test3

streak.o: shop.cpp shop.h
	$(CXX) $(CXXFLAGS) -c shop.cpp

run:
	./proj3

test:
	./test3

debug:
	gdb gdbarg1 --args ./proj3

submit:
	cp shop.h shop.cpp mytest.cpp ~/cs341proj/proj3/
