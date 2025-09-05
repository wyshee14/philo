/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:20 by wshee             #+#    #+#             */
/*   Updated: 2025/09/06 01:10:36 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

static bool check_is_dead(t_data *data);
static bool check_is_full(t_data *data);

// need to create a thread for monitor first
// monitor every philo is dead or not (monitoring thread)
// dead lock is lock when they checking philos is dead or not
// after confirm is dead, unlock, then
// return 1 if philo is dead, 0 if no philo is dead
void *monitoring(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->stop_simulation == false)
	{
		i = 0;
		while(i < data->num_of_philo)
		{
			// printf("time_to_die[%d]: %lu\n", data->philos[i].index, data->philos[i].time_to_die);
			// printf("last_meal_time[%d]: %lu\n", data->philos[i].index, data->philos[i].last_meal);
			// printf("time_now: %lu\n", get_time_stamp());
			if (check_is_dead(data) || check_is_full(data))
			{
				//if one of the condition above is true, stop simulation
				pthread_mutex_lock(&data->stop_lock);
				data-> stop_simulation = true;
				pthread_mutex_unlock(&data->stop_lock);
				return(NULL);
			}
			i++;
		}
	}
	return (NULL);
}

static bool check_is_dead(t_data *data)
{
	int i;

	i = 0;
	while(i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->philos[i].last_meal_mutex);
		if (data->philos[i].time_to_die <= get_time_stamp() - data->philos[i].last_meal)
		{
			//change the flag is dead
			pthread_mutex_lock(&data->philos[i].dead_lock);
			data->philos[i].is_dead = true;
			pthread_mutex_unlock(&data->philos[i].dead_lock);
			//print dead status
			print_status(data, "is died", data->philos[i].index);
			pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
			return (true);
		}
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		i++;
	}
	return(false);
}

// monitor every philo has eaten number of times to eat (optional)
// then simulation stops
static bool check_is_full(t_data *data)
{
	int i;
	bool is_full;

	i = 0;
	while(i < data->num_of_philo)
	{
		if(data->philos[i].number_of_times_to_eat == -1)
			return (false);
		pthread_mutex_lock(&data->philos[i].last_meal_mutex);
		is_full = (data->philos[i].meals_eaten < data->philos[i].number_of_times_to_eat);
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		if (!is_full)
			return (false);
		i++;
	}
	return(true);
}
