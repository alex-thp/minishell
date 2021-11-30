/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 09:07:45 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 19:16:45 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

t_param	ft_checkflag(t_param param, const char **format)
{
	if (*format[0] == '-' || *format[0] == '0')
	{
		while (**format == '-' || **format == '0')
		{
			if (**format == '0' && param.flag == 0)
				param.flag = '0';
			else
				param.flag = '-';
			*format = *format + 1;
		}
	}
	return (param);
}

int	ft_checknbr(va_list argu, const char **format)
{
	int	i;

	i = 0;
	if (**format == '*')
	{
		*format = *format + 1;
		return (va_arg(argu, int));
	}
	if (!((int)**format >= '0' && (int)**format <= '9'))
		return (0);
	while ((int)**format >= '0' && (int)**format <= '9')
	{
		i = i * 10 + ((int)**format - 48);
		*format = *format + 1;
	}
	return (i);
}

t_param	ft_checkprecision(t_param param, va_list argu, const char **format)
{
	if (**format == '.')
	{
		*format = *format + 1;
		param.precision = ft_checknbr(argu, format);
	}
	return (param);
}

t_param	ft_checkconvert(t_param param, char format, char *converts)
{
	while (*converts)
	{
		if (*converts == format)
			param.convert = format;
		converts++;
	}
	if (param.convert == 0)
		param.error++;
	if (ft_strrchr("C", param.convert))
		param.convert = ft_tolower(param.convert);
	return (param);
}
