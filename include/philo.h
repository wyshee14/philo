/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:02:03 by wshee             #+#    #+#             */
/*   Updated: 2025/09/07 11:21:40 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

# define TAKEN_A_FORK 1
# define IS_EATING 2
# define IS_SLEEPING 3
# define IS_THINKING 4
# define IS_DIED 5

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct t_data
{
	int				num_of_philo;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_status;
	pthread_mutex_t	stop_lock;
	size_t			time_start_simulation;
	bool			stop_simulation;
	pthread_t		monitor;
}				t_data;

typedef struct s_philo
{
	int				index;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_to_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	dead_lock;
	size_t			last_meal;
	int				meals_eaten;
	bool			is_dead;
	pthread_t		thread;
	t_data			*data;
}				t_philo;

//validate_input.c
int		check_invalid_input(char **av);
int		ft_atoi(char *str);

//utils.c
void	print_status(t_data *data, char *str, int philo_index, int action);
size_t	get_time_stamp(void);
void	ft_usleep(size_t time_ms, t_data *data);
int		ft_init_mutex(pthread_mutex_t *lock);
void	assign_forks(t_data *data, int i);

//main.c
int		destroy_mutex_data(t_data *data);
int		ft_destroy_mutex(pthread_mutex_t *lock);

//routine.c
void	*routine(void *arg);

//monitor.c
void	*monitoring(void *arg);
bool	check_stop_simulation(t_data *data);

//init.c
int		init_data(t_data *data, char **av);
int		init_threads(t_data *data);
int		init_philo(t_data *data, char **av);
int		init_forks(t_data *data);

#endif
