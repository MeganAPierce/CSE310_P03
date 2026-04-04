#include "heap.h"
#include <iostream>

    
//helper function to swap two nodes in the heap and update their positions  
static void swapHeapNodes(pHEAP pHeap, int i, int j){
    pVERTEX temp = pHeap->H[i];
    pHeap->H[i] = pHeap->H[j];
    pHeap->H[j] = temp;

    pHeap->H[i]->position = i;
    pHeap->H[j]->position = j;
}

//helper function to maintain min-heap property starting from index i downwards
static void heapify(pHEAP pHeap,int i){
    int left = 2 * i;
    int right = 2 * i + 1;
    int smallest = i;

    //check if left child exists and is smaller than current node
    if (left <= pHeap->size && pHeap->H[left]->key < pHeap->H[smallest]->key) {
        smallest = left;
    }
    //check if right child exists and is smaller than current smallest
    if (right <= pHeap->size && pHeap->H[right]->key < pHeap->H[smallest]->key) {
        smallest = right;
    }
    //if smallest is not current node, swap and continue heapifying
    if (smallest != i) {
        swapHeapNodes(pHeap, i, smallest);
        heapify(pHeap, smallest);
    }
}

//creates an empty heap with the specified capacity and returns a pointer to it
pHEAP createHeap(int capacity){
    pHEAP pHeap = new HEAP;
    pHeap->capacity = capacity;
    pHeap->size = 0;
    pHeap->H = new pELEMENT[capacity + 1]; //1-based indexing, so allocate capacity + 1
    return pHeap;
}

//helper function to free memory allocated for the heap
//also sets pointer to nullptr to avoid memory leaks and unused pointers
void destroyHeap(pHEAP pHeap){
    if(pHeap != nullptr){
        delete[] pHeap -> H;
        delete pHeap;
    }
}

//insert a vertex into the heap
void insertElement(pHEAP pHeap, pVERTEX vertex){
    if (pHeap == nullptr || vertex == nullptr) return; //invalid input
    if (pHeap->size >= pHeap->capacity) return; //heap is full, cannot insert
    if(vertex->position != 0) return; //vertex is already in heap, can't insert again

    pHeap->size++;
    pHeap->H[pHeap->size] = vertex;//add a new vertex to the end of the heap
    vertex->position = pHeap->size; //update vertex position

    int current = pHeap->size;
    while(current > 1){
        int parent = current / 2;
        if (pHeap->H[current]->key < pHeap->H[parent]->key){
            swapHeapNodes(pHeap, current, parent);
            current = parent;
        } else {
            break; //heap property is satisfied, stop bubbling up
        }
    }
    
};


pVERTEX extractMin(pHEAP pHeap){
    if (pHeap == nullptr || pHeap->size == 0) return nullptr; //invalid input or empty heap

    pVERTEX minVertex = pHeap->H[1]; //root contains the minimum element
    minVertex->position = 0; //update position to show its no longer in the heap

    //only one element in the heap, just remove it and return
    if(pHeap->size == 1){
        pHeap->H[1] = nullptr;
        pHeap->size = 0;
        return minVertex;
    }

    pHeap->H[1] = pHeap->H[pHeap->size];
    pHeap->H[pHeap->size] = nullptr; //remove last element from heap
    pHeap->size--;
    pHeap->H[1]->position = 1; //update position of new root

    heapify(pHeap, 1); //ensure min-heap property is maintained  
    return minVertex;
};

void decreaseKey(pHEAP pHeap, pVERTEX vertex, double newKey){
    if (pHeap == nullptr || vertex == nullptr) return; //invalid input
    if(vertex->position == 0) return; //vertex not in heap
    if (newKey >= vertex->key) return; //new key is not smaller

    vertex->key = newKey; //update the key value of the vertex
    int current = vertex->position;

    while(current > 1){
        int parent = current / 2;
        if(pHeap->H[current]->key < pHeap->H[parent]->key){
            swapHeapNodes(pHeap, current, parent);
            current = parent;
        }else{
            break; //heap property is satisfied, stop bubbling up
        }
    }

};


void printHeap(pHEAP pHeap){
    //check if heap is empty or null
    if (pHeap == nullptr) {
        std::cerr << "Error: heap is NULL\n";
        return;
    }
    //print heap capacity and size
    std::cout << "Capacity = " << pHeap->capacity << ", size = " << pHeap->size << "\n";
    
    //print each element in the heap array
    for (int k = 1; k <= pHeap->size; k++) {
        pVERTEX v = pHeap->H[k];

        //check if vertex pointer is null before trying to move on
        if (v == nullptr) {
            std::cout << "H[" << k << "] = NULL\n";
        } else {
            std::cout << "H[" << k << "] = " << "Vertex " << v->index << " | key=" << v->key << " | position=" << v->position << "\n";
        }
    }
};