/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:33:44 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 13:09:59 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	ft_len_precision(t_param param, char *str)
{
	if (param.convert == 'c')
		return (1);
	if (param.convert == 's' && param.precision >= 0)
		return (ft_min(param.precision, ft_strlen(str)));
	if (param.convert == 'p' && ft_strlen(str) < 2
		&& *str == '0' && param.precision >= 0)
		if (ft_strlen(str) < 2 && *str == '0' && param.precision >= 0)
			return (0);
	if (ft_strrchr("diuxX", param.convert))
	{
		if (*str == '-' && param.precision > (int)ft_strlen(str) - 1)
			return (param.precision + 1);
		if (*str == '0' && param.precision == 0)
			return (0);
	}
	return (ft_max(param.precision, ft_strlen(str)));
}

int	ft_reput(char flag, int nbr)
{
	char	fill_character;
	int		i;

	fill_character = ' ';
	i = 0;
	if (flag == '0')
		fill_character = '0';
	while (i < nbr)
		i += ft_putchar(fill_character);
	return (i);
}

int	ft_print_champ(t_param *param, char *str)
{
	int		ret_value;
	int		len_precision;

	ret_value = 0;
	len_precision = 0;
	if (!str)
		return (0);
	if (param->flag != '-')
		len_precision += ft_len_precision(*param, str);
	ret_value += ft_reput(param->flag, param->champ - len_precision);
	return (ret_value);
}
