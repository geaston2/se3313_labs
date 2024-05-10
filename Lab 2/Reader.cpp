#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"

struct MyShared{
	int threadID;
	int reportID;
	int elapsedTime;
};

int main(void)
{
	std::cout << "I am a reader" << std::endl;

	Semaphore resourceHandler("resourceHandler",1,false);
	Semaphore readerHandler("readerHandler",1,false);

	Shared<MyShared> shared("sharedMemory",false);
	while(true){
		//some wait
		readerHandler.Wait();
		//print
		std::cout<<"< Thread ID: "<<(shared->threadID)<<" | Report ID: "<<(shared->reportID)<<" | Elapsed Time:"<<(shared->elapsedTime)<<" >"<<std::endl;
		resourceHandler.Signal();
	}

}
