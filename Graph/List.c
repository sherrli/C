#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h"

// private types-----------------

typedef struct NodeObj{
        int data;
        struct NodeObj *prev;
        struct NodeObj *next;
} NodeObj;

// Node: a pointer to NodeObj;
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
        Node front;
        Node back;
        Node cursor;
        int length;
        int cursorIndex;
} ListObj;

// Node constructor
Node newNode(int x){
        Node N = malloc(sizeof(NodeObj));
        assert(N!=NULL);
        N->data = x;
        N->prev = NULL;
        N->next = NULL;
        return(N);
}

// Node destructor
void freeNode(Node* pN){
        if( pN!=NULL && *pN!=NULL ){
                free(*pN);
                *pN = NULL;
        }
}

// List constructor
List newList(void){
        List L = malloc(sizeof(ListObj));
        assert(L!=NULL);
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->length = 0;
        L->cursorIndex = -1;
        return(L);
}

// List destructor
void freeList(List* pL){
        if(pL!=NULL && *pL!=NULL){
                while( length(*pL)!=0 ){
                        deleteBack(*pL);
                }
                free(*pL);
                *pL = NULL;
        }
}


// access functions --------------------------------------------
// length()
// Returns the number of elements in L
int length(List L){
        if( L==NULL){
                printf("List Error: calling length() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        return L->length;
}

// index()
// Returns index of the cursor element if defined
// Otherwise returns -1
int index(List L){
        if( L==NULL ){
                printf("List Error: calling index() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        return L->cursorIndex;
}
// front()
// Returns the value at the front of L
// Pre: length()>0
int front(List L){
        if( L==NULL ){
                printf("List Error: calling front() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if( length(L)<=0 ){
                printf("List Error: calling front() on empty List\n");
                exit(EXIT_FAILURE);
        }
        return L->front->data;
}

// back()
// Returns the back element of L
// Pre: length()>0
int back(List L){
        if( L==NULL ){
                printf("List Error: calling back() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if( length(L)<=0 ){
                printf("List Error: calling back() on empty List\n");
                exit(EXIT_FAILURE);
        }
        return L->back->data;
}

// get()
// Returns cursor element
// Pre: length()>0, index()>=0
int get(List L){
        if( L==NULL ){
                printf("List Error: calling get() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if( length(L)<=0 ){
                printf("List Error: calling get() on empty List\n");
                exit(EXIT_FAILURE);
        }
        if( index(L)<0 ){
                printf("List Error: calling get() on undefined cursor\n");
                exit(EXIT_FAILURE);
        }
        return L->cursor->data;
}
// equals()
// Returns true only if A and B are the same integer sequence
// States of the cursors are irrelevnat in determining equality
int equals(List A, List B){
        if( A==NULL || B==NULL ){
                printf("List Error: calling equals() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        // C has no booleans, let 1=true, 0=false
        Node N = NULL;
        Node M = NULL;
        int eq = 0;
        eq = ( A->length == B->length );
        // no malloc here
        N = A->front;
        M = B->front;
        while( eq && N!=NULL ){
                eq = (N->data==M->data);
                N = N->next;
                M = M->next;
        }
        return eq;
}


// manipulation procedures -----------------------------------------------
// clear()
// Resets L to the empty state
void clear(List L){
        if( L==NULL ){
                printf("List Error: calling clear() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        for(int i=1; i<=L->length; i++){
                Node temp = L->front;
                L->front = L->front->next;
                // no need for temp->next and temp->prev set NULL?
                freeNode(&temp);
        }
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->cursorIndex = -1;
        L->length = 0;
}

// moveFront()
// If L non-empty, place cursor under front element
// If L empty, do nothing
void moveFront(List L){
        if( L==NULL ){
                printf("List Error: calling moveFront() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        // check if L is empty
        if ( L->length>0 ){
                L->cursor = L->front;
                L->cursorIndex = 0;
        }
}

// moveBack()
// If L non-empty, place cursor under back element
// If L empty, do nothing
void moveBack(List L){
        if( L==NULL ){
                printf("List Error: calling moveBack() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        // check if L is empty
        if( L->length>0 ){
                L->cursor = L->back;
                L->cursorIndex = L->length - 1;
        }
}

// movePrev()
// If L non-empty, move cursor one step toward front or make undefined if already at front
// If L empty or cursor undefined, do nothing
void movePrev(List L){
        if( L==NULL ){
                printf("List Error: calling movePrev() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if( L->cursorIndex==0 ){
                L->cursorIndex = -1;
                L->cursor = NULL;
        }else if( L->cursorIndex>0 ){
                L->cursorIndex--;
                L->cursor = L->cursor->prev;
        }
}


// moveNext()
// If L non-empty, move cursor one step toward back or make undefined if already at back
// If L empty or cursor undefined, do nothing
void moveNext(List L){
        if( L==NULL ){
                printf("List Error: calling moveNext() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        // check if cursor is not undefined
        if( L->cursorIndex==L->length-1 ){
                L->cursorIndex = -1;
                L->cursor = NULL;
        }else if( L->cursorIndex>=0 && L->cursorIndex<L->length-1 ){
                L->cursorIndex++;
                L->cursor = L->cursor->next;
        }
}

// prepend()
// If L non-empty, insert before front element
void prepend(List L, int data){
        if( L==NULL ){
                printf("List Error: calling prepend() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        // special case: List is empty
        if( L->length==0 ){
                L->front = newNode(data);
                L->back = L->front;
        }else{
                Node N = newNode(data);
                N->next = L->front;
                L->front->prev = N;
                L->front = N;
                L->cursorIndex++;
        }
        L->length++;
}

// append()
// If L non-empty, insert after back element
void append(List L, int data){
        if( L==NULL ){
                printf("List Error: calling append() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        // special case: List is empty
        if( L->length==0 ){
                L->front = newNode(data);
                L->back = L->front;
        }else{
                Node N = newNode(data);
                N->prev = L->back;
                L->back->next = N;
                L->back = N;
                // cursorIndex does not change
        }
        L->length++;
}

// insertBefore()
// Insert new element before cursor
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
        if( L==NULL ){
                printf("List Error: calling insertBefore() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if( L->length<=0 ){
                printf("List Error: calling insertBefore() on empty List\n");
                exit(EXIT_FAILURE);
        }
        if( L->cursorIndex<0 ){
                printf("List Error: calling insertBefore() on undefined cursor\n");
                exit(EXIT_FAILURE);
        }
        // special case: cursor is under front element
        if( L->cursorIndex==0 ){
                prepend(L, data);
        }else{
                Node N = newNode(data);
                Node temp = L->cursor->prev;
                temp->next = N;
                N->prev = temp;
                N->next = L->cursor;
                L->cursor->prev = N;

                L->length++;
                L->cursorIndex++;
        }
}
// insertAfter()
// Insert new element after cursor
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
        if( L==NULL ){
                printf("List Error: calling insertAfter() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if( L->length<=0 ){
                printf("List Error: calling insertAfter() on empty List\n");
                exit(EXIT_FAILURE);
        }
        if( L->cursorIndex<0 ){
                printf("List Error: calling insertAfter() on undefined cursor\n");
                exit(EXIT_FAILURE);
        }
        // special case: cursor is under back element
        if( L->cursorIndex==L->length-1 ){
                append(L, data);
        }else{
                Node N = newNode(data);
                Node temp = L->cursor->next;
                N->prev = L->cursor;
                L->cursor->next = N;
                N->next = temp;
                temp->prev = N;

                L->length++;
        }
}

// deleteFront()
// Delete the front element
// Pre: length()>0
void deleteFront(List L){
        if( L==NULL ){
                printf("List Error: calling deleteFront() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if( length(L)<=0 ){
                printf("List Error: calling deleteFront() on empty List\n");
                exit(EXIT_FAILURE);
        }
        // special case: List has 1 element
        if( L->length==1 ){
                Node temp = L->front;
                L->front = NULL;
                L->back = NULL;
                L->length = 0;
                L->cursorIndex = -1;
                L->cursor = NULL;
                // freeing temp Node gets rid of what the cursor used to be pointing to
                freeNode(&temp);
        }else{
                if( L->cursorIndex==0 ){
                        L->cursor = NULL;
                        L->cursorIndex = -1;
                }else if( L->cursorIndex>0 ){
                        L->cursorIndex--;
                }
                Node temp = L->front;
                L->front = L->front->next;
                L->front->prev = NULL;
                freeNode(&temp);
                L->length--;
        }
}

// deleteBack()
// Delete the back element
// Pre: length()>0
void deleteBack(List L){
        if( L==NULL ){
                printf("List Error: calling deleteBack() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if( length(L)<=0 ){
                printf("List Error: calling deleteBack() on empty List\n");
                exit(EXIT_FAILURE);
        }
        // special case: List has 1 element
        if( L->length==1 ){
                Node temp = L->front;
                L->front = NULL;
                L->back = NULL;
                L->length = 0;
                L->cursorIndex = -1;
                L->cursor = NULL;
                freeNode(&temp);
        }else{
                // cursorIndex changes only if cursor is pointing to back of List
                if( L->cursorIndex==(L->length)-1 ){
                        L->cursor = NULL;
                        L->cursorIndex = -1;
                }
                Node temp = L->back;
                L->back = L->back->prev;
                L->back->next = NULL;
                freeNode(&temp);
                L->length--;
        }
}

// delete()
// Delete cursor element, making cursor undefined
// Pre: length()>0, index>=0
void delete(List L){
        if( L==NULL ){
                printf("List Error: calling delete() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if( length(L)<=0 ){
                printf("List Error: calling delete() on empty List\n");
                exit(EXIT_FAILURE);
        }
        if( index(L)<0 ){
                printf("List Error: calling delete() on undefined cursor\n");
                exit(EXIT_FAILURE);
        }
        // special cases: cursor is at front or back
        if( L->cursorIndex==0 ){
                deleteFront(L);
        }else if( L->cursorIndex==length(L)-1 ){
                deleteBack(L);
        }else{
                Node temp1 = L->cursor->prev;
                Node temp2 = L->cursor->next;
                temp1->next = temp2;
                temp2->prev = temp1;
                // freeNode points the cursor to NULL and then frees the memory
                freeNode(&(L->cursor));
                L->cursorIndex = -1;
                L->length--;
        }
}

// Other operations -----------------------------------------------------
// printList()
// Prints a space separated sequence of integers, front on the left, to out file
void printList(FILE* out, List L){
        if( L==NULL ){
                printf("List Error: calling printList() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        Node N = NULL;
        for(N=L->front; N!=NULL; N=N->next){
                fprintf(out, "%d ", N->data);
        }
        // freeNode(&N);
        //printf("\n");
}

// copy()
// Returns a new List representing the same integer sequence as L
// cursor in new List is undefined, and L remains unchanged
List copyList(List L){
        List R = newList();
        Node N = L->front;
        while( N!=NULL ){
                append(R, N->data);
                N = N->next;
        }
        return R;
}
