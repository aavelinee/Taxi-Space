all: Utility.o Universe.o User.o Spaceship.o Trip.o System.o Command.o main.o
	g++ Utility.o Universe.o User.o Spaceship.o Trip.o System.o Command.o main.o -o a.out
Exception.o: Exception.h
Utility.o: Utility.h Utility.cpp
	g++ -c Utility.cpp
Universe.o: Universe.h Universe.cpp Utility.h
	g++ -c Universe.cpp
Spaceship.o: Spaceship.h Spaceship.cpp
	g++ -c Spaceship.cpp
User.o: User.h User.cpp Utility.h Spaceship.h
	g++ -c User.cpp
Trip.o: Trip.h Trip.cpp User.h
	g++ -c Trip.cpp
System.o: System.h System.cpp User.h Universe.h
	g++ -c System.cpp
Command.o: Command.h Command.cpp System.h
	g++ -c Command.cpp
main.o: main.cpp System.h Command.h Universe.h
	g++ -c main.cpp