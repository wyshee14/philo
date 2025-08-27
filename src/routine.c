# include "../include/philo.h"

void take_left_and_right_fork(t_philo *philo);

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	//printf("index: %d\n", philo->index);
	// while(check_is_dead(philo))
	if (philo->index % 2 == 0)
		usleep(100);
	//even number sleep first(random time)
	while (1)
	{
		// odd number take first
		take_left_and_right_fork(philo);
		philo_eat(philo);
		// release fork (unlock mutex)

		//sleep
		philo_sleep(philo);

		philo_think(philo);
	}
	if (philo->time_to_eat > philo->time_to_die)
	philo->is_dead = 1;
	//printf("Hi I am philo\n");
	return (arg);
}

void take_left_and_right_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		write(2, "Failed to lock mutex\n", 22);
		return ;
	}
	print_status("has taken a fork", philo->index);
	pthread_mutex_lock(philo->right_fork);
	print_status("has taken a fork", philo->index);
}

// update last meal time, sleep (time to eat)
// mutex lock to write the time start of last meal, then unlock after writing
// print is eating (use sleep to simulate -> because to prevent pc from burning)
void philo_eat(t_philo *philo)
{

	// need a mutex for the monitor to read it
	// once the mutex unlock the monitor can read the actual time
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_stamp();
	pthread_mutex_unlock(&philo->last_meal_mutex);

	print_status("is eating", philo->index);
	ft_usleep(philo->time_to_eat);
	//release the fork
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// create a helper function to sleep in small chunks so it can break early if stop_program is true
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
// int check_is_dead(t_philo *philo)
// {
// 	int i;

// 	i = 0;
// 	while (philo->data->stop_program = false)
// 	{
		// loop through each philo
// 		if (time_to_die > current_time - last_meal_time)
			// print the statement (X is died)
// 			philo[i] -> data-> stop_program = true;
// 		exit(1);
// 	}
// }

//monitor every philo has eaten number of times to eat
// then simulation stops


