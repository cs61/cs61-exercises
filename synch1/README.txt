pingpong:   Unsynchronized version of pingpong pthread program with two threads
	    of each type (too easy to get behavior correct unsynchronized with
	    only one thread of each type.

pingpong-mutex:
	    Synchronize this using a mutex.

pingpong-cv:
	    Synchronize this using a mutex and CV.

check.awk -- awk script to detect if your ping pong output is correct.
