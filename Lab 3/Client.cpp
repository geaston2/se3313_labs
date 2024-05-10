#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socket.h"

using namespace std;
using namespace Sync;

//ip and port number constant
#define ipAddress "127.0.0.1"
#define portNum 8080


int main(void){
	std::cout << "I am a client" << std::endl;



	//create socket
	Socket socket(ipAddress,portNum);
	std::string toReverse;

	//open connection
	socket.Open();
	std::cout<<"Open connecton to "<<ipAddress<<":"<<portNum<<std::endl;

	while(true){
		//take input. if done, break
		std::cout<<"Word you need reversed (word or done)?";
		cin>>toReverse;

		if(toReverse=="done" || toReverse=="Done"){
			break;
		}

		//write data over connection
		Sync::ByteArray payload(toReverse);
		socket.Write(payload);

		//wait for response (read blocks and waits)
		Sync::ByteArray buffer;
		socket.Read(buffer);
		std::string response = buffer.ToString();
		

		//print response
		std::cout<<"Reversed word: "<<response<<std::endl;
	}
	socket.Close();
}
