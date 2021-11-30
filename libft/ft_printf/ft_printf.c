/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 19:54:49 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 13:10:41 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libftprintf.h"

int	ft_print_formated_str(const char *format, va_list argu)
{
	t_param	param;
	int		ret_value;

	ret_value = 0;
	while (*format != '\0')
	{
		if (*format != '%')
			ret_value += ft_putchar(*format);
		else if (*format == '%' && format[1])
		{
			param = ft_format_to_param(param, argu, &format);
			if (param.error > 0)
				return (-param.error);
			ret_value += ft_convert_to_fonc(param, argu);
		}
		format++;
	}
	return (ret_value);
}

int	ft_printf(const char *format, ...)
{
	va_list	argu;
	int		ret_value;

	va_start(argu, format);
	ret_value = ft_print_formated_str(format, argu);
	va_end(argu);
	return (ret_value);
}
