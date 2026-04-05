#include "main.h"
#include "util.h"
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
    infile >> n >> m; //read number of vertices and edges
    
    //create a vertex array  
    pVERTEX *V = new pVERTEX[n + 1]; //1-based indexing
    for (int i = 1; i <= n; i++){
        V[i] = new VERTEX; //allocate memory for each vertex
    }
    //create the graph, heap and stack 
    pHEAP heap = createHeap(n);
    pSTACK stack = createStack(n);
    pNODE *ADJ = createGraph(n);

    int edgeIndex, u, v;
    double w;

    //read through the file and build the graph
    for(int i = 0; i < m; i++){
        infile >> edgeIndex >> u >> v >> w;

        if (graphType == "DirectedGraph"){
            addEdge(ADJ, edgeIndex, u, v, w, flag);
        }else if (graphType == "UndirectedGraph"){
            addEdge(ADJ, edgeIndex, u, v, w, flag);
            addEdge(ADJ, edgeIndex, v, u, w, flag);
        }
    }

    infile.close();

    //process stdin instructions
    std::string command;
    while(std::cin >> command){
        if(command == "Stop"){
            break;
        } else if (command == "PrintADJ"){
            printGraph(ADJ,n);
        } else if (command == "SinglePair"){
            int s, t; 
            //check input
            if(!(std::cin >> s >> t)){
                std::cerr << "Invalid instruction.\n";
                std::cin.clear();
                std::string junk;
                std::getline(std::cin, junk);
                continue;
            }

            dijkstra(V, ADJ, n, s, t, heap);

        } else if (command == "SingleSource"){
            int s;
            if(!(std::cin >> s)){
                std::cerr << "Invalid instruction.\n";
                std::cin.clear();
                std::string junk;
                std::getline(std::cin, junk);
                continue;
            }

            dijkstra(V, ADJ, n, s, -1, heap);

        } else if (command == "PrintPath"){
            int s, t;
            if(!(std::cin >> s >> t)){
                std::cerr << "Invalid instruction.\n";
                std::cin.clear();
                std::string junk;
                std::getline(std::cin, junk);
                continue;
            }

            printPath(V, s, t, stack);

        } else if (command == "PrintLength"){
            int s, t;
            if(!(std::cin >> s >> t)){
                std::cerr << "Invalid instruction.\n";
                std::cin.clear();
                std::string junk;
                std::getline(std::cin, junk);
                continue;
            }

            printLength(V, s, t);
            
        } else {
            std::cerr << "Invalid instruction.\n";
        }
    }

    //clean up memory at the end!!
    destroyHeap(heap);
    destroyStack(stack);
    destroyGraph(ADJ, n);
    
    for (int i = 1; i <=n; i++){
        delete V[i];
    }
    delete[] V;


    return 0;
}