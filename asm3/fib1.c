//! -O1
unsigned long fib(unsigned long n) {
	if (n < 2)
		return n;
	return fib(n - 1) + fib(n - 2);
}
