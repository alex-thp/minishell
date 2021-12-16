/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:14:03 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/16 17:25:44 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(char **env, char *var)
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

int		ft_export(char ***env, int *len_env, char *var)
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

int		check_option_n(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
	}
	return (((size_t)i == ft_strlen(str)) ? 1 : 0);
}

void	ft_echo(char **strs)
{
	int		i;
	int		option;

	i = 0;
	option = 0;
	if(strs)
	{
		while (strs[i] && check_option_n(strs[i]) == 1)
		{
			option = 1;
			i++;
		}
		while (strs[i])
		{
			printf("%s", strs[i]);
			i++;
		}
		if (option == 0)
			printf("\n");
	}
}

void	ft_pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	printf("%s\n", buff);
	if (buff)
		free(buff);
}
