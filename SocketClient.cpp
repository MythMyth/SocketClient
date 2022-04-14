#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Debug/Debug.h"
#include "PThread/MyPThread.h"
#define PORT 8080
   
using namespace std;

class ServerListener: public MyPThread {
    private:
    int socket_fd;
    public:
    ServerListener(int fd) {
        socket_fd = fd;
    }

    void run() {
        int valread;
        char buffer[1024 + 1] = {'\0'};
        while(1) {
            valread = read( socket_fd , buffer, 1024);
            if(valread <= 0) break;
            if(valread > 1024) valread = 1024;
            buffer[valread] = '\0';
            cout << buffer << "\n";
        }
    }
};

int main(int argc, char const *argv[])
{
    if(argc > 1) {
        Debug::GetInstance()->SetDebugLevel((LogLevel)atoi(argv[1]));
    }

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Socket creation error \n";
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        cout << "Invalid address - Address not supported \n";
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cout << "Connection Failed \n";
        return -1;
    }
    string s;
    cout << "Connected \n";
    ServerListener *listener = new ServerListener(sock);
    listener->start();
    while(1) {
        getline(cin, s);
        Debug::GetInstance()->Log(LOG_LEVEL_HIGH, "%s - %d", s.c_str(), s.size());
        send(sock , s.c_str() , s.size() , 0 );
    }
    
    return 0;
}