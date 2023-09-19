/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmontoya <hmontoya@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:08:33 by hmontoya          #+#    #+#             */
/*   Updated: 2023/09/14 15:05:26 by hmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main(int argc, *argv[]) 
{
	if (argc != 3)
	{
		ft_printf
	}
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error while configuring signal handler.\n");
        exit(1);
    }
    kill(getpid(), SIGUSR1);
    while (!client_ready) {
        printf("Waiting for server...\n");
        sleep(1);
    }
    ft_printf("Client ready...\n");
    return 0;
}
