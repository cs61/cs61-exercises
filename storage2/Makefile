PROGRAMS = w01_sync w02_syscall w03_stdio 

INCLUDES = -I.

CFLAGS = -g -O3 -Wall -std=gnu11 $(INCLUDES)

all: $(PROGRAMS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<

w01_sync: w01_sync.o
	$(CC) $(CFLAGS) -o $@ w01_sync.o

w02_syscall: w02_syscall.o
	$(CC) $(CFLAGS) -o $@ w02_syscall.o

w03_stdio: w03_stdio.o
	$(CC) $(CFLAGS) -o $@ w03_stdio.o

clean:
	rm -f $(PROGRAMS) *.o core a.out data
