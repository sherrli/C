/* Use an array of linked lists to represent a hash table.
 * Hash table implementation of a Dictionary ADT.
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

const int tableSize=101;

// don't do #define tableSize=101 -> this substitutes the alias every time tableSize appears
// # define does not occupy space in memory


// private types

typedef struct NodeObj{
	char* key;
	char* value;
	struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node;

Node newNode(char* k, char* v){
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->key=k;
	N->value=v;
	N->next=NULL;
	return(N);
}

void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN = NULL;
	}
}


typedef struct DictionaryObj{
	// variable can change so use a actual integer 101?
	Node* table; //[tableSize]; 'variably modified ...'
	// array of pointers to Nodes, each Node in table points to a NodeObj (head of linked list)
	// we do not need to know the length of each linked list
	int numPairs; // non-null values in the table
	// defined at top: a fixed global constant: const int tableSize=101;
}DictionaryObj;


// rotate_left(): used in pre_hash()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift){
	int sizeInBits = 8*sizeof(unsigned int);
	shift = shift & (sizeInBits-1); //bitwise addition operator
	if(shift==0)
		return value; //<< shifts left by 1 bit
	return (value << shift | (value >> (sizeInBits-shift)));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input){
	unsigned int result = 0xBAE86554;
	while(*input){
		result ^= *input++; //^= bitwise exclusive or
		result = rotate_left(result, 5);
	}
	return result;
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
	return pre_hash(key)%tableSize;
}

// helper function findKey()
// returns the Node containing key k
Node findKey(Dictionary D, char* k){
	// use the hash function to get the list it'd be stored in
	int n = hash(k); // index in table that (v, k) lies in
	if( D->table[n]==NULL ){
		return NULL;
	}else{
		Node N = D->table[n]; // N is the reference to Node stored in the nth index of D->table
		while( N!=NULL ){
			// strcmp gives segfault
			if( strcmp( N->key, k )==0 ){
				return N;
			}
			N=N->next;
		}
	}
	return NULL;
}

// helper function deleteAll()
// resets D->table[i] to the empty state by deleting all nodes in the linked list
void deleteAll(Dictionary D, Node H){
	if( H!=NULL ){
		// backward traversal
		deleteAll(D, H->next);
		freeNode(&H);
		D->numPairs--;
	}
}

// helper function printAll()
// print all nodes in the list
void printAll(FILE* out, Node H){
	Node T = H; // a handle on the current Node
	while(T!=NULL){
		fprintf(out, "%s %s\n", T->key, T->value);
		T=T->next; // alters T but not H
	}
}


// public functions

// Dictionary
// Exported reference type
typedef struct DictionaryObj* Dictionary;

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void){
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D!=NULL);
	D->table = calloc(tableSize, sizeof(Node));
	D->numPairs = 0;
	return D;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD){
	if(pD!=NULL && *pD!=NULL){
		// only make table table if not already empty
		if( /*pD->table!=NULL &&*/ (*pD)->table!=NULL){
			makeEmpty(*pD);
			free( (*pD)->table );
		}else{
			free( (*pD)->table );
		}
		// free actual dictionary
		free(*pD);
		*pD=NULL;
	}
}

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
	if(D==NULL){
		fprintf(stderr, "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	return (D->numPairs == 0);
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D){
	if(D==NULL){
		fprintf(stderr, "Dictionary Error: calling size() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	return (D->numPairs);
}

// lookup()
// returns the value v such that (k, v) is in D
// or returns NULL if no such value v exists
// pre: none
char* lookup(Dictionary D, char* k){
        if(D==NULL){
                fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
                exit(EXIT_FAILURE);
        }
	Node N = findKey(D, k);
	return (N==NULL ? NULL : N->value);
}

// insert()
// inserts new (key, value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v){
        if(D==NULL){
                fprintf(stderr, "Dictionary Error: calling insert() on NULL Dictionary reference\n");
                exit(EXIT_FAILURE);
        }
	Node N = findKey(D, k);
	if(N!=NULL){
		fprintf(stderr, "Dictionary Error: cannot insert() duplicate key: \"%s\"\n", k);
		exit(EXIT_FAILURE);
	}

	Node toInsert = newNode(k, v);
	// insert like linked list
	int h = hash(k);
	// special case: insert when table[h] is null
	if( D->table[h]==NULL ){
		D->table[h] = toInsert;
	}else{
		Node T = D->table[h]; // save first item in linked list
		toInsert->next = T;
		(D->table)[h] = toInsert;
	}
	D->numPairs++;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k){
        if(D==NULL){
                fprintf(stderr, "Dictionary Error: calling delete() on NULL Dictionary reference\n");
                exit(EXIT_FAILURE);
        }
	Node N = findKey(D, k);
	if( N==NULL ){
		fprintf(stderr, "Dictionary Error: cannot delete() non-existent key\n");
		exit(EXIT_FAILURE);
	}
// key must exist
	int h = hash(k);
	Node P = D->table[h];
	if(P==N){
		(D->table)[h] = P->next;
		freeNode(&N); // P and N point to the same thing
	//	freeNode(&P);
		D->numPairs--;
		return;
	}
	while( P->next!=N ){
		P=P->next;
	}
	P->next = N->next;
//		N->next=NULL; // splice (k, v) out of list T[h(k)]
	freeNode(&N);
	D->numPairs--;
}

// makeEmpty()
// re-sets D to the empty state
// pre: none
void makeEmpty(Dictionary D){
	if(D==NULL){
		fprintf(stderr, "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = NULL;

        for(int i=0; i<tableSize; i++){
		N = D->table[i]; // ->, [], have precedence over *
                if( N!=NULL ){
			// free all Nodes in the list headed by N
			deleteAll(D, N);
			D->table[i]=NULL; // results in memory leak if not set to NULL
                }
        }
	// D->table=NULL;
	D->numPairs=0;
}

// printDictionary()
// prints a text representation of D to the file pointed to by out
// pre: none
void printDictionary(FILE* out, Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
                exit(EXIT_FAILURE);
        }
	Node N;
	for(int i=0; i<tableSize; i++){
		if( D->table[i]!=NULL ){
			N = D->table[i];
			if( N!=NULL ){
				// print all nodes in the list headed by N
				printAll(out, N);
			}
		}
	}
}

