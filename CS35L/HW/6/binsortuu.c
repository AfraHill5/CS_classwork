#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> /*for stat */


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
    /*Check the size of the file and allocate enough mem for it */
    char* mem;
    size_t numBlocks;
    struct stat s;
    off_t fileSize;
   
    int result = fstat(0, &s);
    if (s.st_size) /*some sort of file was passed in */
    {
        fileSize = s.st_size;
        /* Need to round off block size so N fits */
        int extra = 0;
        if ((fileSize % N) != 0)
            extra = (N - (fileSize % N));
        fileSize += extra;
        numBlocks = fileSize / N; /*should be a whole # here */
        mem = (char*) malloc(fileSize);
        int i;
        for (i = 0; i < fileSize - extra; i++)
        {
            int currChar = getchar();
            mem[i] = (char)currChar;
        }
        /* now fill extras with \0s */
        for (i; i < fileSize; i++)
            mem[i] = '\0';
    }
    else /*Not a regular file so have to allocate mem the old way */
    {
        numBlocks = 1;
    
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
                int currChar = getchar(); 
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
    
    
         /*if the final block is entirely \0s, it is not used and 
         should be removed. */
        if (mem[N * (numBlocks-1)] == '\0')
        {
            numBlocks--;
            mem = (char*) realloc(mem, numBlocks * N * sizeof(char));
        }
    }
    /*slight hack to make memcmp work with qsort (requires N passed in) */
    int my_memcmp(const void* ptr1, const void* ptr2) 
    {
        return memcmp(ptr1, ptr2, N);
    }
    
    qsort(mem, numBlocks, N, my_memcmp);

    /* Now the array is sorted, just remove duplicates and print */
           
    int j, k, isDiff, comps;
    j = 0;
    comps = 0;
    for (j; j < numBlocks * N; j += N)
    {
        comps++;
        isDiff = memcmp(mem+j, mem+j+N, N); /*cmps 2 inline elements */
        if (!isDiff) {;}/*if elements are the same, */
                        /*skips outputting the duplicate */
        else
        {
            write(fileno(stdout), mem+j, N);
        }
    }
    fprintf(stderr, "Number of comparisons: %i\n", comps);
    /*cleanup*/
    free(mem);

    exit(0);
}

