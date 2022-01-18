/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsupint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:51:52 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/18 21:06:14 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_check_nbr(char **str)
{
	int	sign;

	sign = 1;
	while (**str == ' ' || **str == '\n' || **str == '\t'
		|| **str == '\v' || **str == '\f' || **str == '\r')
		*str = *str + 1;
	if (**str != '-' && **str != '+')
		return (sign);
	if (**str == '-')
		sign = -1;
	*str = *str + 1;
	return (sign);
}

int	ft_strsupint(char *str)
{
	int	sign;
	long	nbr;

	sign = 0;
	nbr = 0;
	sign = ft_check_nbr(&str);
	if (!ft_strisdigit(str))
		return (1);
	while (*str >= '0' && *str <= '9' && *str)
	{
		nbr = nbr * 10 + (*str - 48);
		if (nbr * sign < (long)INT_MIN || nbr * sign > (long)INT_MAX)
			return (1);
		str++;
	}
	return (0);
	
}
