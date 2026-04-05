#include "util.h"
#include <iostream>
#include <fstream>

//check if file exists
bool fileExists(const std::string& filename){
    std::ifstream file(filename);
    return file.good();
}

//check graphType
bool isValidGraphType(const std::string& graphType){
    return graphType == "DirectedGraph" || graphType == "UndirectedGraph";
}

//check flag 
bool isValidFlag(const std::string& flagStr){
    return flagStr == "0" || flagStr == "1";
}

//validate command line arguments
bool validateArguments(int argc, char* argv[]){
    if (argc != 4){
        std::cerr << "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n";
        return false;
    }

    std::string filename = argv[1];
    std::string graphType = argv[2];
    std::string flagStr = argv[3];

    if(!fileExists(filename) || !isValidGraphType || !isValidFlag(flagStr)){
        std::cerr << "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n";
        return false;
    }
}