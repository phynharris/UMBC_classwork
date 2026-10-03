CXX = g++
CXXFLAGS = -Wall -g

lab7: lab7.cpp Playlist.o
	$(CXX) $(CXXFLAGS) lab7.cpp Playlist.o -o lab7

Playlist.o: Playlist.cpp Playlist.h
	$(CXX) $(CXXFLAGS) Playlist.cpp -c

run:
	./lab7

val:
	valgrind ./lab7

clean:
	rm *~ *.o lab7
