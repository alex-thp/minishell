/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_in_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:03:26 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/01 19:09:37 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_add_in_tab(char **tab, char *str)
{
	char	**new;
	int		len_tab;
	int		i;

	len_tab = ft_tablen(tab);
	i = 0;
	new = ft_calloc(sizeof(char *), len_tab + 2);
	while (i < len_tab)
	{
		new[i] = tab[i];
		i++;
	}
	new[i] = ft_strdup(str);
	return (new);
}
