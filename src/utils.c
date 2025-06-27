/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:53:33 by wshee             #+#    #+#             */
/*   Updated: 2025/06/27 21:24:21 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

int ft_atoi (char *str)
{
	int res;
	int i;

	res = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return(res);
}

int check_is_valid_number(char *str)
{
	int i;

	i = 0;
	// while ((str[i] >= 9 && str[i] <=13) || str[i] == 32)
	// 	i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return(-1);
		i++;
	}
	return (0);
}
