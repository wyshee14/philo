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
	parse_argument(av);
	init_data(&data, av);
	init_forks(&data);
	init_philo(&data, av);
	init_threads(&data);
	//monitor is another thread that monitor all philos
	destroy_forks(&data);
	return (0);
}

void parse_argument(char **av)
{
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
		//args[i - 1] = ft_atoi(av[i]);
		i++;
	}
	// for (int i = 0; i < ac - 1; i++)
	// 	printf("atoi: %d\n", args[i]);
}

void destroy_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
		{
			write(2, "Failed to destroy mutex\n", 25);
			return ;
		}
		i++;
	}
}

// philo update the time before eating
// mutex lock when updating the time
// monitor
// alarm records the time
// thread to monitor of the alarm
// mutex lock
