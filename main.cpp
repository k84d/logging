#include <iostream>
#include "logging.h"

int main()
{
	//FILE* pFile = fopen("application.log", "a");
	//Output2FILE::Stream() = pFile;
	LOG(logINFO) << "Log message";
	LOG(logERROR) << "Log message";
	
	return 0;
}
