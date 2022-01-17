/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 18:52:59 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char c, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int		get_lenvalue(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_special(str[i], " <>") == 0)
	{
		i += ft_closed_quote(str + i);
		i++;
	}
	return (i);
}

int		save_quote(char *result, char *str, int i)
{
	int	quote;

	quote = 0;
	quote = ft_closed_quote(str + i);
	while (quote)
	{
		result[i] = str[i];
		str[i] = ' ';
		quote--;
		i++;
	}
	return (i);
}

char	*get_value2(char *str)
{
	int		i;
	char	*result;

	i = 0;
	*str = ' ';
	while (*str == ' ')
		str++;
	result = ft_calloc(get_lenvalue(str) + 1, sizeof(char));
	while (str[i] && is_special(str[i], " <>") == 0)
	{
		i = save_quote(result, str, i);
		result[i] = str[i];
		str[i] = ' ';
		i++;
	}
	if (!ft_strlen(result))
	{
		free(result);
		return (NULL);
	}
	result = erase_quotes(result);
	return (result);
}
