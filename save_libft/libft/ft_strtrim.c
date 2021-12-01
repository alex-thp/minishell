/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:10:59 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 19:07:20 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_findchar(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static	int	ft_setmin(char *s1, char *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_findchar(s1[i], set) == 1)
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	strmax;
	size_t	strmin;
	size_t	strlen;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	strmin = ft_setmin((char *)s1, (char *)set);
	strmax = ft_strlen(s1);
	str = NULL;
	while (strmin < strmax && ft_findchar(s1[strmax - 1], set) == 1)
		strmax--;
	strlen = strmax - strmin;
	str = ft_substr(s1, strmin, strlen);
	return (str);
}
