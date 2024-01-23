/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmontoya <hmontoya@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:10:10 by hmontoya          #+#    #+#             */
/*   Updated: 2023/09/23 17:04:58 by hmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h" 
#include "../include/ft_printf.h" 

void	decoder(int sig)
{
	static int	i = 0;
	static int	c = 0;

	if (!(sig == SIGUSR1 || sig == SIGUSR2))
	{
		perror("Unexpected signal recived\n");
		exit(1);
	}
	if (sig == SIGUSR1)
		c = c | 1 << i;
	i++;
	if (i == 8)
	{
		if (write(1, &c, 1) == -1)
		{
			perror("write");
			exit(1);
		}
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, &decoder);
	signal(SIGUSR2, &decoder);
	ft_printf("SERVER PID: %d\n", getpid());
	sleep(1);
	while (1)
		sleep(1);
	return (0);
}
