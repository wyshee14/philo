/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:56:28 by wshee             #+#    #+#             */
/*   Updated: 2025/06/21 17:42:37 by wshee            ###   ########.fr       */
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
		//check the argument is a number
		// int j = 0;
		// while (av[i][j])
		// {
		// 	printf("arguemnt: %c\n", av[i][j]);
		// 	if (ft_isdigit(av[i][j]) == 1)
		// 	{
		// 		return (1);
		// 	}
		// 	j++;
		// }
		printf("argument[%d]: %s\n", i, av[i]);
		if (check_is_valid_number(av[i]) == -1)
		{
			printf("argument is not a number\n");
			return(1);
		}
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
