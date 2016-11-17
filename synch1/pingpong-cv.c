// These examples build on/mimic the multi-process ping pong program from
// lecture 18 and the select video. The challenge this time is to synchronize
// two pthreads who need to alternate printing out pings and pongs to the console.
//
// The main program creates four threads (2 pings and 2 pongs). The threads are
// identical except for the messages they print and whether they print on even
// or odd messages.  We add an explicit usleep to trigger the race condition.

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// How many total pings and pongs we'll print
#define TOTAL_MSGS 100

// Structure that we'll use to transmit information
// to the threads.

struct pp_thread_info {
    int *msgcount;      // Keeps track of total number of messages; shared state
    char *msg;
    int modval;
    pthread_mutex_t *mutex;	// Sync access to msgcount
    pthread_cond_t *cv;		// Condition variable to use with mutex
};

// Unsynchronized version -- pings and pongs will not alternate nicely

// Thread function for both pings and pongs; the arg function will be 
// pointer to a struct pp_thread_info and carries all the information
// that the thread needs to process pings and pongs.

void *
pp_thread(void *arg)
{
    struct pp_thread_info *infop;
    int c;

    infop = arg;
    while (1) {
	pthread_mutex_lock(infop->mutex);
	if (*infop->msgcount >= TOTAL_MSGS)
		break;
        while (*infop->msgcount % 2 == infop->modval)
	    pthread_cond_wait(infop->cv, infop->mutex);

	// When we get here, we know that it's time to
	// print our message and that we are holding the
	// mutex.
        printf("%s\n", infop->msg);
        c = *infop->msgcount;
        sched_yield();
        c = c + 1;
        *infop->msgcount = c;

	pthread_cond_broadcast(infop->cv);
        pthread_mutex_unlock(infop->mutex);
        sched_yield();
    }
    pthread_mutex_unlock(infop->mutex);
    return (NULL);
}

int
main(void)
{
    pthread_t ping_id1, pong_id1;
    pthread_t ping_id2, pong_id2;
    pthread_mutex_t mutex;
    pthread_cond_t cv;
    struct pp_thread_info ping, pong;
    int msgcount;

    msgcount = 0;

    if (pthread_mutex_init(&mutex, NULL) != 0) {
	fprintf(stderr, "Mutex init failed: %s\n", strerror(errno));
	exit(1);
    }
    if (pthread_cond_init(&cv, NULL) != 0) {
	fprintf(stderr, "CV init failed: %s\n", strerror(errno));
	exit(1);
    }

    ping.msgcount = &msgcount;
    ping.msg = "ping";
    ping.modval = 0;
    ping.mutex = &mutex;
    ping.cv = &cv;

    pong.msgcount = &msgcount;
    pong.msg = "pong";
    pong.modval = 1;
    pong.mutex = &mutex;
    pong.cv = &cv;

    // Create the two threads
    if ((pthread_create(&ping_id1, NULL, &pp_thread, &ping) != 0) ||
        (pthread_create(&pong_id1, NULL, &pp_thread, &pong) != 0) ||
        (pthread_create(&ping_id2, NULL, &pp_thread, &ping) != 0) ||
        (pthread_create(&pong_id2, NULL, &pp_thread, &pong) != 0)) {
        fprintf(stderr, "pingpong: pthread_create failed %s\n", strerror(errno));
        exit(1);
    }

    // Now wait for threads to exit (Probably should check for errors)
    pthread_join(ping_id1, NULL);
    pthread_join(pong_id1, NULL);
    pthread_join(ping_id2, NULL);
    pthread_join(pong_id2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cv);

    printf("Main thread exiting\n");
}

