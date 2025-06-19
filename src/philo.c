/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:56:28 by wshee             #+#    #+#             */
/*   Updated: 2025/06/19 22:14:25 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
# include "../include/philo.h"

int main (int ac, char **av)
{
	if (ac < 5)
	{
		printf("argument must be more than 5\n");
		return (1);
	}
	int i = 0;
	while (av[i])
	{
		int j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
			{
				printf("argument is not a number\n");
			}
			j++;
		}
		int arg = ft_atoi(av[i]);
		printf("number[%d]: %d\n", i, arg);
		i++;
	}
	//init_philo
	return(0);
}

// void init_philo()
// philo update the time before eating
// mutex lock when updating the time
// alarm records the time
// thread to monitor of the alarm
// mutex lock
