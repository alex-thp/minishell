/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/14 19:20:10 by adylewsk         ###   ########.fr       */
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

char	*get_value2(char *str, int i)
{
	int		j;
	int		quote;
	char	*result;

	str[i] = ' ';
	while (str[i] == ' ')
		i++;
	j = 0;
	while (str[i + j] && is_special(str[i + j], " <>") == 0)
	{
		j += ft_closed_quote(str + i + j);
		j++;
	}
	result = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (str[i + j] && is_special(str[i + j], " <>") == 0)
	{
		quote = ft_closed_quote(str + i + j);
		while (quote)
		{
			result[j] = str[i + j];
			str[i + j] = ' ';
			quote--;
			j++;
		}
		result[j] = str[i + j];
		str[i + j] = ' ';
		j++;
	}
	result[j] = 0;
	if (!ft_strlen(result))
	{
		free(result);
		return (NULL);
	}
	result = erase_quotes(result);
	return (result);
}
