/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:02:03 by wshee             #+#    #+#             */
/*   Updated: 2025/06/27 18:38:54 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_data
{
	int num_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_to_eat;
	pthread_mutex_t *forks;
	pthread_t *philos;
}				t_data;

typedef struct s_philo
{
	int philo_index;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t eat;
	pthread_mutex_t sleep;
	pthread_mutex_t write;
}				t_philo;

// utils.c
int check_is_valid_number(char *str);
int ft_atoi (char *str);

void parse_arguments(int ac, char **av, t_data *data);
void init_data(t_data *data);
void set_arguments(t_data *data, int *args);
void init_threads(t_data *data);
void *routine();
void print_status(char *str, int i);
size_t get_time_stamp();

#endif
