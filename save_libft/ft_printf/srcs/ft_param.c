/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:25:45 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 13:10:30 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

t_param	ft_init_param(t_param param)
{
	param.flag = 0;
	param.convert = 0;
	param.champ = 0;
	param.precision = -1;
	param.error = 0;
	return (param);
}

t_param	ft_fill_param(t_param param, va_list argu, const char **format)
{
	param = ft_checkflag(param, format);
	param.champ = ft_checknbr(argu, format);
	param = ft_checkprecision(param, argu, format);
	param = ft_checkconvert(param, **format, "cCspdiuxX%");
	if (param.champ < 0)
	{
		param.flag = '-';
		param.champ = -param.champ;
	}
	return (param);
}

t_param	ft_format_to_param(t_param param, va_list argu, const char **format)
{
	*format = *format + 1;
	param = ft_init_param(param);
	param = ft_fill_param(param, argu, format);
	if (ft_strrchr("diuxX", param.convert))
	{
		if (param.precision >= 0 && param.flag == '0')
			param.flag = 0;
	}
	return (param);
}
