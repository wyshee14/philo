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

void print_status(char *str, int i)
{
	printf("%lu %d %s\n", get_time_stamp(), i, str);
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

void ft_usleep(size_t time_ms)
{
	size_t start;

	start = get_time_stamp();
	while(get_time_stamp() - start < time_ms)
		usleep(200);
}
