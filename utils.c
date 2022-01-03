/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:18:58 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/03 17:48:19 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_dir(char **args)
{
	DIR	*directory;

	if (!args)
		return (0);
	if (args[1])
	{
		if (args[2])
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			return (0);
		}
		directory = opendir(args[1]);
		if (directory == NULL)
		{	
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (0);
		}
		closedir(directory);
		return (1);
	}
	return (1);
}

int	go_home(t_datas *datas)
{
	char	*home;
	int		result;

	result = 0;
	home = get_value(search_for_home(datas));
	result = chdir(home);
	free(home);
	return (result);
}

char	*search_for_home(t_datas *datas)
{
	int		i;

	i = 0;
	while (ft_strncmp(datas->env[i], "HOME=", 5) != 0)
		i++;
	return (datas->env[i]);
}

void	modify_env(char *to_replace, char *to_insert, t_datas *datas)
{
	int		i;

	i = 0;
	while ((datas->env[i]
			&& ft_strncmp(to_replace, datas->env[i],
				ft_strlen(to_replace)) != 0))
		i++;
	if (datas->env[i])
	{
		free(datas->env[i]);
		datas->env[i] = to_insert;
	}
}

char	*interpret_dollar(char *str, t_datas *datas)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (datas->env[i] && ft_strncmp(datas->env[i], str, ft_strlen(str)) != 0)
		i++;
	while (datas->env[i][j] && datas->env[i][j] != '=')
		j++;
	j++;
	return (&datas->env[i][j]);
}
