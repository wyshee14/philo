/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:56:28 by wshee             #+#    #+#             */
/*   Updated: 2025/06/25 23:04:11 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
# include "../include/philo.h"

int main (int ac, char **av)
{
	t_philo philo;
	int args[ac - 1];

	if (ac < 5 || ac > 6)
	{
		printf("argument must be more than 5\n");
		return (1);
	}
	int i = 1;
	while (av[i])
	{
		// printf("argument[%d]: %s\n", i, av[i]);
		//check the argument is a number
		if (check_is_valid_number(av[i]) == -1)
		{
			printf("argument is not a number\n");
			return(1);
		}
		// convert into integer
		args[i - 1] = ft_atoi(av[i]);
		i++;
	}
	// for (int i = 0; i < ac - 1; i++)
	// 	printf("atoi: %d\n", args[i]);
	init_philo(&philo);
	set_arguments(&philo, args);
	init_threads(&philo);
	return (0);
}

void init_philo(t_philo *philo)
{
	memset(philo, 0, sizeof(t_philo));
}

void set_arguments(t_philo *philo, int *args)
{
	philo->num_of_philo = args[0];
	philo->time_to_die = args[1];
	philo->time_to_eat = args[2];
	philo->time_to_sleep = args[3];
	philo->number_of_times_to_eat = args[4];
}

void init_threads(t_philo *philo)
{
	pthread_t philo_thread[philo->num_of_philo];
	pthread_mutex_t mutex;
	int i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while(i < philo->num_of_philo)
	{
		if (pthread_create(&philo_thread[i], NULL, routine, NULL)!= 0)
		{
			printf("Failed to create thread [%d]", i);
			return ;
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while(i < philo->num_of_philo)
	{
		if (pthread_join(philo_thread[i], NULL) != 0)
		{
			printf("Failed to join thread [%d]", i);
			return ;
		}
		printf("Thread %d finished execution\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
}

void *routine()
{
	printf("Hi I am philo\n");
	return (NULL);
}

// philo update the time before eating
// mutex lock when updating the time
// alarm records the time
// thread to monitor of the alarm
// mutex lock
