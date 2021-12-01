/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:36:55 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 19:17:07 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	ft_itoa_len(long nbr, int len_base)
{
	int	result;

	result = 1;
	while (nbr > len_base - 1)
	{
		nbr = nbr / len_base;
		result++;
	}
	return (result);
}

char	ft_itoa_sign(long *nbr, int *len, int len_base)
{
	*len = 0;
	if (*nbr >= 0)
		return (0);
	if (len_base == 10)
	{
		*len = 1;
		*nbr = *nbr * -1;
		return ('-');
	}
	*nbr = ft_pow(len_base, 8) + *nbr;
	return (0);
}

char	*ft_itoa_base(long nbr, char *base)
{
	long	len_base;
	int		len;
	char	*str;
	char	sign;

	len_base = ft_strlen(base);
	sign = ft_itoa_sign(&nbr, &len, len_base);
	len = len + ft_itoa_len(nbr, len_base);
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (str);
	len--;
	while (len > 0)
	{
		str[len] = base[nbr % len_base];
		nbr = nbr / len_base;
		len--;
	}
	if (sign)
		str[len] = sign;
	else
		str[len] = base[nbr % len_base];
	return (str);
}

unsigned	int	ft_nbrlen_base(unsigned int nbr, unsigned int lenbase)
{
	int	i;

	i = 0;
	if (lenbase == 0 || nbr <= 9)
		return (1);
	while (nbr)
	{
		nbr /= lenbase;
		i++;
	}
	return (i);
}

char	*ft_uitoa(unsigned int ui)
{
	char			c;
	char			*str;
	unsigned int	i;

	i = ft_nbrlen_base(ui, 10);
	c = '0';
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	i--;
	while (i > 0)
	{
		c = ui % 10 + '0';
		str[i] = c;
		ui /= 10;
		i--;
	}
	str[i] = ui + '0';
	return (str);
}
