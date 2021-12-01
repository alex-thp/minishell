/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_to.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:06:55 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 19:16:25 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	ft_convert_to_fonc(t_param param, va_list argu)
{
	int						i;
	static t_map_foncptr	convert_to_fonc[10] = {
	{.convert = 'c', .fonc_convert = ft_char_convert},
	{.convert = 's', .fonc_convert = ft_str_convert},
	{.convert = 'p', .fonc_convert = ft_ptr_convert},
	{.convert = 'd', .fonc_convert = ft_base_convert},
	{.convert = 'i', .fonc_convert = ft_base_convert},
	{.convert = 'u', .fonc_convert = ft_unsigned_convert},
	{.convert = 'x', .fonc_convert = ft_base_convert},
	{.convert = 'X', .fonc_convert = ft_base_convert},
	{.convert = '%', .fonc_convert = ft_char_convert},
	{.convert = 0, .fonc_convert = NULL }
	};

	i = 0;
	while (convert_to_fonc[i].convert != 0)
	{
		if (convert_to_fonc[i].convert == param.convert)
			return (convert_to_fonc[i].fonc_convert(param, argu));
		i++;
	}
	return (0);
}

char	*ft_convert_to_base(char convert)
{
	int					i;
	static t_map_base	map_base[7] = {
	{.convert = 'p', .base = HEXADECIMAL},
	{.convert = 'd', .base = DECIMAL},
	{.convert = 'i', .base = DECIMAL},
	{.convert = 'u', .base = DECIMAL},
	{.convert = 'x', .base = HEXADECIMAL},
	{.convert = 'X', .base = HEXADECIMAL_UP},
	{.convert = 0, .base = NULL}
	};

	i = 0;
	while (map_base[i].convert != 0)
	{
		if (map_base[i].convert == convert)
			return (map_base[i].base);
		i++;
	}
	return (0);
}
