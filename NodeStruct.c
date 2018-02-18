#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct NodeObj{
    int item;
    struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node; // Node is the pointer to a NodeObj

// constructor
Node newNode(int x){
    Node N = malloc(sizeof(NodeObj)); // N is of type Node, which means a pointer to a NodeObj
    assert(N!=NULL);
    N->item=x;
    N->next=NULL;
    return(N);
}

// destructor
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL){
        free(*pN);
        *pN=NULL;
    }
}

int main() {
   Node N = newNode(5);
   printf("Node N has value %d", N->item);
   
   /*freeNode(N); incompatible pointer type: expected NodeObj** but got NodeObj* */
   freeNode(&N); /* &N works when passed to freeNode(), but *N and N do not */
}
