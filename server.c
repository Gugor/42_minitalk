/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmontoya <hmontoya@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:10:10 by hmontoya          #+#    #+#             */
/*   Updated: 2023/09/19 18:20:57 by hmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h" 


void decoder(int sig)
{
	static int i = 0;
	static int c = 0;

	if (sig == SIGUSR1)
	{
		c |= 1 << (i) ;		
		printf("SIGSUR1 (%d)\n", i);
		i++;
	}
	if (sig == SIGUSR2)
	{
		c |= 0 << (i);
		printf("SIGSUR2 (%d)\n", i);
		i++;
	}
	if (i ==  8)
	{
		write(1,&c,1);
		write(1,"\n",1);
		i = 0;
		c = 0;
	}
}

int main(void)
{
	signal(SIGUSR1, &decoder); 
	signal(SIGUSR2, &decoder);
	printf("SERVER PID: %d\n",getpid());
	sleep(1);
	while (1)
	{
		pause();
	}
	return (0);
}
