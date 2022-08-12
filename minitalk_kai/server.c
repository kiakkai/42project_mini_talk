/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaizhang <kaizhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:36:32 by kaizhang          #+#    #+#             */
/*   Updated: 2022/08/10 12:25:35 by kaizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include<string.h>
#include<sys/time.h>
#include<signal.h>
#include<stdlib.h>
/*
struct	sigaction
{
	void		(*sa_handler)(int);
	sigset_t	sa_mask;
	int			sa_flags;
	void		(sa_sigaction)(int, siginfo_t*, void*);
	
*/
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nbr)
{
	int	i;

	i = nbr;
	if (i < 0)
	{
		i = i * (-1);
	}
	if (i > 9)
		ft_putnbr(i / 10);
	ft_putchar(i % 10 + 48);
}

void	myfunc(int signum, siginfo_t *siginfo, void *none)
{
	static int	c = 0;
	static int	bits = 0;
	static int	i;

	(void)none;
	c = c << 1;
	if (signum == SIGUSR1)
	{
		c = c + 1;
	}
	bits++;
	if (bits == 8)
	{
		ft_putchar(c);
		bits = 0;
		c = 0;
		if (i != siginfo -> si_pid)
		{
			kill(siginfo -> si_pid, SIGUSR1);
			i = siginfo -> si_pid;
		}
	}
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = myfunc;
	act.sa_flags = SA_SIGINFO;
	write(1, "Server PID is: ", 14);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		pause();
	}
	return (0);
}
