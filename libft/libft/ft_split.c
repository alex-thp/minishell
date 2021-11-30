/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:09:26 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/08 17:06:33 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_nbrword(char *str, char c)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			nb_word++;
		i++;
	}
	return (nb_word);
}

static	int	ft_strlenpart(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static	char	*ft_strduppart(char **src, char c)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = malloc(sizeof(char) * (ft_strlenpart(*src, c) + 1));
	if (!cpy)
		return (0);
	while (**src && **src != c)
	{
		cpy[i] = **src;
		*src += 1;
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;
	char	*save;

	i = 0;
	save = (char *)s;
	if (!save)
		return (NULL);
	tab = ft_calloc(ft_nbrword(save, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	if (save && *save && *save != c)
		tab[i] = ft_strduppart(&save, c);
	if (tab[i] != 0)
		i++;
	while (save && *save && *save == c)
	{
		save++;
		if (*save && *save != c)
		{
			tab[i] = ft_strduppart(&save, c);
			i++;
		}
	}
	return (tab);
}
