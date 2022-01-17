/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:08:42 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 21:18:04 by adylewsk         ###   ########.fr       */
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
