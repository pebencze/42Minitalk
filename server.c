/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:59:07 by pbencze           #+#    #+#             */
/*   Updated: 2024/01/16 12:22:23 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sighandler(int sig)
{
	ft_printf("Process recieved signal %d.\n", sig);
	exit(1);
}

void	signal_handler_minitalk(int signum)
{
	static int	i;
	static char	c;

	if (signum == SIGUSR1)
	{
		c |= (1 << (7 - i));
		i++;
	}
	if (signum == SIGUSR2)
	{
		c &= ~(1 << (7 - i));
		i++;
	}
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler_minitalk;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	ft_printf("PID: %d\n", getpid());
	if (sigaction(SIGUSR1, &sa, NULL) != 0)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) != 0)
		return (1);
	if ((signal(SIGQUIT, sighandler) == SIG_ERR)
		|| (signal(SIGTERM, sighandler) == SIG_ERR)
		|| (signal(SIGINT, sighandler) == SIG_ERR)
		|| (signal(SIGABRT, sighandler) == SIG_ERR)
		|| (signal(SIGTSTP, sighandler) == SIG_ERR))
	{
		ft_printf("Error on handling signal.");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
