CXX := clang++
CXXFLAGS := -std=c++11 -Wall -Werror
OBJ := main.o Dijkstra.o MinHeap.o

all: main

debug: $(OBJ)
	$(CXX) $(OBJ) -o debug
	$(CXX) $(CXXFLAGS) -g -o $@ $^
	valgrind --leak-check=full ./debug 13

debig: debug
	valgrind --leak-check=full ./debug 27

run: main
	./main 13

big: main
	./main 27

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Dijkstra.h MinHeap.h
	$(CXX) $(CXXFLAGS) -c main.cpp

MinHeap.o: MinHeap.cpp MinHeap.h
	$(CXX) $(CXXFLAGS) -c MinHeap.cpp

Dijkstra.o: Dijkstra.cpp Dijkstra.h MinHeap.h
	$(CXX) $(CXXFLAGS) -c Dijkstra.cpp

clean:
	rm -f main
	rm -f debug
	rm -f *.o