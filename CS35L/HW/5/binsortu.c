#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


int main(int argc, char** argv) 
{
    if (argc != 2)
    {
        fprintf(stderr, "Please specify N number of bytes to read from stdin.\n");
        exit(1);
    }

    /*Need to convert the string argument to long*/
    long N = strtoul(argv[1], NULL , 10);
    /* Checking again that the cmdline arg is not malformed */
    if (N < 0 || N == ULONG_MAX)
    {
        fprintf(stderr, "Specified number of bytes must be positive.\n");
        exit(1);
    }
  
    size_t numBlocks = 1;
    char* mem;
    
    mem = (char*) malloc(numBlocks * N * sizeof(char));
    if (!mem)
    {
        fprintf(stderr, "Error allocating memory.\n");
        exit(1);
    }

    while(1)
    {
        int i; 
        for (i = 0; i < N; i++)
        {
            char currChar = (char)(fgetc(stdin));
            int loc = ((numBlocks-1) * N) + i;
            if (feof(stdin)) /*end of file */
            {
                for (i; i < N; i++) /*need to fill with 0s */
                {
                    mem[loc] = '\0';
                }
                break;
            }
            else if (ferror(stdin)) /*actual error */
            {
                fprintf(stderr, "File read error.\n");
                exit(1);
            }
            else /*no error, so place character into memory */
            {
                mem[loc] = currChar;
            }
        }
        if (feof(stdin))
            break;
        else
        {
            numBlocks++;
            mem = (char*) realloc(mem, numBlocks * N * sizeof(char));
            if (!mem)
            {
                fprintf(stderr, "Error allocating memory.\n");
                exit(1);
            }
        }
    }
    
    /*if the final block is entirely \0s, it is not used and should
        be removed. */
    if (mem[N * (numBlocks-1)] == '\0')
    {
        numBlocks--;
        mem = (char*) realloc(mem, numBlocks * N * sizeof(char));
    }
    
    /*slight hack to make memcmp work with qsort (requires N passed in) */
    int my_memcmp(const void* ptr1, const void* ptr2) 
    {
        return memcmp(ptr1, ptr2, N);
    }
    
    qsort(mem, numBlocks, N, my_memcmp);

    /* Now the array is sorted, just remove duplicates and print */
           
    int j, k, isDiff;
    j = 0;
    while (j < (numBlocks*N))
    {
        isDiff = memcmp(mem+j, mem+j+N, N); /*cmps 2 inline elements */
        if (!isDiff) /*if elements are the same */
            j = j + N; /*skips outputting the duplicate */
        else
        {
            for (k = 0; k < N; k++)
            {
                printf("%c", mem[j]);
                j++;
            }
        }
    }
    /*cleanup*/
    free(mem);

    exit(0);
}

