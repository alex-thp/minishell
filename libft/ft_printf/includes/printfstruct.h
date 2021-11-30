/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfstruct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:11:20 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 19:16:06 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTFSTRUCT_H
# define PRINTFSTRUCT_H

typedef struct s_param
{
	char	flag;
	char	convert;
	int		champ;
	int		precision;
	int		error;
}				t_param;

typedef struct s_map_base
{
	char	convert;
	char	*base;
}				t_map_base;

typedef struct s_map_foncptr
{
	char	convert;
	int		(*fonc_convert)(t_param, va_list);
}				t_map_foncptr;

#endif
