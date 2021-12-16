/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/16 14:28:26 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	check_pipe_error(char *command) //return 1 = error || return 0 = ok
{
	int	i;
	int	j;

	i = 0;
	if (!command || !*command)
		return (1);
	while (command[i])
	{
		j = 0;
		while (command[i] && is_whitespace(command[i]))
			i++;
		while (command[i] && command[i] != '|')
		{
			i++;
			j++;
		}
		if (j == 0)
			return (1);
	}
	return (0);
}

char	**lexer(char *command)
{
	char	**result;

	if (check_pipe_error(command) == 1)
	{
		printf("error with pipe\n");
		return (NULL);
	}
	result = ft_split(command, '|');
	return (result);
}
