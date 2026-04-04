This project is the essential part of a navigation system. It reads in either a directed graph or an
undirected graph G with n vertices and m edges from a file specified by the command-line (with
proper arguments). It then takes corresponding actions for given instructions from stdin. 

Besides the Stop instruction, valid instructions include
(i) graph printing instruction (PrintADJ)
(ii) path computation instructions (SinglePair and SingleSource)
(iii) length/path printing instructions (PrintLength and PrintPath)

Both SinglePair and SingleSource path computations should have worst-case time complexity
O((m + n)logn). Path printing should have worst-case time complexity O(n). 
Length printing should have worst-case time complexity O(1). 
Memory should be allocated when needed, and released when it is no longer needed. 

Memory leaks should be avoided.

VALID EXECUTION FORM:

./PJ3 <InputFile> <GraphType> <Flag>

Where:
    -PJ3 is the executable file of the project
    -<InputFile> should be the exact name of the input file
    -<GraphType> should be substitued by either DirectedGraph or UndirectedGraph
    -<Flag> is either 1 or 0

The program will check if the execution is valid. If it is not valid, it will print the following message to stderr and stop:
Usage: ./PJ3 <InputFile> <GraphType> <Flag> 

INSTRUCTIONS:

Stop - on reading stop, the program stops

PrintADJ - program should:
    -print the adjacency lists of the input graph to stdout
    -wait for the next instruction from stdin

SinglePair <source> <destination> - where <source> and <destination> are two integers in the set {1,2,...,n}. This is one of the two path computation instructions. On reading SinglePair the program will:
    -Apply the variant of Dijkstra's algorithm as taught in class to compute the shortest path from <source> to <destination>. 

SingleSource <source> - where <source> in the set {1,2,...,n}. This is the other path computation instruction. On reading the SingleSource instruction the program will:
    -Apply Dijkstra's algorithm to compute shortest paths from <source> to all vertices that are reachable from <source>.

PrintLength <s> <t> - where <s> and <t> are two integers in the set {1,2,...,n}. This is the only length printing instruction. This instruction is valid IF AND ONLY IF <s> is the same as <source> in the most recent path computation instruction and <t> is the same as <destination> in case the most recent path computation instruction is a SinglePair instruction. On reading the instruction the program will:
    -Print the length of the computed path to stdout if the program has computed a shortest <s> to <t> in the most recent path computation. 
    -If the program hasn't computed a shortest <s> to <t> path in the most recent path computation, it will print the following to stdout:
    "There is no path from <s> to <t>."
    -Wait for the next instruction from stdin


PrintPath <s> <t>

Invalid Instruction: Upon reading an invalid instruction the program will write the following to stderr: "Invalid instruction." Then it will wait for the next instruction from stdin.

Example of a valid input file (directed graph with n = 8 and m = 14):
 8 14
 1 1 2 10
 2 1 4 5
 3 2 3 1
 4 2 4 2
 5 3 5 4
 6 4 2 3
 7 4 3 9
 8 4 5 2
 9 5 1 7
10 5 3 6
11 6 3 7
12 6 7 5
13 7 8 3
14 8 6 1
<img width="632" height="232" alt="image" src="https://github.com/user-attachments/assets/393fe03e-3749-4ae1-873b-34247a1d1e27" />

