/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmontoya <hmontoya@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:08:33 by hmontoya          #+#    #+#             */
/*   Updated: 2024/01/23 13:21:37 by hmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../include/ft_printf.h"

void	error_handler(int argc, char *argv[])
{
	pid_t	pid;

	pid = 0;
	if (argc != 3)
	{
		ft_printf(":: Error! - Wrong number of arguments.\n");
		ft_printf(":: Usage: ./client [SERVER PID] [STRING MESSAGE]\n");
		exit(1);
	}
	ft_printf("Cheking pid...\n");
	pid = atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf(":: Error: PID argument is not a valid number.\n");
		exit(2);
	}
	ft_printf("Access to server with PID: %d\n", pid);
}

void server_ping(int sig)
{
	static int i = 0;

	if (sig == SIGUSR1)
		i++;
	else
		ft_printf("Message Sended! (%d bytes)\n",i);
}

void	send_signal(pid_t pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		perror("Error while sending signaln");
		exit(EXIT_FAILURE);
	}
}

int	encode(int pid, char bits)
{
	int	i;

	i = 0;
	if (kill(pid, 0) != 0)
	{
		perror("Server unrecheable!");
		exit(EXIT_FAILURE);
	}
	while (i < 8)
	{
		if ((bits & (1 << (7 - i))))
			send_signal(pid, SIGUSR1);
		else
			send_signal(pid, SIGUSR2);
		usleep(100);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		i;
	int		error;
	char	*str;

	error_handler(argc, argv);
	pid = atoi(argv[1]);
	i = -1;
	error = 0;
	str = argv[2];
	signal(SIGUSR1, &server_ping);
	signal(SIGUSR2, &server_ping);
	while (str[++i])
		encode(pid, str[i]);
	i = 8;
	while(i--)
		send_signal(pid, SIGUSR2);
	return (0);
}
