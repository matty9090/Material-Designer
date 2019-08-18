#include "Log.hpp"
#include <iostream>

void FLog::Log(std::string msg, ELogType logLevel)
{
#ifdef _DEBUG
    std::cout << "[" << LogTypes[logLevel] << "] " << msg << std::endl;
#else
    if(logLevel != Verbose)
        std::cout << "[" << LogTypes[logLevel] << "] " << msg << std::endl;
#endif
}
