# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

int x = 0;
pthread_mutex_t mutex;

void *routine_123()
{
	// printf("thread: %lu\n", pthread_self());
	// printf("pid: %d\n", getpid());
	for (long i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		x++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main()
{
	//unsigned long integer type
	pthread_t thread[4];
	struct timeval tv;
	// struct timezone *tz;

	gettimeofday(&tv, NULL);
	printf("Time now is %lu second and %lu microsecond\n", tv.tv_sec, tv.tv_usec);

	//initialize mutex lock
	pthread_mutex_init(&mutex, NULL);

	// starts a new thread in the calling process
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(&thread[i], NULL, routine_123, NULL) != 0)
		{
			perror("Failed to create thread\n");
			return(1);
		}
		printf("Thread %d has started\n", i);
	}

	// wait for the thread to finish
	// coimpile with -pthread
	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
			return(2);
		}
		printf("Thread %d finished execution\n", i);
	}

	//destroy mutex lock
	pthread_mutex_destroy(&mutex);

	// printf("x is %d\n", x);
	return (0);
}
