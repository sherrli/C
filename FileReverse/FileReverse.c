/* Description: Reads in tokens from a file and print them backwards iteratively.
 * Instructions: Takes in two command line arguments naming the input and output files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* stringReverse() directly modifies the char array that s points to */
void stringReverse(char* s){
   int i=0;
   int j=strlen(s)-1;
   while( i<j ){
      char temp=s[i];
      s[i]=s[j];
      s[j]=temp;
      i++;
      j--;
   }
}

int main(int argc, char* argv[]){
   FILE* in; /* asterik is a pointer */
   FILE* out;
   char word[256];

   /* check command line for correct number of arguments */
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE); /* a predefined constant in stdlib.h */
   }

   /* open input file for reading */
   in = fopen(argv[1], "r");
   if( in==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   /* open output file for writing */
   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   /* read words from input file, print on separate lines to output file */
   while( fscanf(in, " %s", word) != EOF ){
      stringReverse(word);
      fprintf(out, "%s\n", word);
   }

   fclose(in);
   fclose(out);

   return(EXIT_SUCCESS);
}
