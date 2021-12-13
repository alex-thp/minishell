/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:09:13 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 19:15:12 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cpdst;
	unsigned char	*cpsrc;

	cpdst = (unsigned char *)dst;
	cpsrc = (unsigned char *)src;
	if (cpsrc < cpdst)
	{
		while (len)
		{
			len--;
			cpdst[len] = cpsrc[len];
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
