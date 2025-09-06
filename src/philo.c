/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:15:54 by wshee             #+#    #+#             */
/*   Updated: 2025/09/07 03:00:17 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		write(2, "There must be 5 or 6 arguments\n", 32);
		return (1);
	}
	if (check_invalid_input(av))
		return (1);
	if (init_data(&data, av))
		return (1);
	if (init_forks(&data))
		return (1);
	if (init_philo(&data, av))
		return (1);
	if (init_threads(&data))
		return (1);
	if (destroy_mutex_data(&data))
		return (1);
	return (0);
}

int	destroy_mutex_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (ft_destroy_mutex(&data->philos[i].last_meal_mutex))
			return (1);
		if (ft_destroy_mutex(&data->philos[i].dead_lock))
			return (1);
		if (ft_destroy_mutex(&data->forks[i]))
			return (1);
		i++;
	}
	if (ft_destroy_mutex(&data->write_status))
		return (1);
	if (ft_destroy_mutex(&data->stop_lock))
		return (1);
	free(data->philos);
	free(data->forks);
	return (0);
}

int	ft_destroy_mutex(pthread_mutex_t *lock)
{
	if (pthread_mutex_destroy(lock) != 0)
	{
		write(2, "Failed to destroy mutex write\n", 31);
		return (1);
	}
	return (0);
}
