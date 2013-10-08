#include <stdio.h>

#define NAME "Hello," "Jackey"

int stoi(char *);

int main() {
	char str[] = "Hello world";
	printf("%s\n", str);

	int num;
	char *str_num = "25932";
	printf("stoi: %d\n", stoi(str_num));
	return 0;
}

int stoi(char *str) {
	int n, i;
	for (i = 0; str[i] >= '0' && str[i] <= '9'; i++) {
		n = n*10 + str[i] - '0';
	}

	return n;
}
