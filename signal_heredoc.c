/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:41:23 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 18:16:59 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sighere(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 2);
	exit(130);
}

void	ft_sigquithere(int signal)
{
	(void)signal;
	write(1, "\b\b> ", 4);
}
