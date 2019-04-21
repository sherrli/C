/* Test client for the Dictionary.c Hash Table ADT. Make sure functions work correctly.
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){
	Dictionary B = newDictionary();
	printDictionary(stdout, B);
	freeDictionary(&B);
	if(B!=NULL) printf("freeDictionary test failed\n");

	/* test isEmpty(), size(), lookup(), insert() */
	Dictionary A = newDictionary();
	if(isEmpty(A) != 1) printf("isEmpty test1 failed\n");
	if(size(A) != 0) printf("size test1 failed\n");
	insert(A, "zero", "foo");
	char* one = lookup(A, "zero");
	if( strcmp(one, "foo")!=0 ) printf("lookup test failed\n");
	printDictionary(stdout, A);

	/* test delete() */
	delete(A, "zero");
	printf("Dictionary now has size %d\n", size(A));

	/* if(size(A) != 1) printf("size test2 failed\n"); */

	char* keyset[] = {"a","b","c","d","e","f","g","h","i","j","k","l"};
	char* valueset[] ={"1","2","3","4","5","6","7","8","9","10","11","12"};
	for(int i=0; i<12; i++) insert(A, keyset[i], valueset[i]);

	/* test isEmpty() */
	if(isEmpty(A)) printf("isEmpty test2 failed\n");
	if(size(A)!=12) printf("size test2 failed\n");

	/* test makeEmpty() */
	makeEmpty(A);
	if(!isEmpty(A)) printf("makeEmpty test failed\n");

	freeDictionary(&A);
	return EXIT_SUCCESS;
}
