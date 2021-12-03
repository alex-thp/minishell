/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:14:03 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/03 17:32:12 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **env, char *var)
{
	int		index;
	char	*tmp;

	index = get_envindex(env, var);
	if (index < 0)
		return (0);
	free(env[index]);
	env[index] = NULL;
	index++;
	while (env[index])
	{
		tmp = env[index - 1];
		env[index - 1] = env[index];
		env[index] = tmp;
		index++;
	}
	return (1);
}

int	ft_export(char ***env, int *len_env, char *var)
{
	int		i;
	char	**new;
	char	**tmp;

	tmp = *env;
	i = 0;
	while (tmp[i])
	{
		i++;
	}
	if (i < *len_env)
		tmp[i] = ft_strdup(var);
	else
	{
		new = ft_add_in_tab(tmp, var);
		free(tmp);
		tmp = new;
		*env = tmp;
		*len_env += 1;
	}
	return (1);

}

