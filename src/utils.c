/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:53:33 by wshee             #+#    #+#             */
/*   Updated: 2025/06/19 22:16:31 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

int ft_isdigit(char c);

int ft_atoi (char *str)
{
	int res;
	int i;
	int sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <=13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign *= -1;
			i++;
		}
	}
	while (!ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return(res * sign);
}

int ft_isdigit(char c)
{
	if(c >= '0' && c <= '9')
		return (0);
	else
		return(1);
}
