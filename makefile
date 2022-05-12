CXX = g++

all: Server Client #Stack

# Stack: stack.o
# 	$(CXX) stack.o -o Stack

Server: server.o alloc.o
	$(CXX) server.o alloc.o -pthread -o Server

Client: client.o
	$(CXX) client.o -o Client

test: Test.o
	$(CXX) Test.o -o Test

# stack.o: stack.cpp
# 	$(CXX) stack.cpp -c

Test.o: Test.cpp doctest.h
	$(CXX) Test.cpp -c

server.o: server.cpp alloc.hpp
	$(CXX) server.cpp -c

alloc.o: alloc.cpp alloc.hpp
	$(CXX) alloc.cpp -c

client.o: client.cpp
	$(CXX) client.cpp -c

clean:
	rm -f *.o Server Client