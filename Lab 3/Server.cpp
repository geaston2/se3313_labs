#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <vector>
#include <string>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include "socketserver.h"
#include "socket.h"
#include <thread>
#include <stack>


using namespace std;
using namespace Sync;
#define portNum 8080

//reverse string method
string reverseString(const string &inputString)
{
    string reversed;
    for (int i = inputString.length() - 1; i >= 0; i--) {
        reversed.push_back(inputString[i]);
    }
    return reversed;
}

//thread function
void ThreadMain(Socket recvSocket,ByteArray buffer){
    //convert buffer to stirng, reverse string, write back
	std::string recieved = buffer.ToString();
    std::cout<<"Recieved string: "<<recieved<<std::endl;
    std::string response = reverseString(recieved);

    //send back
    Sync::ByteArray payload(response);
	recvSocket.Write(payload);
    std::cout<<response<<" returned to client"<<std::endl;
    recvSocket.Close();
}


int main(void)
{
    //create socket server
    std::cout << "I am a server." << std::endl;
    SocketServer server(portNum);
    std::cout<< "Server initialized!" <<std::endl;

    //thread stack to store thread objects
    std::stack<std::thread> threads;

    //wait for connection
    //accept connection
    Socket recvSocket = server.Accept();
    std::cout<<"Accepting incoming connections"<<std::endl;

   while(true){
        //read from socket, create threadd from recieved data
        Sync::ByteArray buffer;
        std::cout<<"Reading incoming data"<<std::endl;
        recvSocket.Read(buffer);

        threads.push(std::thread(ThreadMain,recvSocket,buffer));
    }
    //close socket, empty thread stack
    recvSocket.Close();
    while(!threads.empty()){
		threads.top().join();
		threads.pop();
	}

}

