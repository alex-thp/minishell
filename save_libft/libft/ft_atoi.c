/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:25:48 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 19:10:10 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_check_nbr(const char **str)
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

int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;

	sign = 0;
	nbr = 0;
	sign = ft_check_nbr(&str);
	while (*str >= '0' && *str <= '9' && *str)
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (nbr * sign);
}
