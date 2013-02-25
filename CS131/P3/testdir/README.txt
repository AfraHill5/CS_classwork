I implemented my program using two files:
	- a Jpigz class, which reads in the input stream and delegates compression
	  tasks to seperate threads
	- a Deflater_Thread class, which deals with the actual compression.

The implementation is fairly straightforward:

Jpigz first initializes an Executor class with the inputted number of threads as its
given threadpool. This acts as basically a queue for tasks, delegating responsibilities
to the various threads and reusing them when they have completed a task.

Jpigz reads in a file stream, breaking it into 128kb chunks and feeding it into the 
Executor, and also tracking the tasks in a list. When all the stream has been read, it
writes the header, then iterates through the list of submitted tasks and writes each
of the compressed byte arrays returned from the threads. When all these have been written,
it writes the footer.

The dictionary is passed in to the threads as well; if -i is specified, the dictionary
is blank; else it is simply the previous 32kb before the current block.

I wrote in a small modification -- the program will not attempt to use more processes than the
actual number on the machine, because it causes slowdown. If your machine has 4 processes, and
you attempt to run Jpigz -8, it will throw an error.

Generally I found that the byte-for-byte output of my program was identical to that of pigz,
and only slightly different from that of gzip. More processes almost always equaled increased
performance, except for when the file to be compressed was less than 128kb (in which case
it didn't matter.)

I would expect the performance of my multi-threaded implementation to increase compared to 
gzip as the size of the input file increases, simply because parallelism = speed the majority
of the time. However, for smaller files the additional overhead of the various libraries
needed to control the threads will probably cause it to run slower than gzip the majority of
the time, simply the speed gained by parallizing is offset by the speed lost from overhead.

I tested my file with a test file of random gibberish. It had file size 56MB.
My test simply called the three zip functions and created output files.
Then it output whether the unzipped Jpigz.gz file was at all different from the original file.

I first tried the test with baseline Jpigz, no inputted options. This means it used the default
number of processors (16 on the SEASnet servers), and utilized dictionaries:

Attempt 1:
gzip:

real    0m0.825s
user    0m0.717s
sys     0m0.047s

pigz:

real    0m0.132s
user    0m1.573s
sys     0m0.053s

Jpigz:

real    0m0.466s
user    0m2.695s
sys     0m0.641s
-rw-r--r-- 1 north csugrad 135969 Feb  8 19:19 gzip.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:19 Jpigz.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:19 pigz.gz

Attempt 2:
gzip:

real    0m0.790s
user    0m0.766s
sys     0m0.015s

pigz:

real    0m0.163s
user    0m2.077s
sys     0m0.050s

Jpigz:

real    0m0.466s
user    0m2.810s
sys     0m0.594s
-rw-r--r-- 1 north csugrad 135969 Feb  8 19:19 gzip.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:19 Jpigz.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:19 pigz.gz

Attempt 3:
gzip:

real    0m0.741s
user    0m0.714s
sys     0m0.021s

pigz:

real    0m0.138s
user    0m1.555s
sys     0m0.044s

Jpigz:

real    0m0.438s
user    0m2.422s
sys     0m0.617s
-rw-r--r-- 1 north csugrad 135969 Feb  8 19:20 gzip.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:20 Jpigz.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:20 pigz.gz

The generated file was byte-for-byte identical with the generated pigz.gz file, and the unzipped
versions were all identical to the original file as well. Jpigz offered some speed increase
in the "real" category over gzip, but not in the "user" or "sys" categories. It began to approach
the speed of pigz, but was still a ways off. I attribute this to C vs Java -- C is just faster.

My next test was with Jpigz using the -i command, to disable dictionaries:

Attempt 1:
gzip:

real    0m0.794s
user    0m0.778s
sys     0m0.007s

pigz:

real    0m0.177s
user    0m2.069s
sys     0m0.045s

Jpigz:

real    0m0.458s
user    0m2.756s
sys     0m0.278s
-rw-r--r-- 1 north csugrad 135969 Feb  8 19:26 gzip.gz
-rw-r--r-- 1 north csugrad 152320 Feb  8 19:26 Jpigz.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:26 pigz.gz

Attempt 2:
gzip:

real    0m0.788s
user    0m0.770s
sys     0m0.011s

pigz:

real    0m0.166s
user    0m1.969s
sys     0m0.062s

Jpigz:

real    0m0.401s
user    0m2.539s
sys     0m0.478s
-rw-r--r-- 1 north csugrad 135969 Feb  8 19:26 gzip.gz
-rw-r--r-- 1 north csugrad 152320 Feb  8 19:26 Jpigz.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:26 pigz.gz

Attempt 3:
gzip:

real    0m0.794s
user    0m0.778s
sys     0m0.010s

pigz:

real    0m0.164s
user    0m2.024s
sys     0m0.040s

Jpigz:

real    0m0.407s
user    0m2.517s
sys     0m0.506s
-rw-r--r-- 1 north csugrad 135969 Feb  8 19:26 gzip.gz
-rw-r--r-- 1 north csugrad 152320 Feb  8 19:26 Jpigz.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:26 pigz.gz

In this attempt, the Jpigz.gz file was no longer identical to the pigz.gz file,
but it still successfully decompressed into the original file. It was also
slightly larger, which makes sense -- it had to keep track of more symbols
due to the lack of pre-seeding the dictionary.

Also, I found my speed was slightly decreased -- but still faster than gzip.

My final test attempt was for Jpigz with -p 1 enabled. I tried this to see
if the performance degraded. I kept dictionaries in, as I wanted an
apples-to-apples comparison with pigz.

Attempt 1:
gzip:

real    0m0.788s
user    0m0.762s
sys     0m0.017s

pigz:

real    0m0.166s
user    0m1.992s
sys     0m0.050s

Jpigz:

real    0m1.441s
user    0m1.909s
sys     0m0.800s
-rw-r--r-- 1 north csugrad 135969 Feb  8 19:30 gzip.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:30 Jpigz.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:30 pigz.gz

Attempt 2:
gzip:

real    0m0.771s
user    0m0.744s
sys     0m0.020s

pigz:

real    0m0.136s
user    0m1.565s
sys     0m0.047s

Jpigz:

real    0m1.398s
user    0m2.049s
sys     0m0.828s
-rw-r--r-- 1 north csugrad 135969 Feb  8 19:30 gzip.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:30 Jpigz.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:30 pigz.gz

Attempt 3:

gzip:

real    0m0.676s
user    0m0.658s
sys     0m0.011s

pigz:

real    0m0.134s
user    0m1.596s
sys     0m0.045s

Jpigz:

real    0m1.653s
user    0m2.283s
sys     0m0.710s
-rw-r--r-- 1 north csugrad 135969 Feb  8 19:31 gzip.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:31 Jpigz.gz
-rw-r--r-- 1 north csugrad 144633 Feb  8 19:31 pigz.gz

While the output was once again byte-identical with pigz.gz, the speed took a
noticable hit when only using one processor. It is now half as fast as gzip,
which is discouraging, but expected as C > Java when it comes to performance.

Using strace on gzip and pigz indicated that they were spending the majority of
their  time on file reading, while the compression calculations were relatively
quick. My java implementation, on the other hand, had a much larger trace and 
spent a surprising amount of its time moving around memory elements and
reallocating system memory. I think this had to to with the fact that every time
I copied an array in Java, I had to create a new one as arrays are immutable --
and I did a lot of array copying in my implementation.

To speed up my program, perhaps I could try less array copying and possibly
attempt to use some other (mutable) data structure, so writing to buffers and
such would be smoother (overwrites > allocating new memory.) I'm not sure how to 
do this exactly, as everything is an Object in Java.


