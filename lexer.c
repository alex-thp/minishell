/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/16 18:57:04 by adylewsk         ###   ########.fr       */
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

int	check_pipe_error(char *command)
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
			if (command[i] == '\'' || command[i] =='"')
			{
				if (ft_look(command, i, command[i]) != -1)
					i = ft_look(command, i, command[i]);
			}
			i++;
			j++;
		}
		if (j == 0)
			return (1);
		if (command[i])
			i++;
	}
	return (0);
}

char	**lexer(char *command, t_datas *datas)
{
	char	**result;

	if (check_pipe_error(command) == 1)
	{
		printf("error with pipe\n");
		return (NULL);
	}
	result = parse_command(command, datas);
	return (result);
}
