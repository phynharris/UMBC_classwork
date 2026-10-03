CXX = g++
CXXFLAGS = -Wall -g

proj3: proj3.cpp Register.o Order.o OrderItemList.o OrderItem.o Menu.o MenuItem.o Node.h
	$(CXX) $(CXXFLAGS) Register.o proj3.cpp Order.o OrderItemList.o OrderItem.o Node.h Menu.o MenuItem.o -o proj3

debug: proj3.cpp Register.o Order.o OrderItemList.o OrderItem.o Menu.o MenuItem.o Node.h
	$(CXX) -g Register.o proj3.cpp Order.o OrderItemList.o OrderItem.o Node.h Menu.o MenuItem.o -o proj3

Register.o: Register.h Register.cpp Menu.o Order.o OrderItemList.o OrderItem.o
	$(CXX) $(CXXFLAGS) -c Register.cpp

Order.o: Order.h Order.cpp
	$(CXX) $(CXXFLAGS) -c Order.cpp

OrderItemList.o: OrderItemList.h OrderItemList.cpp OrderItem.o Node.h
	$(CXX) $(CXXFLAGS) -c OrderItemList.cpp

OrderItem.o: OrderItem.h OrderItem.cpp
	$(CXX) $(CXXFLAGS) -c OrderItem.cpp

Menu.o: Menu.h Menu.cpp
	$(CXX) $(CXXFLAGS) -c Menu.cpp

MenuItem.o: MenuItem.h MenuItem.cpp
	$(CXX) $(CXXFLAGS) -c MenuItem.cpp

run:
	./proj3

clean:
	rm *~
	rm *.o

val:
	valgrind ./proj3

submit:
	cp Menu.h Menu.cpp MenuItem.h MenuItem.cpp Order.h Order.cpp OrderItem.h OrderItem.cpp OrderItemList.h OrderItemList.cpp Register.h Register.cpp Node.h ~/cs202proj/proj3
