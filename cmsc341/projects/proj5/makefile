CXX = g++
CXXFLAGS = -Wall -g

proj5: graph.o driver.cpp
	$(CXX) $(CXXFLAGS) graph.o driver.cpp -o proj5

test5: graph.o mytest.cpp
	$(CXX) $(CXXFLAGS) graph.o mytest.cpp -o test5

graph.o: graph.cpp graph.h
	$(CXX) $(CXXFLAGS) -c graph.cpp

run:
	./proj5

test:
	./test5

debug:
	gdb gdbarg1 --args ./proj4

submit:
	cp graph.h graph.cpp mytest.cpp chat.pdf report.pdf ~/cs341proj/proj5/
