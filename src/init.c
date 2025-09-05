/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:37:15 by wshee             #+#    #+#             */
/*   Updated: 2025/09/05 17:07:43 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void init_data(t_data *data, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->num_of_philo = ft_atoi(av[1]);
	// printf("num of philo: %d\n", data->num_of_philo);
	if (data->num_of_philo > 200)
		return ;
	data->philos = (t_philo *)malloc(data->num_of_philo * sizeof(t_philo));
	memset(data->philos, 0, sizeof(t_philo));
	data->forks = (pthread_mutex_t *)malloc(data->num_of_philo * sizeof(pthread_mutex_t));
	memset(data->forks, 0, sizeof(pthread_mutex_t));
	if (pthread_mutex_init(&data->write_status, NULL) != 0)
	{
		write(2, "Failed to init mutex\n", 22);
		return ;
	}
	if (pthread_mutex_init(&data->stop_lock, NULL) != 0)
	{
		write(2, "Failed to init mutex\n", 22);
		return ;
	}
	// printf("write_lock: %p\n", &data->write_status);
}

//pthread_create return 0 if success
void init_threads(t_data *data)
{
	// pthread_t philo_thread[philo->num_of_philo];
	// pthread_mutex_t mutex;
	int i;
	// size_t time_start;

	i = 0;
	data->time_start_simulation = get_time_stamp();
	// pthread_mutex_init(&mutex, NULL);
	while(i < data->num_of_philo)
	{
		data->philos[i].last_meal = get_time_stamp();
		if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
		{
			write(2, "Failed to create thread\n", 25);
			return ;
		}
		// printf("Thread %d has started\n", i);
		// print_status("start", i + 1);
		i++;
	}
	init_monitor(data);
	i = 0;
	while(i < data->num_of_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			write(2, "Failed to join thread\n", 23);
			return ;
		}
		// printf("Thread %d finished execution\n", i);
		// print_status("end", i);
		i++;
	}
	// pthread_mutex_destroy(&mutex);
}

void init_philo(t_data *data, char **av)
{
	int i;

	i = 0;
	// printf("num of philo: %d\n", data->num_of_philo);
	while (i < data->num_of_philo)
	{
		data->philos[i].index = i + 1;
		// printf("index: %d\n", data->philos[i].index);
		data->philos[i].time_to_die = ft_atoi(av[2]);
		//printf("time to die: %d\n", data->philos[i].time_to_die);
		data->philos[i].time_to_eat = ft_atoi(av[3]);
		// printf("time to eat: %d\n", data->philos[i].time_to_eat);
		data->philos[i].time_to_sleep = ft_atoi(av[4]);
		// printf("time to sleep: %d\n", data->philos[i].time_to_sleep);
		if (!av[5])
			data->philos[i].number_of_times_to_eat = -1;
		else
			data->philos[i].number_of_times_to_eat = ft_atoi(av[5]);
		//printf("number of times to eat: %d\n", data->philos->number_of_times_to_eat);
		data->philos[i].left_fork = &data->forks[i];
		// printf("forks[%i]: %p\n", data->num_of_philo, &data->forks[data->num_of_philo]);
		if (i == 0)
			data->philos[i].right_fork = &data->forks[data->num_of_philo - 1];
		else
			data->philos[i].right_fork = &data->forks[i - 1];
		pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL);
		pthread_mutex_init(&data->philos[i].dead_lock, NULL);
		data->philos[i].last_meal = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].is_dead = false;
		// data->philos[i].num_of_philo = data->num_of_philo;
		data->philos[i].data = data;
		i++;
	}
}

void init_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(2, "Failed to init mutex\n", 22);
			return ;
		}
		i++;
	}
}

// monitoring thread monitor all philo status is dead or not
void init_monitor(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, &monitoring, data) != 0)
	{
		write(2, "Failed to create monitor thread.", 33);
		return ;
	}
	if (pthread_join(data->monitor, NULL) != 0)
	{
		write(2, "Failed to join thread.", 23);
		return ;
	}
}
