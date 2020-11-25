all: client

client: main.o client_socket.o tools.o Passenger_Client.o
	g++ main.o client_socket.o tools.o Passenger_Client.o -o client

main: main.cpp
	g++ -c main.cpp

client_socket.o: client_socket.cpp client_socket.h tools.h network_exception.h
	g++ -c client_socket.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp

Passenger_Client.o: Passenger_Client.cpp Passenger_Client.h client_exception.h
	g++ -c Passenger_Client.cpp
	
clean:
	rm *.o client
