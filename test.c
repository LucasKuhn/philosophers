#include <pthread.h> // pthread
#include <stdio.h>   // printf
#include <unistd.h>  // sleep


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 

static void	*my_turn(void *arg)
{
	int *i = (int *) arg;
	while (1)
	{
		pthread_mutex_lock(&lock);
		*i = *i + 1;
		usleep(1000 * 1);
		pthread_mutex_unlock(&lock);
	}
}

static void	*display(void *arg)
{
	int *i = (int *) arg;

	while (1)
	{
		printf("Counter is %d\n", *i);
		usleep(1000 * 1000);
	}
}

int	main(int argc, char const *argv[])
{
	pthread_t newthread; 
	pthread_t newthread2; 
	int v = 0; 

	pthread_create(&newthread, NULL, my_turn, &v);
	pthread_create(&newthread2, NULL, my_turn, &v);
	display(&v);
	// pthread_join(newthread, NULL);
	// pthread_join(newthread2, NULL);
	// printf("\rHey 😅");
	// fflush(stdout);
	// usleep(500 * 1000);
	// printf("\rHey 😮‍💨");
	// fflush(stdout);
	// usleep(500 * 1000);
	// printf("\rHey 😎");
	// fflush(stdout);
	// usleep(500 * 1000);
	// printf("\n");
}
