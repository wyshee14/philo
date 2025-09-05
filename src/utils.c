# include "../include/philo.h"

int ft_atoi (char *str)
{
	int res;
	int i;

	res = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return(res);
}

int check_is_valid_number(char *str)
{
	int i;

	i = 0;
	// while ((str[i] >= 9 && str[i] <=13) || str[i] == 32)
	// 	i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return(-1);
		i++;
	}
	return (0);
}

// i is the philo index
void print_status(t_data *data, char *str, int philo_index)
{
	if (check_stop_simulation(data))
		return ;
	pthread_mutex_lock(&data->write_status);
	printf("\033[31m%lu\033[0m %d %s\n", get_time_stamp() - data->time_start_simulation, philo_index, str);
	pthread_mutex_unlock(&data->write_status);
}

//print the current timestamp in milliseconds
//fx gettimeofday: gives the number of seconds and microseconds since the Epoch
//Epoch time: number of seconds that have elapsed since January 1, 1970

size_t get_time_stamp()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		write(2, "error gettimestamp\n", 20);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

//break into smaller parts to exit the program if someone died
void ft_usleep(size_t time_ms, t_data *data)
{
	size_t start;

	start = get_time_stamp();
	while(get_time_stamp() - start < time_ms)
	{
		if (check_stop_simulation(data))
			return ;
		usleep(200);
	}
}
