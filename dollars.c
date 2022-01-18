/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:14:54 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/18 20:02:51 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_finished(char *str, int i)
{
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == 0)
		return (-1);
	return (i);
}

char	*add_variable_to_str(char *result, int i, t_datas *datas)
{
	char	*str;
	char	*tmp;
	int		j;

	tmp = interpret_dollar(&result[i + 1], datas);
	if (!tmp)
		return (result);
	str = malloc(sizeof(char) * (ft_strlen(result) + ft_strlen(tmp)) + 1);
	j = -1;
	while (++j < i)
		str[j] = result[j];
	i = -1;
	while (tmp[++i])
		str[j + i] = tmp[i];
	i += j;
	while (result[j] && result[j] != ' ' && result[j] != '"')
		j++;
	while (result[j])
		str[i++] = result[j++];
	str[i] = 0;
	free(result);
	return (str);
}

char	*add_return_code(char *str, int i)
{
	int		j;
	int		k;
	char	*result;
	char	*tmp;

	j = -1;
	tmp = ft_itoa(g_variable);
	result = ft_calloc(ft_strlen(str) + ft_strlen(tmp) + 1, sizeof(char));
	while (++j < i)
		result[j] = str[j];
	k = -1;
	j -= 1;
	while (tmp[++k])
		result[++j] = tmp[k];
	i += 1;
	j += 1;
	while (str[++i])
	{
		result[j] = str[i];
		j++;
	}
	free(str);
	free(tmp);
	return (result);
}

char	*change_dollar(t_datas *datas, char *result, int i)
{
	if (result[i] == '$')
	{
		if (result[i + 1] == '?')
			result = add_return_code(result, i);
		else
			result = add_variable_to_str(result, i, datas);
	}
	return (result);
}

char	*dollar_interpretation(char *str, t_datas *datas)
{
	int		i;
	char	*result;

	i = 0;
	result = str;
	while (result[i])
	{
		while (result[i] && result[i] != '\'')
		{
			result = change_dollar(datas, result, i);
			i++;
		}
		if (result[i] == '\'')
		{
			i++;
			if (is_finished(result, i) != -1)
				i = is_finished(result, i);
			else
				return (result);
			i++;
		}
	}
	return (result);
}
