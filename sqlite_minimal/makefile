CXXFLAGS=-std=c++11
LINK=-l sqlite3

sqlite_minimal: sqlite_basic_minimal.o

sqlite_basic_minimal.o: sqlite_basic_minimal.cpp
	g++ $(CXXFLAGS) -o $@ $< $(LINK)

.PHONY: clean

clean:
	rm -f *.o
