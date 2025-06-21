/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:56:28 by wshee             #+#    #+#             */
/*   Updated: 2025/06/21 22:28:22 by wshee            ###   ########.fr       */
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
	int i = 1;
	while (av[i])
	{
		printf("argument[%d]: %s\n", i, av[i]);
		//check the argument is a number
		if (check_is_valid_number(av[i]) == -1)
		{
			printf("argument is not a number\n");
			return(1);
		}
		//check int min and int max

		// convert into integer
		int arg = ft_atoi(av[i]);
		printf("atoi: %d\n", arg);
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
