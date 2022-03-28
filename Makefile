CC=g++

build/SocketClient: build/SocketClient.o
	$(CC) build/SocketClient.o -o build/SocketClient

build/SocketClient.o: SocketClient.cpp
	$(CC) -c SocketClient.cpp -o build/SocketClient.o