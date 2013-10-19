#include <stdio.h>
#include <pthread.h>

void *thread_routine(void *data) {
	printf("%s\n", "Print from thread routine");
	return (void *)0;
}

int main() {
	pthread_t thread_1;
	int ret = pthread_create(&thread_1, NULL, thread_routine, NULL);
	return 0;
}