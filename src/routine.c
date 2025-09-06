/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:56 by wshee             #+#    #+#             */
/*   Updated: 2025/09/07 03:01:57 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	handle_single_philo(t_data *data, t_philo *philo);
static void	take_and_release_fork(t_data *data, t_philo *philo);
static void	philo_eat(t_philo *philo);
static void	philo_sleep_and_think(t_philo *philo);

// let even number sleep first(random time) to avoid dead lock
// odd number take fork and eat first
void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->index % 2 == 0)
		ft_usleep(20, data);
	while (!check_stop_simulation(data))
	{
		if (data->num_of_philo == 1)
		{
			handle_single_philo(data, philo);
			return (NULL);
		}
		take_and_release_fork(data, philo);
		philo_sleep_and_think(philo);
	}
	return (NULL);
}

// specially handle for single philo to prevent dead lock
// where only one fork is taken and waiting for the second fork to take
// causing the program keep on waiting
static void	handle_single_philo(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(data, "has taken a fork", philo->index, TAKEN_A_FORK);
	pthread_mutex_unlock(philo->left_fork);
	ft_usleep(philo->time_to_die, data);
}

// assign even and odd number to take diff sequence to prevent dead lock
// philo can start to eat only when they taken two forks
// release the fork in the sequence of which fork is taken last 
// (good practice in stack order)
// it doesnt affect the program on the sequence of unlock after experiment
static void	take_and_release_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	bool			stop;

	if (philo->index % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print_status(data, "has taken a fork", philo->index, TAKEN_A_FORK);
	pthread_mutex_lock(second_fork);
	print_status(data, "has taken a fork", philo->index, TAKEN_A_FORK);
	stop = check_stop_simulation(data);
	if (!stop)
		philo_eat(philo);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

// update last meal time when the philo start eating
// need a mutex for the monitor to read it
// mutex lock to write the time start of last meal, then unlock after writing
// once the mutex unlock the monitor can read the actual time
// print is eating (use sleep to simulate -> because to prevent pc from burning)
// update number of meals eaten (using mutex so that monitor can read)
static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_stamp();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	print_status(philo->data, "is eating", philo->index, IS_EATING);
	ft_usleep(philo->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

static void	philo_sleep_and_think(t_philo *philo)
{
	print_status(philo->data, "is sleeping", philo->index, IS_SLEEPING);
	ft_usleep(philo->time_to_sleep, philo->data);
	print_status(philo->data, "is thinking", philo->index, IS_THINKING);
}
