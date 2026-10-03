CXX = g++
CXXFLAGS = -Wall -g

proj5: SongPlayer.o Song.o proj5.cpp Queue.cpp
	$(CXX) $(CXXFLAGS) SongPlayer.o Song.o Queue.cpp proj5.cpp -o proj5

SongPlayer.o: SongPlayer.cpp  SongPlayer.h Song.o Queue.cpp
	$(CXX) $(CXXFLAGS) -c SongPlayer.cpp

Song.o: Song.cpp Song.h
	$(CXX) $(CXXFLAGS) -c Song.cpp

Queue.o: Queue.cpp
	$(CXX) $(CXXFLAGS) -c Queue.cpp

run:
	./proj5 proj5_songs.txt

val:
	valgrind ./proj5 proj5_songs.txt

##Use this to clean out your directory
clean: 
	rm *~
	rm *.o

##Use this when you want to test just your Queue
qtest: Queue.o queue_test.cpp
	$(CXX) $(CXXFLAGS) Queue.o queue_test.cpp -o qtest

##Use this when you want to valgrind your Queue tests
qtest2:
	valgrind ./qtest

##Use this when you want to debug your whole project
debug1:
	gdb gdbarg1 --args ./proj5 proj5_songs.txt

##Use this when you want to submit your files (from your proj5 directory)
submit:
	cp Song.h Song.cpp SongPlayer.h SongPlayer.cpp Queue.cpp proj5.cpp ~/cs202proj/proj5

