/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:39:30 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/10 22:29:53 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_name(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*get_name(char *env)
{
	int		i;
	int		j;
	char	*name;

	i = get_size_name(env);
	j = 0;
	name = ft_calloc(i, sizeof(char));
	while (j < i)
	{
		name[j] = env[j];
		j++;
	}
	return (name);
}

char	*get_value(char *env)
{
	int		i;
	int		j;
	char	*value;

	j = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	while (env[i + j])
		j++;
	value = malloc(sizeof(char) * j);
	value[j - 1] = 0;
	j = 0;
	while (env[i + j])
	{
		value[j] = env[i + j];
		j++;
	}
	return (value);
}

int	get_envindex(char **env, char *var)
{
	int	i;
	int	len_var;

	i = 0;
	len_var = ft_strlen(var);
	while (env[i])
	{
		if (!ft_memcmp(env[i], var, len_var)
			&& (env[i][len_var] == '='))
			return (i);
		i++;
	}
	return (-1);
}

char	**envp_to_alloc_tab(char **envp, int *len_env)
{
	char	**new;
	int		i;

	*len_env = ft_tablen(envp);
	new = ft_calloc(*len_env + 1, sizeof(char *));
	i = 0;
	while (i < *len_env)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new);
}

int	change_env_value(char **env, char *var)
{
	char	*name;
	int		index;

	name = get_name(var);
	index = get_envindex(env, name);
	free(name);
	if (index != -1)
	{
		free(env[index]);
		env[index] = ft_strdup(var);
		return (1);
	}
	return (0);
}
