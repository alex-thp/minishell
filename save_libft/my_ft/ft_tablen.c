/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:42:51 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/03 00:15:19 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_tablen(char **tab)
{
	size_t	len;

	len = 0;
	if (tab == NULL)
		return (FALSE);
	while (tab[len])
		len++;
	return (len);
}
