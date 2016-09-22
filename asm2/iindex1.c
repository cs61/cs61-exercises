//! -O1
// Demonstrate how well addressing maps onto array access

struct foo {
	int x;
	int y;
};

int iindex(struct foo *fp, int i) {
	return fp[i].y;
}
