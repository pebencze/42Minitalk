/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:59:03 by pbencze           #+#    #+#             */
/*   Updated: 2024/01/19 17:37:03 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler_client(int signum)
{
	if (signum == SIGUSR1)
	{
		exit (0);
	}
	exit (1);
}

int	ft_action(void)
{
	struct sigaction	action;

	action.sa_handler = signal_handler_client;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	if (sigaction(SIGUSR1, &action, NULL) != 0)
		return (1);
	else
		ft_printf("Server recieved the full message.");
	return (0);
}

void	send_message(char *message, pid_t pid)
{
	int	i;
	int	result;

	while (*message)
	{
		i = 7;
		while (i >= 0)
		{
			if ((*message >> i) & 1)
				result = kill(pid, SIGUSR1);
			else
				result = kill(pid, SIGUSR2);
			if (result == -1)
			{
				ft_printf("Failure on sending signal.");
				exit (1);
			}
			i--;
			usleep(150);
		}
		message++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nbr;

	sign = 1;
	i = 0;
	nbr = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	return (nbr * sign);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	char	*message;

	if (ac != 3)
	{
		ft_printf("Usage: %s <pid> <message>\n", av[0]);
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (kill(pid, 0) == -1 || pid <= 0)
	{
		ft_printf("PID not valid.\n", av[0]);
		return (1);
	}
	message = av[2];
	ft_action();
	send_message(message, pid);
	return (0);
}
