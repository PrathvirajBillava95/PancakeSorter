VERSION = 0.0.1
CXX= g++
INC = -Iinclude/
BIN = bin/PancakeSorter-$(VERSION)

output: src/main.o src/BFSClass.o src/helpers.o
	$(CXX) src/main.o src/BFSClass.o src/helpers.o -o $(BIN)

src/main.o: src/main.cpp
	$(CXX) -c src/main.cpp -o src/main.o $(INC)
src/BFSClass.o: src/BFSClass.cpp
	$(CXX) -c src/BFSClass.cpp -o src/BFSClass.o $(INC)
src/helpers.o: src/helpers.cpp
	$(CXX) -c src/helpers.cpp -o src/helpers.o $(INC)

clean:
	rm -f src/*.o bin/*
