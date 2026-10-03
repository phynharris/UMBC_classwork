CXX = g++
CXXFLAGS = -Wall -g

proj4: vdetect.o driver.cpp
	$(CXX) $(CXXFLAGS) vdetect.o driver.cpp -o proj4

test4: vdetect.o mytest.cpp
	$(CXX) $(CXXFLAGS) vdetect.o mytest.cpp -o test4

streak.o: vdetect.cpp vdetect.h
	$(CXX) $(CXXFLAGS) -c vdetect.cpp

run:
	./proj4

test:
	./test4

debug:
	gdb gdbarg1 --args ./proj4

submit:
	cp vdetect.h vdetect.cpp mytest.cpp ~/cs341proj/proj4/
