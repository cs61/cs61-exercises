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
	if (*infop->msgcount >= TOTAL_MSGS)
		break;
        if (*infop->msgcount % 2 == infop->modval) {
            printf("%s\n", infop->msg);
            c = *infop->msgcount;
	    sched_yield();
            c = c + 1;
            *infop->msgcount = c;
        }
	sched_yield();
    }
    return (NULL);
}

int
main(void)
{
    pthread_t ping_id1, pong_id1;
    pthread_t ping_id2, pong_id2;
    struct pp_thread_info ping, pong;
    int msgcount;

    msgcount = 0;

    ping.msgcount = &msgcount;
    ping.msg = "ping";
    ping.modval = 0;

    pong.msgcount = &msgcount;
    pong.msg = "pong";
    pong.modval = 1;

    // Create the four threads
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

    printf("Main thread exiting\n");
}

