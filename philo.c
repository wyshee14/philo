/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:22:41 by wshee             #+#    #+#             */
/*   Updated: 2025/05/25 16:27:18 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
 # include <unistd.h>

int balance = 0;

int read_balance()
{
    usleep(250000);
    return(balance);
}

void write_balance(int new_balance)
{
    usleep(250000);
    balance = new_balance;
}

void deposit(int amount)
{
    int acc_bal = read_balance();
    acc_bal += amount;
    write_balance(acc_bal);
}

int main()
{
    int before = read_balance();
    printf("Before: %d\n", before);
    deposit(300);
    deposit(200);
    int after = read_balance();
    printf("After: %d\n", after);
    return(0);
}