CXX = g++
CXXFLAGS = -Wall -g

test1: fuel.o mytest.cpp
	$(CXX) $(CXXFLAGS) fuel.o mytest.cpp -o test1

proj1: fuel.o driver.cpp
	$(CXX) $(CXXFLAGS) fuel.o driver.cpp -o proj1

fuel.o: fuel.cpp fuel.h
	$(CXX) $(CXXFLAGS) -c fuel.cpp

run:
	./proj1

test:
	./test1

debug:
	gdb gdbarg1 --args ./proj1

submit:
	cp fuel.h fuel.cpp mytest.cpp ~/cs341proj/proj1/
