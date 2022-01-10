/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:53:46 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/10 21:45:06 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigreset(int signal)
{
	(void)signal;
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
	catch_sig();
}

void	ft_sigquit(int signal)
{
	(void)signal;
	catch_sig();
}

int	catch_sig(void)
{
	struct sigaction	sint;
	struct sigaction	squit;

	sint.sa_handler = ft_sigint;
	squit.sa_handler = ft_sigquit;
	sigaction(SIGINT, &sint, NULL);
	sigaction(SIGQUIT, &squit, NULL);
	return (0);
}
