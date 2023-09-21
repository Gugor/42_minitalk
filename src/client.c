/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmontoya <hmontoya@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:08:33 by hmontoya          #+#    #+#             */
/*   Updated: 2023/09/21 18:49:09 by hmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../include/ft_printf.h"

void error_handler(int argc, char *argv[])
{
	pid_t  pid;

	pid = 0;
	if (argc != 3)
	{
		ft_printf(":: Error! - Wrong number of arguments.\n");
		ft_printf(":: Correct: ./client [SERVER PID] [STRING MESSAGE]\n");
		exit(1);
	}
	ft_printf("Cheking pid...\n");
	pid = atoi(argv[1]);
	if (pid < 0)
	{
		ft_printf(":: Error: PID argument is not a valid number.\n");
		exit(2);
	}
	ft_printf("Access to server with PID: %d\n", pid);
}

int  encode(int pid, char bits)
{
	int i;
	
	i = 0;
	if (!bits)
		return (0);
	while (i <  8)
	{
		if (kill(pid, 0) != 0)
		{
			perror("Server unrecheable!");
			exit(EXIT_FAILURE);
		}
		if ((bits & (1 << i)) != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				perror("Error while sending SIGUSR1\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
    		if (kill(pid, SIGUSR2) == -1)
			{
				perror("Error while sending SIGUSR1\n");
				exit(EXIT_FAILURE);
			}
		}
		usleep(100);
		i++;
	}
		return (0);
}


int main(int argc, char *argv[]) 
{
	pid_t  pid;
	int i;
	int error;
	char *str;
	
	error_handler(argc, argv);
	pid = atoi(argv[1]);
	i = 0;
	error = 0;
	str = argv[2];
	while (str[i])
	{
		encode(pid, str[i]);
		i++;
	}
	ft_printf("Message send succesfully!.\n");
    return 0;
}
