/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmontoya <hmontoya@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:08:33 by hmontoya          #+#    #+#             */
/*   Updated: 2024/01/23 20:31:15 by hmontoya         ###   ########.fr       */
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

void	server_ping(int sig)
{
	static int	i = 0;

	if (sig == SIGUSR1)
		i++;
	else
		write(1, "Message Sended!\n", 16);
}

int	encode(int pid, unsigned char bits)
{
	int	i;

	i = -1;
	if (kill(pid, 0) != 0)
	{
		perror("Server unrecheable!");
		exit(EXIT_FAILURE);
	}
	while (++i < 8)
	{
		if ((bits >> (7 - i) & 1))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
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
		encode(pid, (unsigned char)str[i]);
	i = 9;
	while (--i)
	{
		kill(pid, SIGUSR2);
		usleep(100);
	}
	return (0);
}
