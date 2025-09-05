/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:02:03 by wshee             #+#    #+#             */
/*   Updated: 2025/09/06 00:39:22 by wshee            ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_philo t_philo;

typedef struct t_data
{
	int num_of_philo;
	t_philo *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t write_status;
	pthread_t	monitor;
	size_t time_start_simulation;
	pthread_mutex_t stop_lock;
	bool stop_simulation;
}				t_data;

typedef struct s_philo
{
	int index;
	size_t time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_to_eat;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t last_meal_mutex;
	pthread_mutex_t dead_lock;
	size_t last_meal;
	int meals_eaten;
	bool is_dead;
	t_data *data;
}				t_philo;

// utils.c
int ft_atoi (char *str);
int check_is_valid_number(char *str);
void print_status(t_data *data, char *str, int philo_index);
size_t get_time_stamp();
void ft_usleep(size_t time_ms, t_data *data);

//main.c
void parse_argument(char **av);
void destroy_mutex_data(t_data *data);

//routine.c
void *routine(void *arg);
bool check_stop_simulation(t_data *data);

//monitor.c
void *monitoring(void *arg);

//init.c
void init_data(t_data *data, char **av);
void init_threads(t_data *data);
void init_philo(t_data *data, char **av);
void init_forks(t_data *data);
void init_monitor(t_data *data);

#endif
