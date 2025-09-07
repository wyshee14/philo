/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:32:07 by wshee             #+#    #+#             */
/*   Updated: 2025/09/07 11:32:09 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_is_valid_number(char *str);

int	check_invalid_input(char **av)
{
	int	i;
	int	max_philo;

	i = 1;
	while (av[i])
	{
		if (check_is_valid_number(av[i]) == -1)
		{
			write(2, "argument is not a positive number\n", 35);
			return (1);
		}
		max_philo = ft_atoi(av[1]);
		if (max_philo > 200)
		{
			write(2, "Number of philo should not be more than 200\n", 45);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

static int	check_is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (0);
}
