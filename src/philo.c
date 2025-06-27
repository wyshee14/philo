/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:56:28 by wshee             #+#    #+#             */
/*   Updated: 2025/06/27 18:03:40 by wshee            ###   ########.fr       */
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
	parse_arguments(ac, av, &data);
	init_threads(&data);
	return (0);
}

void parse_arguments(int ac, char **av, t_data *data)
{
	int args[ac - 1];
	int i;
	
	i = 1;
	while (av[i])
	{
		// printf("argument[%d]: %s\n", i, av[i]);
		//check the argument is a number
		if (check_is_valid_number(av[i]) == -1)
		{
			printf("argument is not a number\n");
			exit(1);
		}
		// convert into integer
		args[i - 1] = ft_atoi(av[i]);
		i++;
	}
	// for (int i = 0; i < ac - 1; i++)
	// 	printf("atoi: %d\n", args[i]);
	init_data(data);
	set_arguments(data, args);
}

void init_data(t_data *data)
{
	memset(data, 0, sizeof(t_data));
}

void set_arguments(t_data *data, int *args)
{
	if (data->num_of_philo > 200)
	return ;
	else
	data->num_of_philo = args[0];
	data->time_to_die = args[1];
	data->time_to_eat = args[2];
	data->time_to_sleep = args[3];
	data->number_of_times_to_eat = args[4];
	data->philos = (pthread_t *)malloc(data->num_of_philo * sizeof(pthread_t));
	memset(data->philos, 0, sizeof(pthread_t));
}

void init_threads(t_data *data)
{
	// pthread_t philo_thread[philo->num_of_philo];
	// pthread_mutex_t mutex;
	int i;

	i = 0;
	// pthread_mutex_init(&mutex, NULL);
	while(i < data->num_of_philo)
	{
		if (pthread_create(&data->philos[i], NULL, routine, NULL) != 0)
		{
			//remove()
			write(2, "Failed to create thread\n", 25);
			return ;
		}
		// printf("Thread %d has started\n", i);
		print_status("start", i);
		i++;
	}
	i = 0;
	while(i < data->num_of_philo)
	{
		if (pthread_join(data->philos[i], NULL) != 0)
		{
			write(2, "Failed to join thread\n", 23);
			return ;
		}
		// printf("Thread %d finished execution\n", i);
		print_status("end", i);
		i++;
	}
	// pthread_mutex_destroy(&mutex);
}

void *routine(void *arg)
{
	//eat
	//think
	//sleep
	printf("Hi I am philo\n");
	return (NULL);
}

void print_status(char *str, int i)
{
	printf("%lu thread %d %s\n", get_time_stamp(), i, str);
}

size_t get_time_stamp()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		write(2, "error gettimestamp\n", 20);
	}
	return (tv.tv_usec);
}

// philo update the time before eating
// mutex lock when updating the time
// monitor
// alarm records the time
// thread to monitor of the alarm
// mutex lock
