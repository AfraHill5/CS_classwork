#include <omp.h>

int main()
{
	int nthreads, tid;
	/* fork a teak of threads */
	#pragma omp parallel private(tid)
   {
	
	/*obtain and print thread id */
	tid = omp_get_thread_num();
	printf("Hello world from thread = %d\n", tid);
	
	/*only master thread does this */
	if (tid == 0)
	{
		nthreads = omp_get_num_threads();
		printf("Number of threads = %d\n", nthreads);
	}

   } /*all threas join master thread and terminate */


	int i, chunk;
	float a[1000], b[1000], c[1000], d[1000];

	for( i = 0; i < 1000; i++)
		a[i] = b[i] = i;
	chunk = 100;
	i = 0;
	#pragma omp parallel shared(a,b,c,chunk) private(i)
	{
	#pragma omp for schedule(dynamic, chunk) nowait
	for (i=0; i < 1000; i++)
	{
		c[i] = a[i] + b[i];
	}
	printf("Thread #%d finished its task with i = %d.\n", omp_get_thread_num(), i);
	}


	#pragma omp parallel shared(a,b,c,chunk) private(i)
	{
		#pragma omp sections nowait
		{
			#pragma omp section
			{
			for (i=0; i<1000; i++)
				c[i] = a[i] + b[i];
			printf("Greetings from thread #%d, in section 1\n", omp_get_thread_num);
			}
			#pragma omp section
			{			
			for(i=0; i<1000; i++)
				d[i] = a[i] + b[i];
			printf("Greetings from thread #%d, in section 2\n", omp_get_thread_num);
			}
		}
	}
	
} 
