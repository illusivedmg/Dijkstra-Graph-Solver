CXX := clang++
CXXFLAGS := -std=c++11 -Wall -Werror

all: main

debug: main.o MinHeap.o
	$(CXX) main.o MinHeap.o -o debug
	$(CXX) $(CXXFLAGS) -g -o $@ $^
	valgrind --leak-check=full ./debug 13

debig: debug
	valgrind --leak-check=full ./debug 27

run: main
	./main 13

big: main
	./main 27

main: main.o MinHeap.o
	$(CXX) main.o MinHeap.o -o main
	$(CXX) $(CXXFLAGS) -o $@ $^

binaryMinHeap.o: MinHeap.cpp MinHeap.h
main.o: main.cpp MinHeap.h

clean:
	rm -f ./main
	rm -f ./debug
	rm -f *.o