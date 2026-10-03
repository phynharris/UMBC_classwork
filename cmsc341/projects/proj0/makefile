CXX = g++
CXXFLAGS = -Wall -g

proj0: art.o driver.cpp
	$(CXX) $(CXXFLAGS) art.o driver.cpp -o proj0

mytest: art.o mytest.cpp
	$(CXX) $(CXXFLAGS) art.o mytest.cpp -o mytest

proj: arttest.o drivert.cpp
	$(CXX) $(CXXFLAGS) arttest.o drivert.cpp -o proj

art.o: art.cpp  art.h
	$(CXX) $(CXXFLAGS) -c art.cpp

run:
	./mytest

val:
	valgrind ./proj0

##Use this to clean out your directory
clean:
	rm *~
	rm *.o

##Use this when you want to submit your files (from your proj5 directory)
submit:
	cp Song.h Song.cpp SongPlayer.h SongPlayer.cpp Queue.cpp proj5.cpp ~/cs202proj/proj5

debug:
	gdb gdbarg1 --args ./mytest
