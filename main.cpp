#include <iostream>
#include "logging.h"

int main()
{
	//FILE* pFile = fopen("application.log", "a");
	//Output2FILE::Stream() = pFile;

#ifndef _WIN32
	std::cout << "Fuck!!!"
#endif

	LOG(logINFO) << "Log message";
	LOG(logERROR) << "Log message";
	
	return 0;
}
