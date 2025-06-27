/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:22:41 by wshee             #+#    #+#             */
/*   Updated: 2025/06/27 22:09:07 by wshee            ###   ########.fr       */
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
	pthread_t t1;
	pthread_t t2;
	int deposit1 = 300;
    int deposit2 = 200;
	pthread_create(&t1, NULL, deposit, (void*)deposit1);
    pthread_create(&t2, NULL, deposit, (void*)deposit1);
	pthread_join(&t1, NULL);
    pthread_join(&t2, NULL);
    int after = read_balance();
    printf("After: %d\n", after);
    return(0);
}
