/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:53:33 by wshee             #+#    #+#             */
/*   Updated: 2025/06/21 17:39:06 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

char *check_is_valid_number(char *str);

int ft_atoi (char *str)
{
	int res;
	int i;
	int sign;

	res = 0;
	i = 0;
	sign = 1;
	// while (!ft_isdigit(str[i]))
	// {
	// 	res = res * 10 + (str[i] - '0');
	// 	i++;
	// }
	return(res * sign);
}

int check_is_valid_number(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <=13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return(-1);
	}
	return (0);
}
