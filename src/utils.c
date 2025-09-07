/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:31:51 by wshee             #+#    #+#             */
/*   Updated: 2025/09/07 11:31:57 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check stop flag every time when print
void	print_status(t_data *data, char *str, int philo_index, int action)
{
	if (check_stop_simulation(data))
		return ;
	pthread_mutex_lock(&data->write_status);
	if (action == 1)
		printf(BLUE"%lu " YELLOW"%d " RESET"%s" RESET"\n",
			get_time_stamp() - data->time_start_simulation, philo_index, str);
	else if (action == 2)
		printf(BLUE"%lu " YELLOW"%d " GREEN"%s" RESET"\n",
			get_time_stamp() - data->time_start_simulation, philo_index, str);
	else if (action == 3)
		printf(BLUE"%lu " YELLOW"%d " MAGENTA"%s" RESET"\n",
			get_time_stamp() - data->time_start_simulation, philo_index, str);
	else if (action == 4)
		printf(BLUE"%lu " YELLOW"%d " CYAN"%s" RESET"\n",
			get_time_stamp() - data->time_start_simulation, philo_index, str);
	else if (action == 5)
		printf(BLUE"%lu " YELLOW"%d " RED"%s" RESET"\n",
			get_time_stamp() - data->time_start_simulation, philo_index, str);
	pthread_mutex_unlock(&data->write_status);
}

//print the current timestamp in milliseconds
//fx gettimeofday: struct consists seconds and microseconds since Epoch
//Epoch time: number of seconds that have elapsed since January 1, 1970
size_t	get_time_stamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		write(2, "error gettimestamp\n", 20);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// break into smaller parts to exit the program if someone died
// normal usleep is not accurate might cause delay
// after sleep need to wait OS scheduler to run the thread again
// so checking the time frequently may help to check the time more accurately
void	ft_usleep(size_t time_ms, t_data *data)
{
	size_t	start;

	start = get_time_stamp();
	while (get_time_stamp() - start < time_ms)
	{
		if (check_stop_simulation(data))
			return ;
		usleep(200);
	}
}

int	ft_init_mutex(pthread_mutex_t *lock)
{
	if (pthread_mutex_init(lock, NULL) != 0)
	{
		write(2, "Failed to init mutex\n", 22);
		return (1);
	}
	return (0);
}

void	assign_forks(t_data *data, int i)
{
	data->philos[i].left_fork = &data->forks[i];
	if (i == 0)
		data->philos[i].right_fork = &data->forks[data->num_of_philo - 1];
	else
		data->philos[i].right_fork = &data->forks[i - 1];
}
