#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported reference type
typedef struct ListObj* List;

// Constructors & Destructors
// newList() returns a reference to a new empty List object
List newList(void);

// freeList() frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL);

// Access Functions--------------------------
// length()
// Returns the number of elements in this List
int length(List L);

// index()
// Returns index of the cursor element if defined
// Otherwise returns -1
int index(List L);

// front()
// Returns the value at the front of L
// Pre: length()>0
int front(List L);

// back()
// Returns the back element of L
// Pre: length()>0
int back(List L);

// get()
// Returns cursor element
// Pre: length()>0, index()>=0
int get(List L);

// equals()
// Returns true only if A and B are the same integer sequence
// States of the cursors are irrelevnat in determining equality
int equals(List A, List B);


// Manipulation procedures ----------------------------------------------------
// clear()
// Resets L to the empty state
void clear(List L);

// moveFront()
// If L non-empty, place cursor under front element
// If L empty, do nothing
void moveFront(List L);

// moveBack()
// If L non-empty, place cursor under back element
// If L empty, do nothing
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one step toward front
// If cursor is defined and at front, cursor becomes undefined
// Otherwise do nothing
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one step toward back
// If cursor is defined and at back, cursor becomes undefined
// Otherwise do nothing
void moveNext(List L);

// prepend()
// If L non-empty, insert before front element
void prepend(List L, int data);

// append()
// If L non-empty, insert after back element
void append(List L, int data);

// insertBefore()
// Insert new element before cursor
// Pre: length()>0, index()>=0
void insertBefore(List L, int data);

// insertAfter()
// Insert new element after cursor
// Pre: length()>0, index()>=0
void insertAfter(List L, int data);

// deleteFront()
// Delete the front element
// Pre: length()>0
void deleteFront(List L);

// deleteBack()
// Delete the back element
// Pre: length()>0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined
// Pre: length()>0, index>=0
void delete(List L);                                              


// Other operations -----------------------------------------------------------
// printList()
// Prints a space separated sequence of integers, front on the left, to out file
void printList(FILE* out, List L);

// copy()
// Returns a new List representing the same integer sequence as L
// cursor in new List is undefined, and L remains unchanged
List copyList(List L);

// concatList()
// Optional method that returns the concatenation of elements of List A followed by List B
// cursor in new List is undefined and Lists A and B remain unchanged
List concatList(List A, List B);

#endif
