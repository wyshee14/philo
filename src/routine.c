/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:01:56 by wshee             #+#    #+#             */
/*   Updated: 2025/06/27 23:15:56 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

void *routine(void *arg)
{
	//eat

	//sleep
	//think
	printf("Hi I am philo\n");
	return (NULL);
}

void philo_eat(t_data *data)
{
    //take left and right fork
}

void philo_take_fork(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->num_of_philo)
    {
        if (pthread_mutex_lock(&data->forks[i]))
        {
            write(2, "Failed to lock mutex\n", 22);
            return ;
        }
        print_status("has taken a fork", i);
        philo_eat()

        i++;
    }
}

//assign fork
// {
    //while philo i
    //if(i==0)
        //right=fork-1
    //else
        //right = i
    //left = i - 1
// }
