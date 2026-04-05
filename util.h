#ifndef UTIL_H
#define UTIL_H 
#include<string>

bool validateArguments(int argc, char* argv[]);
bool isValidGraphType(const std::string& graphType);
bool isValidFlag(const std::string& flagStr);
bool fileExists(const std::string& filename);

#endif