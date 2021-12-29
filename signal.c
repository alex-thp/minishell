/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:53:46 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/29 17:50:56 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
	catch_sig();
}

void	ft_sigquit(int signal)
{
	(void)signal;
	catch_sig();
}

int	catch_sig()
{
	struct sigaction	sint;
	struct sigaction	squit;

	sint.sa_handler = ft_sigint;
	squit.sa_handler = ft_sigquit;
	sigaction(SIGINT, &sint, NULL);
	sigaction(SIGQUIT, &squit, NULL);
	return (0);
}
