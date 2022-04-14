CC=g++

build/SocketClient: build/SocketClient.o
	$(CC) -pthread build/SocketClient.o -o build/SocketClient

build/SocketClient.o: SocketClient.cpp
	$(CC) -c SocketClient.cpp -o build/SocketClient.o

clean:
	rm -rf build
	mkdir build