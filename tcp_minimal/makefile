CXXFLAGS=-std=c++11

tcp_minimal: tcp_client_minimal.o tcp_server_minimal.o

tcp_client_minimal.o: tcp_client_minimal.cpp
	g++ $(CXXFLAGS) -o $@ $<

tcp_server_minimal.o: tcp_server_minimal.cpp
	g++ $(CXXFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f *.o
