/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:22:41 by wshee             #+#    #+#             */
/*   Updated: 2025/06/12 21:44:29 by wshee            ###   ########.fr       */
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
	pthread_t t1;
	pthread_t t2;
    printf("Before: %d\n", before);
	pthread_create(&t1, NULL, deposit, NULL);
    pthread_create(&t2, NULL, deposit, NULL);
	// deposit(300);
    // deposit(200);
	pthread_join()
    int after = read_balance();
    printf("After: %d\n", after);
    return(0);
}
