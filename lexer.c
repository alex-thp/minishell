/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/10 16:05:24 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_error(char *command) //return 1 = error || return 0 = ok
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (command[i] == 32)
		i++;
	if (command[i] == '|')
		return (1);
	while (command[i])
	{
		j = 0;
		k = 1;
		while (command[i + k] && command[i + k] != '|')
		{
			if (command[i + k] != 32)
				j++;
			k++;
		}
		if (j == 0 && command[i + k])
			return (1);
		i += k;
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
