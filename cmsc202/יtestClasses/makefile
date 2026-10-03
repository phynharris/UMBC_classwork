CXX = g++
CXXFLAGS = -Wall

rect: Rectangle.o driver.cpp
	$(CXX) $(CXXFLAGS) Rectangle.o driver.cpp -o rect

Rectangle.o: Rectangle.h Rectangle.cpp
	$(CXX) $(CXXFLAGS) -c Rectangle.cpp

clean:
	rm *~

run:
	./rect
