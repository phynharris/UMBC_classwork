CXX = g++
CXXFLAGS = -Wall -g

proj2: streak.o driver.cpp
	$(CXX) $(CXXFLAGS) streak.o driver.cpp -o proj2

test2: streak.o mytest.cpp
	$(CXX) $(CXXFLAGS) streak.o mytest.cpp -o test2

streak.o: streak.cpp streak.h
	$(CXX) $(CXXFLAGS) -c streak.cpp

run:
	./proj2

test:
	./test2

debug:
	gdb gdbarg1 --args ./proj2

submit:
	cp streak.h streak.cpp mytest.cpp ~/cs341proj/proj2/
