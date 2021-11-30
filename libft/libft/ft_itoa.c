/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:08:53 by adylewsk          #+#    #+#             */
/*   Updated: 2021/07/19 21:07:33 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_nlen(long save)
{
	int	i;

	i = 0;
	if (save < 0)
	{
		i++;
		save *= -1;
	}
	if (save >= 0 && save <= 9)
		return (i + 1);
	while (save > 0)
	{
		save /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	save;
	int		len;

	save = (long)n;
	len = ft_nlen(save);
	str = ft_calloc((len + 1), sizeof(*str));
	if (!str)
		return (0);
	if (save == 0)
		str[0] = '0';
	if (save < 0)
	{
		str[0] = '-';
		save *= -1;
	}
	while (save > 0)
	{
		len--;
		str[len] = (int)(save % 10) + 48;
		save /= 10;
	}
	return (str);
}
