#include <iostream>
#include "SharedObject.h"
#include <chrono>
#include "thread.h"
#include <stack>
#include <thread>
#include "Semaphore.h"
using namespace std;

//defines structure for MyShared (data placed in shared memory)
//MyShared.field to access
struct MyShared{
	int threadID;
	int reportID;
	int elapsedTime;
};
bool endFlag = false;
Semaphore resourceHandler("resourceHandler",1,true);
Semaphore readerHandler("readerHandler",1,true);

void ThreadMain(int t,int d){
	int threadNum = t;
	int delay = d;
	int report = 0;


	std::cout<<"Thread "<<threadNum<<" is running!"<<std::endl;

	auto lastOperationTime = std::chrono::high_resolution_clock::now();

	Shared<MyShared> sharedMemory("sharedMemory", false);

	while(!endFlag){

		resourceHandler.Wait();
		sleep(delay);
		auto currentTime = std::chrono::high_resolution_clock::now();
		sharedMemory -> threadID=threadNum;
		sharedMemory -> reportID=++report;
		sharedMemory -> elapsedTime= std::chrono::duration_cast<std::chrono::seconds>(currentTime-lastOperationTime).count();
		lastOperationTime = currentTime;

		readerHandler.Signal();

	}
	std::cout<<"Thread "<<threadNum<<" is terminating!"<<std::endl;

}

int main(void)
{
	std::cout << "I am a Writer" << std::endl;


	std::string response;
	int n;
	int threadCount=1;

	std::stack<std::thread> threads;

	Shared<MyShared> sharedMemory("sharedMemory", true); //This is the owner of sharedMemory

	while(true){
		//create thread using user input
		std::cout<<"Would you like to create a writer thread?";
		getline(cin, response); cout << endl;

		if(response=="n"){
			endFlag=true;
			break;
		}
		else if(response=="y"){
			std::cout<<"\nWhat is the delay time for the new thread?";
			getline(cin, response); cout << endl;

			try{
				n = stoi(response);
			}catch(const std::invalid_argument& e){
				n=3;
			}

			//create new thread with sleep time of n
			threads.push(thread(ThreadMain,threadCount++,n));
		}
	}
	
	// Signal all threads to exit
	while(!threads.empty()){
		threads.top().join();
		threads.pop();
	}
}

