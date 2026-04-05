#include "main.h"
#include "util.h"
#include <iostream>
#include <fstream>

//helper function to check validity of provided vertex
//not needed in main.h because it isn't being called anywhere else but main.cpp
//static because it tells compiler "this function is only visible inside this file"
static bool isValidVertex(int v, int n){
    return v >= 1 && v <= n;
}

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

    /*Helpers to track:
    * if shortest-path computation has happened
    * most recent source
    * most recent destination
    * if last computation was SingleSource
    */
    bool hasComputed = false;
    int lastSource = -1;
    int lastDestination = -1;
    bool lastWasSingleSource = false;


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

            if(!isValidVertex(s, n) || !isValidVertex(t, n)){
                std::cerr << "Invalid instruction.\n";
                continue;
            }

            dijkstra(V, ADJ, n, s, t, heap);
            lastSource = s;
            lastDestination = t;
            lastWasSingleSource = false;
            hasComputed = true;

        } else if (command == "SingleSource"){
            int s;
            if(!(std::cin >> s)){
                std::cerr << "Invalid instruction.\n";
                std::cin.clear();
                std::string junk;
                std::getline(std::cin, junk);
                continue;
            }

            if(!isValidVertex(s,n)){
                std::cerr << "Invalid instruction.\n";
                continue;
            }

            dijkstra(V, ADJ, n, s, -1, heap);
            lastSource = s;
            lastDestination = -1;
            lastWasSingleSource = true;
            hasComputed = true;

        } else if (command == "PrintPath"){
            int s, t;
            if(!(std::cin >> s >> t)){
                std::cerr << "Invalid instruction.\n";
                std::cin.clear();
                std::string junk;
                std::getline(std::cin, junk);
                continue;
            }

            if(!isValidVertex(s,n) || !isValidVertex(t, n)){
                std::cerr << "Invalid instruction.\n";
                continue;                
            }

            if(!hasComputed || s != lastSource || (!lastWasSingleSource && t != lastDestination)){
                std::cout << "There is no path from " << s << " to " << t << ".\n";
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

            if(!isValidVertex(s,n) || !isValidVertex(t, n)){
                std::cerr << "Invalid instruction.\n";
                continue; 
            }

            if(!hasComputed || s != lastSource || (!lastWasSingleSource && t != lastDestination)){
                std::cout << "There is no path from " << s << " to " << t << ".\n";
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