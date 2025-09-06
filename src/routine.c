/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:56 by wshee             #+#    #+#             */
/*   Updated: 2025/09/06 17:40:17 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

static void take_left_and_right_fork(t_data *data, t_philo *philo);
// static void philo_eat(t_philo *philo);
static void philo_sleep(t_philo *philo);
static void philo_think(t_philo *philo);

void *routine(void *arg)
{
	t_philo *philo;
	t_data *data;

	philo = (t_philo *)arg;
	data = philo->data;
	//printf("index: %d\n", philo->index);
	//even number sleep first(random time)
	if (philo->index % 2 == 0)
		ft_usleep(10, data);
	while (!check_stop_simulation(data))
	{
        // if (check_stop_simulation(data))
        //     return (NULL);
		if(data->num_of_philo == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			print_status(data, "has taken a fork", philo->index);
			pthread_mutex_unlock(philo->left_fork);
			ft_usleep(philo->time_to_die, data);
			return (NULL);
		}
		// odd number take first
		take_left_and_right_fork(data, philo);
		// philo_eat(philo);
		// release fork (unlock mutex)

		//sleep
		philo_sleep(philo);

		philo_think(philo);
	}
	return (NULL);
}

static void take_left_and_right_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	if (philo->index % 2 == 0)
	{
		first_fork = philo->left_fork;
		// printf("left fork: %p\n", philo->left_fork);
		// printf("first_fork: %p\n", first_fork);
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	//take first fork
	if (pthread_mutex_lock(first_fork) != 0)
	{
		write(2, "Failed to lock first fork\n", 22);
		return ;
	}
	//print left fork status
	print_status(data, "has taken a fork", philo->index);
	//take second fork
	if (pthread_mutex_lock(second_fork) != 0)
		printf("failed to lock second fork\n");
	//print right fork status
	print_status(data, "has taken a fork", philo->index);

	// need a mutex for the monitor to read it
	// once the mutex unlock the monitor can read the actual time
	if(pthread_mutex_lock(&philo->last_meal_mutex) != 0)
		printf("failed to lock mutex\n");
	philo->last_meal = get_time_stamp();
	if(pthread_mutex_unlock(&philo->last_meal_mutex) != 0)
		printf("failed to unlock mutex\n");

	print_status(philo->data, "is eating", philo->index);

	ft_usleep(philo->time_to_eat, philo->data);
	//release the fork
	if (pthread_mutex_unlock(second_fork) != 0)
		printf("Failed to unlock first fork\n");
	if (pthread_mutex_unlock(first_fork) != 0)
		printf("Failed to unlock second fork\n");

	//update number of meals eaten
	if(pthread_mutex_lock(&philo->last_meal_mutex) != 0)
		printf("failed to lock meals eaten\n");
	philo->meals_eaten++;
	if(pthread_mutex_unlock(&philo->last_meal_mutex) != 0)
		printf("failed to unlock meals eaten\n");
}

// update last meal time, sleep (time to eat)
// mutex lock to write the time start of last meal, then unlock after writing
// print is eating (use sleep to simulate -> because to prevent pc from burning)
// static void philo_eat(t_philo *philo)
// {
// 	// need a mutex for the monitor to read it
// 	// once the mutex unlock the monitor can read the actual time
// 	if(pthread_mutex_lock(&philo->last_meal_mutex) != 0)
// 		printf("failed to lock mutex\n");
// 	philo->last_meal = get_time_stamp();
// 	if(pthread_mutex_unlock(&philo->last_meal_mutex) != 0)
// 		printf("failed to unlock mutex\n");

// 	print_status(philo->data, "is eating", philo->index);

// 	ft_usleep(philo->time_to_eat, philo->data);
// 	//release the fork
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// 	//update number of meals eaten

// 	if(pthread_mutex_lock(&philo->last_meal_mutex) != 0)
// 		printf("failed to lock meals eaten\n");
// 	philo->meals_eaten++;
// 	if(pthread_mutex_unlock(&philo->last_meal_mutex) != 0)
// 		printf("failed to unlock meals eaten\n");
// }

// create a helper function to sleep in small chunks so it can break early if stop_program is true
static void philo_sleep(t_philo *philo)
{
	print_status(philo->data, "is sleeping", philo->index);
	ft_usleep(philo->time_to_sleep, philo->data);
}

static void philo_think(t_philo *philo)
{
	print_status(philo->data, "is thinking", philo->index);
}

bool check_stop_simulation(t_data *data)
{
	bool status;

	pthread_mutex_lock(&data->stop_lock);
	status = data->stop_simulation;
	pthread_mutex_unlock(&data->stop_lock);
	return (status);
}
