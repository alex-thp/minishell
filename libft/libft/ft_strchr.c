/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:09:29 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 00:17:31 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*cps;

	i = 0;
	cps = (char *)s;
	while (cps[i])
	{
		if (cps[i] == (char)c)
			return (cps + i);
		i++;
	}
	if (cps[i] == (char)c)
		return (cps + i);
	return (NULL);
}
