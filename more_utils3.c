/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:25:51 by alex              #+#    #+#             */
/*   Updated: 2022/01/17 16:29:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_closed_quote(char *str)
{
	int		i;
	char	quote;

	i = 1;
	if (!str || !*str)
		return (0);
	if (*str != '"' && *str != '\'')
		return (0);
	quote = *str;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

char	*erase_quotes(char *str)
{
	int		i;
	int		j;
	int		closed_quote;
	char	*result;

	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	j = 0;
	closed_quote = 0;
	while (str[i])
	{
		closed_quote = ft_closed_quote(str + i);
		if (closed_quote)
		{
			i++;
			while (closed_quote > 1)
			{
				result[j] = str[i];
				i++;
				j++;
				closed_quote--;
			}
			i++;
		}
		else
		{
			result[j] = str[i];
			j++;
			i++;
		}
	}
	result[j] = 0;
	free(str);
	return (result);
}

int	get_size_name(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
