/* The program reads characters from a file and outputs the number of occurrences of certain types of characters to another file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_STRING_LENGTH 100

/* Prototype of function extract_chars
 * (usually written in a .h file -- TA Shubhangi)
 */
void extract_chars(char* s, char* a, char* d, char* p, char* w);

int main(int argc, char* argv[]){
/* argc are the cmd line arguments
 * argv[] is the character array
 */
	FILE *in;
	FILE *out;
	char* line; /*string holding input line*/
	char* alpha;
	char* numer;
	char* punct;
	char* space;
	

	if(argc != 3){
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* open input file for reading */
	if( (in=fopen(argv[1], "r")) == NULL ){
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* open output file for writing */
	if( (out=fopen(argv[2], "w")) == NULL){
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	line = calloc(MAX_STRING_LENGTH+1, sizeof(char));
	/* ensure that calloc found a free block of sufficient size */
	assert(line!=NULL);
	
	/* note: can use int counter instead.
	 * counter can be made into stack memory but I wanted to experiment with pointers */
	int* counter;
	counter = malloc(sizeof(int));
	assert(counter!=NULL);
	*counter = 1;

	/* loop through every line in the file "in" */
	while(fgets(line, MAX_STRING_LENGTH, in) != NULL){
		/* create new arrays on each iteration */
		/* note: Professor Tantalo says it is unnecessary to use heap memory
     * if you're going to keep allocating the same amount of large memory each time.
     */
		alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char));
		numer = calloc(MAX_STRING_LENGTH+1, sizeof(char));
    punct = calloc(MAX_STRING_LENGTH+1, sizeof(char));
	  space = calloc(MAX_STRING_LENGTH+1, sizeof(char));
		/* ensure calloc allocated memory successfully */
		assert(alpha!=NULL && numer!=NULL && punct!=NULL && space!=NULL);
		/* alter line, alpha, numer, punct, space arrays in function extract_chars */
		extract_chars(line, alpha, numer, punct, space);
		
		int* a = malloc(sizeof(int));
		int* n = malloc(sizeof(int));
		int* p = malloc(sizeof(int));
		int* s = malloc(sizeof(int));
		assert(a!=NULL && n!=NULL && p!=NULL && s!=NULL);
/* test
		printf("line: %s\n ", line);
		printf("alpha: %s\n ", alpha);
		printf("numer: %s\n ", numer);
		printf("punct: %s\n ", punct);
		printf("space: %s\n\n", space);	
end test */
		*a = strlen(alpha);
		*n = strlen(numer);
		*p = strlen(punct);
		*s = strlen(space);	
	
		fprintf(out, "line %d contains:\n", *counter);

		if(*a==1){
			fprintf(out, "%d alphabetic character: %s\n", *a, alpha);
		}else{
			fprintf(out, "%d alphabetic characters: %s\n", *a, alpha);
		}

		if(*n==1){
			fprintf(out, "%d numeric character: %s\n", *n, numer);
		}else{
			fprintf(out, "%d numeric characters: %s\n", *n, numer);
		}

    if(*p==1){
      fprintf(out, "%d punctuation character: %s\n", *p, punct);
    }else{
      fprintf(out, "%d punctuation characters: %s\n", *p, punct);
		}

    if(*s==1){
      fprintf(out, "%d whitespace character: %s\n", *s, space);
    }else{
      fprintf(out, "%d whitespace characters: %s\n", *s, space);
		}

		/* increment line number */
		(*counter)++;

		free(a);
		free(n);
		free(p);
		free(s);
		free(alpha);
	  free(numer);
		free(punct);
		free(space);

	}

	free(counter);
	free(line);

	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}

// define function extract_chars
void extract_chars(char* line, char* alpha, char* digit, char* punct, char* whitespace){
	int* lineCount = malloc(sizeof(int));
	int* alphaCount = malloc(sizeof(int));
	int* digitCount = malloc(sizeof(int));
	int* punctCount = malloc(sizeof(int));
	int* whitespaceCount = malloc(sizeof(int));

	assert(lineCount!=NULL && alphaCount!=NULL && digitCount!=NULL && punctCount!=NULL && whitespaceCount!=NULL);

	*lineCount=0;
	*alphaCount=0;
	*digitCount=0;
	*punctCount=0;
	*whitespaceCount=0;

	while(line[*lineCount] != '\0' && *lineCount < MAX_STRING_LENGTH){

		// test
		// printf("line at i is: %c\n", line[*lineCount]);
		// end test

		if( isalpha( line[*lineCount] ) ){
			alpha[ (*alphaCount)++ ] = line[*lineCount];
		}else if( isdigit( line[*lineCount] ) ){
			digit[ (*digitCount)++ ] = line[*lineCount];
		}else if( ispunct( line[*lineCount] ) ){
			punct[ (*punctCount)++ ] = line[*lineCount];
			// test by printing the line at *lineCount as a character %c
			// printf("punct=%c i=%d j=%d\n", line[*lineCount], *lineCount, *punctCount);
		}else if( isspace( line[*lineCount] ) ){
			whitespace[ (*whitespaceCount)++ ] = line[*lineCount];
		}
		(*lineCount)++;
	}

	free(lineCount);
	free(alphaCount);
	free(digitCount);
	free(punctCount);
	free(whitespaceCount);
}
