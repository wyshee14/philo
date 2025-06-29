# include "../include/philo.h"

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    //printf("index: %d\n", philo->index);
    if (philo->index % 2 == 0)
    {
        printf("philo %d is sleeping\n", philo->index);
        // wait
        usleep(philo->time_to_eat);
    }
    //eat
    philo_eat(philo);
	//sleep
	//think
	//printf("Hi I am philo\n");
	return (arg);
}

void philo_eat(t_philo *philo)
{
    if (pthread_mutex_lock(philo->left_fork) != 0)
    {
        write(2, "Failed to lock mutex\n", 22);
        return ;
    }
    print_status("has taken a fork", philo->index);
    pthread_mutex_unlock(philo->left_fork);
}
