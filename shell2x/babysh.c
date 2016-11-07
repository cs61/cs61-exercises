/*
 * sh - shell
 *
 * Usage:
 *     sh
 *     sh -c command
 *
 * This is a stripped down version of the shell we use in CS161.  The goal of
 * today's exercise is to provide practice using the key system calls you'll
 * need to use in Assignment 5.
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <err.h>

/*
 * We are going to limit both the number of arguments that we might pass to a
 * shell command and the total length of those arguments. On most UNIX systems,
 * there is no NARG_MAX. The structure below including a #define brackeded by
 * #ifndef and #endif is how we define things, if we want to define them only if
 * they are not already defined in system include files.
 */
#ifndef NARG_MAX
#define NARG_MAX 1024
#endif

#ifndef ARG_MAX
#define CMDLINE_MAX 4096
#elif ARG_MAX > 4096
#define CMDLINE_MAX 4096
#else
#define CMDLINE_MAX ARG_MAX
#endif

static int dowait(pid_t pid);

/*
 * runcommand --
 * This routine is where you need to use fork and exec to run commands.
 */
static int
run_cmd(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	/*
	 * TODO
	 * If you get here, then you are dealing with a command that
	 * will be implemented by executing a program. You will need 
	 * to do a fork/exec here and then wait for the child.
	 */

	/*
	 * TODO
	 * The parent should wait for its child and then return the exit
	 * status of the process it created. Note that there is a function
	 * you have to fill in called "dowait." Call it here in the parent
	 * process.
	 */
	return (0);
}

/*
 * dowait -- this is a routine you need to write so that a parent can
 * wait for its child to complete. The pid parameter is the pid of the
 * child for whom this process wishes to wait.
 */
static int
dowait(pid_t pid)
{
	(void)pid;
	/*
	 * TODO
	 * Make a process wait on a particular pid, and give proper
	 * error messages and/or warnings on failure. Return exit
	 * status.
	 * NOTE: Read the man page to decide what, if any, flags you want
	 * to user here.
	 */
	return (0);
}

/*
 * chdir
 * This is just an interface to the chdir system call.  This shell has
 * no notion of current working directory (you'll get to implement this
 * for assignment 5), so you need full pathnames here.
 * YOU DO NOT NEED TO CHANGE THIS
 */
static int
cmd_chdir(int argc, char *argv[])
{
	if (argc == 2) {
		if (chdir(argv[1]) != 0) {
			warn("chdir");
			return (1);
		}
		return (0);
	}
	printf("Usage: chdir dir\n");
	return (1);
}

/*
 * cmd_exit: This is the function we use to exit the shell.
 * YOU DO NOT NEED TO CHANGE THIS.
 */
static int
cmd_exit(int argc, char *argv[])
{
	int stat;

	stat = 0;
	if (argc == 2) {
		stat = atoi(argv[1]);
	} else if (argc > 1) {
		printf("Usage: exit [status]\n");
		return (1);
	} 
	exit(stat);

	/*
	 * You never get here, but if you don't put this here,
	 * the compiler will complain.
	 */
	return (0);
}

/*
 * This is a command dispatch table for a few of the builtin functions. Each
 * of them takes an argc and argv.
 *
 * Feel free to add some builtins here if you want.
 */
static struct {
	const char *name;
	int (*func)(int, char **);
} builtins[] = {
	{ "cd",    cmd_chdir },
	{ "chdir", cmd_chdir },
	{ "exit", cmd_exit },
	{ NULL, NULL }
};

/*
 * docommand --
 * We use the C library strtok to break a command line into a set of tokens.
 * If the command line is blank, then we simply return.  Once we have the set
 * of tokens, we check check to see if the command is a builtin -- if so, we
 * run it. If not, we assume that it is a program that we need to fork/exec.
 * YOU DO NOT HAVE TO CHANGE THIS.
 */
static int
docommand(char *buf)
{
	char *args[NARG_MAX + 1];
	int nargs, i;
	char *s;
	int bg;

	bg = 0;
	nargs = 0;

	for (s = strtok(buf, " \t\r\n"); s; s = strtok(NULL, " \t\r\n")) {
		if (nargs >= NARG_MAX) {
			printf("%s: Too many arguments "
			  "(exceeds system limit)\n", args[0]);
			return (1);
		}
		args[nargs++] = s;
	}
	args[nargs] = NULL;

	/* Check for empty line. */
	if (nargs == 0) {
		return (0);
	}

	/* Check for builtin command. */
	for (i = 0; builtins[i].name; i++) {
		if (strcmp(builtins[i].name, args[0]) == 0) {
			return (builtins[i].func(nargs, args));
		}
	}

	/* Not a builtin; run it */
	return run_cmd(nargs, args);
}

/*
 * getcmd --
 * Reads valid characters from the console, filling the buffer.
 * Backspace deletes a character, by moving the position backwards.
 * A newline or carriage return breaks the loop, which terminates
 * the string and returns.
 *
 * If there is an invalid character or a backspace when there is nothing
 * in the buffer, outputs an alert (bell).
 * YOU DO NOT HAVE TO CHANGE THIS.
 */
static void
getcmd(char *buf, size_t len)
{
	size_t pos;
	int ch, done;

    pos = 0;
    done = 0;

	/*
	 * In the absence of a <ctype.h>, assume input is 7-bit ASCII.
	 */

	while (!done) {
		ch = getchar();
		if ((ch == '\b' || ch == 127) && pos > 0) {
			pos--;
		} else if (ch == '\r' || ch == '\n') {
			done = 1;
		} else if (ch >= 32 && ch < 127 && pos < len-1) {
			buf[pos++] = ch;
		}
	}
	buf[pos] = 0;
}

/*
 * interactive --
 * Runs the interactive shell.  This is your basic infinite loop that
 * grabs commands and executes them (printing the exit status if it's not
 * success.)
 * YOU DO NOT HAVE TO CHANGE THIS.
 */
static void
interactive(void)
{
	char buf[CMDLINE_MAX];

	while (1) {
		printf("BabyShell: ");
		getcmd(buf, sizeof(buf));
		/*
         * We don't do anything with the error status
		 * in interactive mode.
		 */
		(void)docommand(buf);
	}
}


/*
 * main --
 * If there are no arguments, run interactively, otherwise, run a program
 * from within the shell, but immediately exit.
 * YOU DO NOT HAVE TO CHANGE THIS.
 */
int
main(int argc, char *argv[])
{
	/*
	 * Allow argc to be 0 in case we're running on a broken kernel,
	 * or one that doesn't set argv when starting the first shell.
	 */
	if (argc == 0 || argc == 1) {
		interactive();
	} else if (argc == 3 && !strcmp(argv[1], "-c")) {
		return (docommand(argv[2]));
	} else {
		errx(1, "Usage: sh [-c command]");
	}

	return (0);
}
