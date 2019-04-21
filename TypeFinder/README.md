In charType.c, I created a pointer on heap memory to keep count of the line number I was reading from.  
It's possible to create the counter on stack memory, but I wanted to practice allocating and freeing heap memory.  

In each iteration of my while loop in main(), I allocated, freed, and re-allocated blocks of memory for my character arrays.  
Note that the blocks of memory I allocated during each loop iteration are already determined to be of length 101.  
I knew the size I'd be allocating in advance, so the array size was independent from the length of the line being read.  

Run 
```
valgrind --leak-check=full -v charType in out
```
for a 'verbose' description of memory leaks and logic errors.
