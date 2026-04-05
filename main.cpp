#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "main.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]){

    //validate command-line arguments
    if(!validateArguments(argc, argv)){
        return 1;
    }

    std::string filename = argv[1];
    std::string graphType = argv[2];
    int flag = std::stoi(argv[3]);
    
    //create the graph, heap and stack 
    
    //process stdin instructions
    std:: string command;
    while(std::cin >> command){
        if(command == "Stop"){
            break;
        } else if (command == "PrintADJ"){

        } else if (command == "SinglePair"){

        } else if (command == "SingleSource"){

        } else if (command == "PrintPath"){

        } else if (command == "PrintLength"){

        } else {
            std::cerr << "Invalid instruction.\n";
        }
    }
    //clean up memory at the end!!

    return 0;
}