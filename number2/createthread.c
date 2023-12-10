#include <stdio.h>
#include <pthread.h>
#include <stddef.h>


void *hello_thread(void *arg){
	printf("Thread: Hello, World!! This is Lab4\n");
	return arg;
}

void main(){
	pthread_t tid;
	int status;
	
	status = pthread_create(&tid, NULL, hello_thread, NULL);
	if(status != 0)
		perror("Create thread");
	pthread_exit(NULL);
}
