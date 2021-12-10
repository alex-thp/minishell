/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:19:12 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/10 16:22:58 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_word(char const *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != c)
			count++;
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	*ft_copy_word(char const *s, char c)
{
	char	*result;
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	result = ft_calloc(i + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static void	ft_free(int count, char **strs)
{
	while (count > -1)
	{
		free(strs[count]);
		count--;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**strs;

	i = ft_count_word(s, c);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (0);
	strs[i] = NULL;
	j = 0;
	while (j < i)
	{
		while (*s == c)
			s++;
		strs[j] = ft_copy_word(s, c);
		if (strs[j] == NULL)
		{
			ft_free(j, strs);
			return (NULL);
		}
		while (*s != c && *s)
			s++;
		j++;
	}
	return (strs);
}
