#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "main.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){

    //validate command-line arguments
    if(!validateArguments(argc, argv)){
        return 1;
    }

    std::string filename = argv[1];
    std::string graphType = argv[2];
    int flag = std::stoi(argv[3]);
    
    //read the graph from the input file
    int n, m;
    std::ifstream infile(filename);
    
    if(!infile){
        std::cerr << "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n";
        return 1;
    }
    if (!infile.is_open()){
        std::cerr << "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n";
        return 1;
    }
    infile >> n >> m; //read number of vertices and edges
    
    //create the graph, heap and stack 
    pVERTEX *V = new pVERTEX[n + 1]; //1-based indexing
    for (int i = 0; i <= n; i++){
        V[i] = new VERTEX; //allocate memory for each vertex
    }

    pHEAP heap = createHeap(n);
    pSTACK stack = createStack(n);
    pNODE *ADJ = createGraph(n);


    //process stdin instructions
    std:: string command;
    while(std::cin >> command){
        if(command == "Stop"){
            break;
        } else if (command == "PrintADJ"){
            printGraph(ADJ,n);
        } else if (command == "SinglePair"){
            int s, t; 
            std::cin >> s >> t;
            dijkstra(V, ADJ, n, s, t, heap);
        } else if (command == "SingleSource"){
            int s;
            std::cin >> s;
            dijkstra(V, ADJ, n, s, -1, heap);
        } else if (command == "PrintPath"){
            int s, t;
            std::cin >> s >> t;
            printPath(V, s, t, stack);
        } else if (command == "PrintLength"){
            int s, t;
            std::cin >> s >> t;
            printLength(V, s, t);
        } else {
            std::cerr << "Invalid instruction.\n";
        }
    }

    //clean up memory at the end!!

    return 0;
}