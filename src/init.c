/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:37:15 by wshee             #+#    #+#             */
/*   Updated: 2025/09/07 11:29:01 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_join_thread(t_data *data);

int	init_data(t_data *data, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->num_of_philo = ft_atoi(av[1]);
	data->philos = (t_philo *)malloc(data->num_of_philo * sizeof(t_philo));
	memset(data->philos, 0, sizeof(t_philo));
	data->forks = (pthread_mutex_t *)malloc(data->num_of_philo
			* sizeof(pthread_mutex_t));
	memset(data->forks, 0, sizeof(pthread_mutex_t));
	if (ft_init_mutex(&data->write_status))
		return (1);
	if (ft_init_mutex(&data->stop_lock))
		return (1);
	data->stop_simulation = false;
	return (0);
}

// create philo and monitor thread tgt
// pthread_join is wait the thread to finish
// join all philo thread, then join monitor
// monitor must wait until all philo finish
// record the time start simulation to get make simulation starts from 0
// init last meal to let monitor check from the start
int	init_threads(t_data *data)
{
	int	i;

	data->time_start_simulation = get_time_stamp();
	i = 0;
	while (i < data->num_of_philo)
	{
		data->philos[i].last_meal = get_time_stamp();
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
		{
			write(2, "Failed to create philo thread\n", 31);
			return (1);
		}
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitoring, data) != 0)
	{
		write(2, "Failed to create monitor thread.", 33);
		return (1);
	}
	ft_join_thread(data);
	return (0);
}

static int	ft_join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			write(2, "Failed to join philo thread\n", 29);
			return (1);
		}
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
	{
		write(2, "Failed to join monitor thread\n", 31);
		return (1);
	}
	return (0);
}

int	init_philo(t_data *data, char **av)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		data->philos[i].index = i + 1;
		data->philos[i].time_to_die = ft_atoi(av[2]);
		data->philos[i].time_to_eat = ft_atoi(av[3]);
		data->philos[i].time_to_sleep = ft_atoi(av[4]);
		if (!av[5])
			data->philos[i].number_of_times_to_eat = -1;
		else
			data->philos[i].number_of_times_to_eat = ft_atoi(av[5]);
		assign_forks(data, i);
		if (ft_init_mutex(&data->philos[i].last_meal_mutex))
			return (1);
		if (ft_init_mutex(&data->philos[i].dead_lock))
			return (1);
		data->philos[i].is_dead = false;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (ft_init_mutex(&data->forks[i]))
			return (1);
		i++;
	}
	return (0);
}
