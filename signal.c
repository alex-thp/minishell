/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:53:46 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/14 22:43:47 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigreset(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	return;
}

void	ft_sigint(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	_variable = -22;
	//catch_sig();
}

void	ft_sigquit(int signal)
{
	(void)signal;
	write(1, "\b\b  \b\b", 6);
	//catch_sig();
}

void	ft_sigchild(int signal)
{
	(void)signal;
	int	status;

	status = 0;
	wait(&status);
	//printf("pid ft_wait = %d\n", getpid());
	if (WIFEXITED(status))
		_variable = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
			write(2, "(core dumped)\n", 14);
		_variable = WTERMSIG(status);
		_variable += 128;
	}
}

int	catch_sig(void)
{
	// struct sigaction	sint;
	// struct sigaction	squit;

	// sint.sa_handler = ft_sigint;
	// squit.sa_handler = ft_sigquit;
	// sigaction(SIGINT, &sint, NULL);
	// sigaction(SIGQUIT, &squit, NULL);
	signal(SIGINT, &ft_sigint);
	signal(SIGQUIT, &ft_sigquit);
	signal(SIGCHLD, &ft_sigchild);
	return (0);
}
