/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:25:51 by alex              #+#    #+#             */
/*   Updated: 2022/01/17 20:33:02 by adylewsk         ###   ########.fr       */
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

int	save_in_quotes(char *result, char *str, int	*i, int *j)
{
	int	closed_quote;

	closed_quote = ft_closed_quote(str + *i);
	if (closed_quote)
	{
		*i += 1;
		while (closed_quote > 1)
		{
			result[*j] = str[*i];
			*i += 1;
			*j += 1;
			closed_quote--;
		}
		*i += 1;
		return (1);
	}
	return (0);
}

char	*erase_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!save_in_quotes(result, str, &i, &j))
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
