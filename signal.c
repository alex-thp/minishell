/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:12:26 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 21:12:29 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigreset(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
}

void	ft_sigint(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigquit(int signal)
{
	(void)signal;
	write(1, "\b\b  \b\b", 6);
}

void	ft_sigchild(int signal)
{
	int	status;

	(void)signal;
	status = 0;
	wait(&status);
	if (WIFEXITED(status))
		g_variable = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
			write(2, "(core dumped)\n", 14);
		g_variable = WTERMSIG(status);
		g_variable += 128;
	}
}

int	catch_sig(void)
{
	signal(SIGINT, &ft_sigint);
	signal(SIGQUIT, &ft_sigquit);
	signal(SIGCHLD, &ft_sigchild);
	return (0);
}
