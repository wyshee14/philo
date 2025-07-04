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
	while(check_is_dead(philo))
	{
		//eat
		philo_eat(philo);
		//sleep
		philo_sleep(philo);
		philo_think(philo);
	}
	if (philo->time_to_eat > philo->time_to_die)
		philo->is_dead = 1;
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
	pthread_mutex_lock(philo->right_fork);
	print_status("has taken a fork", philo->index);
	print_status("is eating", philo->index);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void philo_sleep(t_philo *philo)
{
	print_status("is sleeping", philo->index);
	// wait
	usleep(philo->time_to_eat);
}

void philo_think(t_philo *philo)
{
	print_status("is thinking", philo->index);
	// wait
	//usleep(philo->time_to_eat);
}

// need to create a thread for monitor first
// monitor every philo is dead or not (monitoring thread)
// dead lock is lock when they checking philos is dead or not
// after confirm is dead, unlock, then
// return 1 if philo is dead, 0 if no philo is dead
int check_is_dead(t_philo *philo)
{
	int i = 0;
	while (philo[i]->is_dead)
	//if(philo[i])
}

//monitor every philo has eaten number of times to eat
// then simulation stops
