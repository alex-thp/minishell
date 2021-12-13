/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:08:57 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 00:17:31 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*cpdst;
	unsigned char	*cpsrc;

	i = 0;
	cpdst = (unsigned char *)dst;
	cpsrc = (unsigned char *)src;
	while (i < n)
	{
		cpdst[i] = cpsrc[i];
		if (cpdst[i] == (unsigned char)c || cpsrc[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
