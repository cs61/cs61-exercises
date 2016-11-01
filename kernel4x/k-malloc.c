// Skeleton code for kernel malloc.
// The file testmalloc.sh will build this in standalone mode. This builds a
// regular program (not a Weensy program) that you can use to test your
// malloc implementation. Rather than allocating OS pages as you will do
// to implement kmalloc, it uses malloc to obtain a page. The test program then
// runs a test program using valgrind, which should report that all memory
// has been freed. You are encouraged to debug your basic malloc/free logic
// this way before building with Weensy OS.

int testmalloc(void);
#define NALLOCS 1000

#ifdef STANDALONE
// Standalone testing
#include <stdlib.h>
int main(int argc, char *argv[]) {
	if (testmalloc())
		exit(1);
}

#define PAGESIZE 4096
#define	GETPAGE	malloc(PAGESIZE)
#define FREEPAGE(P) free(P)

#else
// Put in the kernel
#include "kernel.h"
#include "lib.h"
// Here are the routines that get free pages from the kernel and then
// return them to the kernel
#define	GETPAGE	(void *)page_alloc_unused()
#define FREEPAGE(P) page_unalloc((uintptr_t)P)
#endif

// Kernel malloc: You may limit kmalloc to fail on allocations larger
// than a page; in fact, they can fail on allocations larger than a page
// minus "some overhead".  Use the GETPAGE/FREEPAGE macros so that you can
// build your code either in the shell or in Weensy.
void *kmalloc(size_t sz) {
	return NULL;
}

void kfree(void *v) {
	return;
}

// This is a test program that will test your implementation of kmalloc
// and kfree.
int testmalloc(void) {
	void *allocs[NALLOCS];
	for (int i = 0; i < NALLOCS; i++) {
		allocs[i] = kmalloc(rand() % 64);
		if (allocs[i] == NULL)
			return -1;
	}

	for (int i = 0; i < NALLOCS; i++) {
		int indx = rand() % NALLOCS;
		kfree(allocs[indx]);
		allocs[indx] = kmalloc(rand() % 64);
		if (allocs[indx] == NULL)
			return -1;
	}
	for (int i = 0; i < NALLOCS; i++)
		kfree(allocs[i]);

	return 0;
}
