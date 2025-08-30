# include "../include/philo.h"

void take_left_and_right_fork(t_data *data, t_philo *philo);

void *routine(void *arg)
{
	t_philo *philo;
	t_data *data;

	philo = (t_philo *)arg;
	data = philo->data;
	//printf("index: %d\n", philo->index);
	//even number sleep first(random time)
	if (philo->index % 2 == 0)
		usleep(10000);
	// while(check_is_dead(philo))
	while (&check_is_dead)
	{
		// odd number take first
		take_left_and_right_fork(data, philo);
		philo_eat(philo);
		// release fork (unlock mutex)

		//sleep
		philo_sleep(philo);

		philo_think(philo);
	}
	return (NULL);
}

void take_left_and_right_fork(t_data *data, t_philo *philo)
{
	//take left fork
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		write(2, "Failed to lock mutex\n", 22);
		return ;
	}
	//print left fork status
	print_status(data, "has taken a fork", philo->index);
	//take right fork
	pthread_mutex_lock(philo->right_fork);
	//print right fork status
	print_status(data, "has taken a fork", philo->index);
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

	print_status(philo->data, "is eating", philo->index);

	ft_usleep(philo->time_to_eat);
	//release the fork
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// create a helper function to sleep in small chunks so it can break early if stop_program is true
void philo_sleep(t_philo *philo)
{
	print_status(philo->data, "is sleeping", philo->index);
	ft_usleep(philo->time_to_sleep);
}

void philo_think(t_philo *philo)
{
	print_status(philo->data, "is thinking", philo->index);
}

// need to create a thread for monitor first
// monitor every philo is dead or not (monitoring thread)
// dead lock is lock when they checking philos is dead or not
// after confirm is dead, unlock, then
// return 1 if philo is dead, 0 if no philo is dead
void *check_is_dead(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->stop_simulation == false)
	{
		i = 0;
		while(i < data->num_of_philo)
		{
			if (data->philos[i].time_to_die <= get_time_stamp() - data->philos[i].last_meal)
			{
				//change the flag is dead
				pthread_mutex_lock(&data->philos[i].dead_lock);
				data->philos[i].is_dead = 1;
				pthread_mutex_unlock(&data->philos[i].dead_lock);
				//print dead status
				print_status(data, "is died", i);
				data-> stop_simulation = true;
				//TODO: EXIT THE WHOLE PROGRAM
				return(NULL);
			}
			i++;
		}
	}
	return(NULL);
}

//monitor every philo has eaten number of times to eat (optional)
// then simulation stops


