output: main.o Store.o Queue.o
	g++ main.o Store.o Queue.o -o output

main.o: main.cpp
	g++ -c main.cpp 
Store.o: Store.cpp Store.h
	g++ -c Store.cpp
Queue.o: Queue.cpp Queue.h
	g++ -c Queue.cpp
clean:
	rm *.o output
