#include <stdio.h>

int main(int argc, char *argv) {
	float lower = 0;
	float power = 280;
	float step = 20;

	while (lower<=power) {
		float f;
		f = 5 * (lower - 32) /9;
		printf("%.0f\t%4.1f\n", lower, f);
		lower += step;
	}

	return 0;
}