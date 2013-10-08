#include <stdio.h>

#define NUM 50

int main() {
	int digit[10];
	int c;
	for (int i = 0; i < 10; i++) {
		digit[i] = 0;
	}
	while ( (c = getchar()) != EOF) {
		if (c >= '0' && c <= '9') {
			++digit[c - '0'];
		}
	}

	for (int i = 0; i < 10; i++) printf("\t%d ", digit[i]);
	printf("\n");

	return 0;
}