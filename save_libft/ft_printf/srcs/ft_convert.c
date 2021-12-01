/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:18:28 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 13:10:23 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	ft_char_convert(t_param param, va_list argu)
{
	char	c;
	int		ret_value;

	ret_value = 0;
	if (param.convert == '%')
	{
		c = '%';
		param.convert = 'c';
	}
	else
		c = va_arg(argu, int);
	if (param.flag != '-')
	{
		ret_value = ft_print_champ(&param, &c);
		ret_value += ft_print_str(&param, &c);
		return (ret_value);
	}
	ret_value += ft_print_str(&param, &c);
	ret_value += ft_reput(param.flag, param.champ);
	return (ret_value);
}

int	ft_str_convert(t_param param, va_list argu)
{
	char	*str;
	int		ret_value;

	str = va_arg(argu, char *);
	ret_value = 0;
	if (!str)
		str = "(null)";
	if (param.flag != '-')
	{
		ret_value = ft_print_champ(&param, str);
		ret_value += ft_print_str(&param, str);
		return (ret_value);
	}
	ret_value += ft_print_str(&param, str);
	ret_value += ft_reput(param.flag, param.champ);
	return (ret_value);
}

int	ft_ptr_convert(t_param param, va_list argu)
{
	unsigned long int	ptr_addr;
	char				*str;
	int					ret_value;

	ret_value = 0;
	ptr_addr = va_arg(argu, unsigned long int);
	str = ft_itoa_base(ptr_addr, HEXADECIMAL);
	param.champ -= 2;
	if (param.flag != '-')
	{
		ret_value += ft_print_champ(&param, str);
		ret_value += ft_putstr("0x");
		ret_value += ft_print_ptr(&param, str);
		free(str);
		return (ret_value);
	}
	ret_value += ft_putstr("0x");
	ret_value += ft_print_ptr(&param, str);
	ret_value += ft_reput(param.flag, param.champ);
	free(str);
	return (ret_value);
}

int	ft_base_convert(t_param param, va_list argu)
{
	char	*str;
	char	*save_str;
	int		ret_value;

	str = ft_itoa_base(va_arg(argu, int), ft_convert_to_base(param.convert));
	save_str = str;
	ret_value = 0;
	if (param.flag != '-')
	{
		if (*save_str == '-' && param.flag == '0' && param.precision < 0)
		{
			ret_value += ft_putchar('-');
			save_str++;
			param.champ--;
		}
		ret_value += ft_print_champ(&param, save_str);
		ret_value += ft_print_nbr(&param, save_str);
		free(str);
		return (ret_value);
	}
	ret_value += ft_print_nbr(&param, save_str);
	ret_value += ft_reput(param.flag, param.champ);
	free(str);
	return (ret_value);
}

int	ft_unsigned_convert(t_param param, va_list argu)
{
	char			*str;
	char			*save_str;
	int				ret_value;

	str = ft_uitoa(va_arg(argu, unsigned int));
	save_str = str;
	ret_value = 0;
	if (param.flag != '-')
	{
		ret_value += ft_print_champ(&param, save_str);
		ret_value += ft_print_nbr(&param, save_str);
		free(str);
		return (ret_value);
	}
	ret_value += ft_print_nbr(&param, save_str);
	ret_value += ft_reput(param.flag, param.champ);
	free(str);
	return (ret_value);
}
