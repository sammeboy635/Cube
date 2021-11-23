#include <iostream>
#include <string>
#include "logger.h"

void error_log(std::string error)
{
    std::cout << error;
    perror("");
}