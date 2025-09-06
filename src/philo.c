/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:15:54 by wshee             #+#    #+#             */
/*   Updated: 2025/09/06 19:16:34 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
# include "../include/philo.h"

int main (int ac, char **av)
{
	t_data data;
	// t_philo *philo;

	// philo = NULL;
	if (ac < 5 || ac > 6)
	{
		printf("argument must be more than 5\n");
		return (1);
	}
	if(check_invalid_input(av))
		return (1);
	init_data(&data, av);
	init_forks(&data);
	init_philo(&data, av);
	// init_monitor(&data);
	init_threads(&data);
	destroy_mutex_data(&data);
	return (0);
}

int check_invalid_input(char **av)
{
	int i;
	int max_philo;

	i = 1;
	while (av[i])
	{
		if (check_is_valid_number(av[i]) == -1)
		{
			write(2, "argument is not a positive number\n", 35);
			return (1);
		}
		max_philo=ft_atoi(av[1]);
		if (max_philo > 200)
		{
			write(2, "Number of philo should not be more than 200\n", 45);
			return(1);
		}
		i++;
	}
	return(0);
}

void destroy_mutex_data(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_destroy(&data->philos[i].last_meal_mutex))
		{
			write(2, "Failed to destroy mutex last meal\n", 35);
			return ;
		}
		pthread_mutex_destroy(&data->philos[i].dead_lock);
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
		{
			write(2, "Failed to destroy mutex forks\n", 31);
			return ;
		}
		i++;
	}
	if (pthread_mutex_destroy(&data->write_status) != 0)
	{
		write(2, "Failed to destroy mutex write\n", 31);
		return ;
	}
	if (pthread_mutex_destroy(&data->stop_lock) != 0)
	{
		write(2, "Failed to destroy mutex stop\n", 30);
		return ;
	}
	free(data->philos);
	free(data->forks);
}

// philo update the time before eating
// mutex lock when updating the time
// monitor
// alarm records the time
// thread to monitor of the alarm
// mutex lock
