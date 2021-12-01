/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:46:10 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 00:18:59 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include "../../libft.h"
# include "../../macro.h"
# include "printfstruct.h"

int		ft_print_str(t_param *param, char *str);
int		ft_print_ptr(t_param *param, char *str);
int		ft_print_nbr(t_param *param, char *str);
int		ft_reput(char flag, int nbr);
int		ft_print_champ(t_param *param, char *str);
int		ft_toggle_flag(t_param param, char *str, int len);
char	*ft_uitoa(unsigned int ui);
int		ft_convert_to_fonc(t_param param, va_list argu);
char	*ft_convert_to_base(char convert);
char	*ft_itoa_base(long nbr, char *base);
int		ft_char_convert(t_param param, va_list argu);
int		ft_str_convert(t_param param, va_list argu);
int		ft_unsigned_convert(t_param param, va_list argu);
int		ft_base_convert(t_param param, va_list argu);
int		ft_ptr_convert(t_param param, va_list argu);
int		ft_formated_len(t_param param, char *str);
long	ft_pow(long nbr, long exp);
t_param	ft_checkprecision(t_param param, va_list argu, const char **format);
t_param	ft_format_to_param(t_param param, va_list argu, const char **format);
t_param	ft_checkflag(t_param param, const char **str);
t_param	ft_checkconvert(t_param param, char format, char *converts);
int		ft_checknbr(va_list argu, const char **str);

#endif
