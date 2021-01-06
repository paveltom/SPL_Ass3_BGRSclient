CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -pthread -lboost_thread


all: BGRSclient

BGRSclient: bin/main.o bin/ConnectionHandler.o bin/EncoderDecoder.o bin/Task.o bin/NetTask.o bin/KeyboardTask.o
	@echo 'Building target: BGRSclient'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/BGRSclient bin/main.o bin/ConnectionHandler.o bin/EncoderDecoder.o bin/Task.o bin/NetTask.o bin/KeyboardTask.o $(LDFLAGS)
	@echo 'Finished building target: BGRSclient'
	@echo ' '


bin/main.o:
	src/main.cpp g++ $(CFLAGS) -o bin/main.o src/main.cpp

bin/ConnectionHandler.o:
	src/ConnectionHandler.cpp g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp $(LDFLAGS)

bin/EncoderDecoder.o:
	src/EncoderDecoder.cpp g++ $(CFLAGS) -o bin/EncoderDecoder.o src/EncoderDecoder.cpp

bin/Task.o:
	src/Task.cpp g++ $(CFLAGS) -o bin/Task.o src/Task.cpp

bin/NetTask.o:
	src/NetTask.cpp g++ $(CFLAGS) -o bin/NetTask.o src/NetTask.cpp

bin/KeyboardTask.o:
	src/KeyboardTask.cpp g++ $(CFLAGS) -o bin/KeyboardTask.o src/KeyboardTask.cpp


.PHONY: clean
clean:
	@echo 'Cleaning'
	rm -f bin/*

