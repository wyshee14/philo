/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:02:03 by wshee             #+#    #+#             */
/*   Updated: 2025/08/27 21:09:47 by wshee            ###   ########.fr       */
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
	pthread_t	monitor;
	bool stop_program;
}				t_data;
// add print mutex

typedef struct s_philo
{
	int index;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_to_eat;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t eat;
	pthread_mutex_t sleep;
	pthread_mutex_t last_meal_mutex;
	int last_meal;
	int is_dead;
	int num_of_philo;
}				t_philo;

// utils.c
int ft_atoi (char *str);
int check_is_valid_number(char *str);
void print_status(char *str, int i);
size_t get_time_stamp();
void ft_usleep(size_t time_ms);

//main.c
void parse_argument(char **av);
void destroy_forks(t_data *data);

//routine.c
void *routine(void *arg);
void take_left_and_right_fork(t_philo *philo);
void philo_eat(t_philo *philo);
void philo_sleep(t_philo *philo);
void philo_think(t_philo *philo);

//init.c
void init_data(t_data *data, char **av);
void init_threads(t_data *data);
void init_philo(t_data *data, char **av);
void init_forks(t_data *data);

#endif
