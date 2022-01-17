/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:09:36 by alex              #+#    #+#             */
/*   Updated: 2022/01/17 16:27:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char *str, int *j)
{
	char	*result;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[*j] && str[*j] == ' ')
		*j += 1;
	while (str[*j + i] && str[*j + i] != '|')
	{
		if (str[*j + i] == '\'' || str[*j + i] == '"')
		{
			if (ft_look2(str, *j + i, str[*j + i]) != -1)
				i += ft_look2(str, *j + i, str[*j + i]);
		}
		i++;
	}
	result = malloc(sizeof(char) * (i + 1));
	result[i] = 0;
	i += *j;
	while (*j < i)
	{
		result[k] = str[*j];
		*j += 1;
		k++;
	}
	return (result);
}

int	ft_init_split(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (ft_look(str, i, str[i]) != -1)
				i = ft_look(str, i, str[i]);
		}
		else if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	**ft_custom_split(char *str, t_datas *datas)
{
	char	**result;
	int		i;
	int		j;
	int		index;

	i = ft_init_split(str);
	j = 0;
	index = 0;
	result = ft_calloc(i + 1, sizeof(char *));
	while (j < i)
	{
		result[j] = get_word(str, &index);
		result[j] = dollar_interpretation(result[j], datas);
		index++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

char	**parse_command(char *str, t_datas *datas)
{
	char	**tab;

	tab = ft_custom_split(str, datas);
	return (tab);
}
