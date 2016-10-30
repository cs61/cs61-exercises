#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	while (1)
		(void)fork();
}
