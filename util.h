#ifndef _util_h
#define _util_h 1
#include <string>

enum CommandType{
    CMD_STOP,
    CMD_READ,
    CMD_PRINT_ARRAY,
    CMD_PRINT_HEAP,
    CMD_BUILD_HEAP,
    CMD_INSERT,
    CMD_EXTRACT_MIN,
    CMD_DECREASE_KEY,
    CMD_WRITE,
    CMD_UNKNOWN
};

struct Command{
    CommandType type = CMD_UNKNOWN;
    int index = 0; //for insert and decrease key
    double newKey = 0.0; //for DecreaseKey
    std::string raw; //store original command string for error messages  
};

//parses instructions from stdin, figures out what command user typed
bool readCommand(Command &cmd);

#endif