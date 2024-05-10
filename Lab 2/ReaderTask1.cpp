#include <iostream>
#include "SharedObject.h"

struct MyShared{
	int threadID;
	int reportID;
	int elapsedTime;
};

int main(void)
{
	std::cout << "I am a reader" << std::endl;

	Shared<MyShared> shared("sharedMemory",false);
	while(true){
		//some wait
		sleep(3);

		//print
		std::cout<<"< Thread ID: "<<(shared->threadID)<<" | Report ID: "<<(shared->reportID)<<" | Elapsed Time:"<<(shared->elapsedTime)<<" >"<<std::endl;

	}

}
