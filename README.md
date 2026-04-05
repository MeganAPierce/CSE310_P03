# Project 3: Graph Navigation System (Dijkstra-Based)

## Overview

This program implements a graph-based navigation system that computes shortest paths using Dijkstra’s Algorithm. It supports both directed and undirected graphs, allows interaction via standard input, and provides efficient shortest path queries.

The system:
- Reads a graph from an input file
- Builds an adjacency list representation
- Computes shortest paths using a min-heap (priority queue)
- Supports interactive commands for querying paths and distances

## Features

- Supports DirectedGraph and UndirectedGraph
- Efficient shortest path computation:
  - Time complexity: O((m + n) log n)
- Uses:
  - Adjacency list for graph storage
  - Min-heap for Dijkstra’s algorithm
  - Stack for path reconstruction
- Input validation and memory management
- No memory leaks (all structures are properly destroyed)

## Data Structures

### Vertex
```c
typedef struct TAG_VERTEX {
    int index;
    COLOR color;
    double key;
    int pi;
    int position;
} VERTEX;
```

- key: shortest distance from source
- pi: predecessor (used for path reconstruction)

### Graph (Adjacency List)
Each vertex has a linked list of outgoing edges:
```c
typedef struct TAG_NODE {
    int u, v;
    double w;
    struct TAG_NODE *next;
} NODE;
```

### Heap (Min-Priority Queue)
Used in Dijkstra’s algorithm:
```c
typedef struct TAG_HEAP {
    int capacity;
    int size;
    pELEMENT *H;
} HEAP;
```

### Stack
Used to reverse paths when printing:
```c
typedef struct TAG_STACK {
    int capacity;
    int top;
    int *S;
} STACK;
```

## Compilation

```bash
g++ -std=c++17 main.cpp util.cpp graph.cpp heap.cpp stack.cpp -o PJ3
```

## Running the Program

```bash
./PJ3 <InputFile> <GraphType> <Flag>
```

### Arguments

| Argument | Description |
|--------|------------|
| InputFile | Graph file |
| GraphType | DirectedGraph or UndirectedGraph |
| Flag | 0 = insert edges at front, 1 = insert at rear |

Example:

```bash
./PJ3 network01.txt DirectedGraph 1
```

## Input File Format

```
n m
edgeIndex u v weight
edgeIndex u v weight
...
```

Example:

```
4 4
1 1 2 1.0
2 1 3 4.0
3 2 3 2.0
4 3 4 1.0
```

## Commands (via stdin)

After launching the program, enter commands interactively:

### PrintADJ
Print adjacency list

Example:
```
ADJ[1]:-->[1 2: 1.00]-->[1 3: 4.00]
```

### SinglePair s t
Compute shortest path from s to t

### SingleSource s
Compute shortest paths from s to all vertices

### PrintPath s t
Print shortest path from s to t

Example:
```
The shortest path from 1 to 3 is:
[1:    0.00]-->[4:    5.00]-->[2:    8.00]-->[3:    9.00].
```

### PrintLength s t
Print shortest path distance

Example:
```
The length of the shortest path from 1 to 3 is:    9.00
```

### Stop
Terminate the program

## Behavior Rules

### Command validity
- Invalid syntax prints:
  ```
  Invalid instruction.
  ```

### Path existence
If no path exists:
```
There is no path from s to t.
```

### Most recent computation rule
PrintPath and PrintLength only produce output if:
- A shortest-path computation has already been performed
- The query matches the most recent computation

Otherwise, no output is produced.

## Algorithm Details

### Dijkstra’s Algorithm

Steps:
1. Initialize all vertices
2. Insert source into min-heap
3. Repeatedly extract minimum
4. Relax edges
5. Update heap via decreaseKey

## Memory Management

All allocated memory is properly freed:
- Graph: destroyGraph()
- Heap: destroyHeap()
- Stack: destroyStack()
- Vertices: deleted in main

## File Structure

| File | Description |
|------|------------|
| main.cpp | Program entry and command processing |
| graph.cpp/h | Graph and Dijkstra implementation |
| heap.cpp/h | Min-heap (priority queue) |
| stack.cpp/h | Stack for path printing |
| util.cpp/h | Argument validation |
| data_structures.h | Core structure definitions |

## Example Run

```
./PJ3 network01.txt DirectedGraph 1

PrintADJ
SinglePair 1 3
PrintPath 1 3
PrintLength 1 3
Stop
```

## Summary

This project demonstrates:
- Graph representation using adjacency lists
- Efficient shortest path computation
- Priority queue usage
- Strict output formatting
- Input validation and memory safety
