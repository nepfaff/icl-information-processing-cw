CXXFLAGS=-std=c++11

udp_minimal: udp_client_minimal.o udp_server_minimal.o

udp_client_minimal.o: udp_client_minimal.cpp
	g++ $(CXXFLAGS) -o $@ $<

udp_server_minimal.o: udp_server_minimal.cpp
	g++ $(CXXFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f *.o
