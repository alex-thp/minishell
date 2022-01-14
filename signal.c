/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:53:46 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/13 16:14:50 by adylewsk         ###   ########.fr       */
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
	//catch_sig();
}

void	ft_sigquit(int signal)
{
	(void)signal;
	write(1, "\b\b  \b\b", 6);
	//catch_sig();
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
	return (0);
}
