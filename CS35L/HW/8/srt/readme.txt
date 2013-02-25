Zach North
603 885 768
HW 8 After-Action Report

I implemented the parallelism aspects of the code by first getting the
number of specified threads to be used, and then splitting up the work
done rendering the pixels among the different threads.

The rendering loop was placed in a seperate function called
ThreadTask, and pthreads were created which invoked this function. 
Since none of the pixels depend on any of the others the work could 
simply be evenly divided among the threads, each one executing a fraction
of the iterations in the loop.

The hardest part of the project was passing in the various data necessary
in the loop to each thread. There was something like 10 different variables
necessary, and the pthread_create function requires all this data to 
be stuffed into a struct, referenced as a null pointer, and then 
dereferenced inside the function. It was a huge hassle and I really
prefer OpenMP's implementation, at least from a user's perspective.

The time outputs indicated that 2-test, 4-test and 8-test ran much faster
than 1-ppm in my modified code. My guess is that these used more threads
and were therefore more "parallel" in my updated code, which explains
the speed increase.
