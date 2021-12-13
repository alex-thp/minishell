/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:31:53 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 13:10:01 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	ft_print_nbr(t_param *param, char *str)
{
	int	ret_value;
	int	str_len;

	ret_value = 0;
	if (!str)
		return (0);
	if (*str == '0' && param->precision == 0)
		return (ret_value);
	if (str[0] == '-')
	{
		ret_value += ft_putchar('-');
		str++;
	}
	str_len = ft_strlen(str);
	ret_value += ft_reput('0', param->precision - str_len);
	ret_value += ft_putstr(str);
	param->champ -= ret_value;
	return (ret_value);
}
