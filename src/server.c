/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmontoya <hmontoya@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:10:10 by hmontoya          #+#    #+#             */
/*   Updated: 2024/01/23 13:23:14 by hmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../include/minitalk.h" 
#include "../include/ft_printf.h" 

void	decoder(int sig, siginfo_t *info, void *context)
{
	static int	i 			= 0;
	static unsigned char c	= 0;
	static int cli_pid		= 0;

	if (!cli_pid)
		cli_pid = info->si_pid;
	if (!(sig == SIGUSR1 || sig == SIGUSR2))
	{
		perror("Unexpected signal recived\n");
		exit(1);
	}
	(void)context;
	c |= (sig == SIGUSR1);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(cli_pid, SIGUSR2);
			cli_pid = 0;
			return ;
		}
		if (write(1, &c, 1) == -1)
		{
			perror("write");
			exit(1);
		}
		kill(cli_pid, SIGUSR1);
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction sigact;

	sigact.sa_sigaction = decoder;
	sigact.sa_flags		= SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, 0);
	sigaction(SIGUSR2, &sigact, 0);
	ft_printf("SERVER PID: %d\n", getpid());
	sleep(1);
	while (1)
		sleep(1);
	return (0);
}
