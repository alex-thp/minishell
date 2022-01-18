/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:16:46 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/18 18:51:20 by ade-temm         ###   ########.fr       */
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
	while (command[i])
	{
		j = 0;
		while (command[i] && is_whitespace(command[i]))
			i++;
		while (command[i] && command[i] != '|')
		{
			if (command[i] == '\'' || command[i] == '"')
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

	if (!command || !*command || check_pipe_error(command) == 1)
	{
		printf("minishell : syntax error or empty line\n");
		return (NULL);
	}
	result = parse_command(command, datas);
	return (result);
}
