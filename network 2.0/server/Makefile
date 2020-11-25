all: server

server: main.o server_socket.o server.o tools.o system.o
	g++ main.o server_socket.o server.o tools.o system.o -o server

main.o: main.cpp system.h server.h
	g++ -c main.cpp 

server.o: server.cpp server.h
	g++ -c server.cpp
	
server_socket.o: server_socket.cpp server_socket.h tools.h network_exception.h
	g++ -c server_socket.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp

system.o: system.cpp system.h
	g++ -c system.cpp

clean:
	rm *.o server
