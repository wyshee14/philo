/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:20 by wshee             #+#    #+#             */
/*   Updated: 2025/09/07 11:30:28 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_is_dead(t_data *data);
static bool	check_is_full(t_data *data);

// need to create a thread to monitor all philo
// monitor every philo is dead or all philo is full
// stop simulation if either condition is true (stop_lock)
// philo check the flag stop to stop the routine
void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!check_stop_simulation(data))
	{
		if (check_is_dead(data) || check_is_full(data))
		{
			pthread_mutex_lock(&data->stop_lock);
			data->stop_simulation = true;
			pthread_mutex_unlock(&data->stop_lock);
			break ;
		}
	}
	return (NULL);
}

// philo die if it have not eaten from the last meal time from the time to die
// use mutex to read the lastmeal time, as it is accessible by philo
// dead lock is lock when they checking philos is dead or not
// change status of each philo to died if philo is dead, then unlock
static bool	check_is_dead(t_data *data)
{
	int		i;
	bool	is_dead;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->philos[i].last_meal_mutex);
		is_dead = (get_time_stamp() - data->philos[i].last_meal)
			>= data->philos[i].time_to_die;
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		if (is_dead)
		{
			pthread_mutex_lock(&data->philos[i].dead_lock);
			data->philos[i].is_dead = true;
			pthread_mutex_unlock(&data->philos[i].dead_lock);
			print_status(data, "is died", data->philos[i].index, IS_DIED);
			return (true);
		}
		i++;
	}
	return (false);
}

// monitor every philo has eaten number of times to eat (optional)
// then simulation stops
static bool	check_is_full(t_data *data)
{
	int		i;
	bool	is_full;
	t_philo	*philo;

	i = 0;
	philo = data->philos;
	while (i < data->num_of_philo)
	{
		if (philo[i].number_of_times_to_eat == -1)
			return (false);
		pthread_mutex_lock(&philo[i].last_meal_mutex);
		is_full = philo[i].meals_eaten < philo[i].number_of_times_to_eat;
		pthread_mutex_unlock(&philo[i].last_meal_mutex);
		if (is_full)
			return (false);
		i++;
	}
	return (true);
}

bool	check_stop_simulation(t_data *data)
{
	bool	status;

	pthread_mutex_lock(&data->stop_lock);
	status = data->stop_simulation;
	pthread_mutex_unlock(&data->stop_lock);
	return (status);
}
