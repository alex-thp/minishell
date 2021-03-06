/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:09:20 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/18 15:04:21 by adylewsk         ###   ########.fr       */
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
	if (!var)
		return (1);
	if (change_env_value(*env, var))
		return (1);
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

int	check_option_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
	}
	if ((size_t)i == ft_strlen(str))
		return (1);
	return (0);
}

int	ft_echo(char **strs, t_node *head)
{
	int	i;
	int	option;
	int	out;

	i = 1;
	option = 0;
	out = redir_builtins(head);
	if (strs && strs[i])
	{
		while (strs[i] && check_option_n(strs[i]) == 1)
		{
			option = 1;
			i++;
		}
		while (strs[i])
		{
			ft_putstr_fd(strs[i], out);
			if (strs[i + 1])
				ft_putstr_fd(" ", out);
			i++;
		}
		if (option == 0)
			ft_putstr_fd("\n", out);
	}
	return (0);
}

int	ft_pwd(t_node *head, char **env)
{
	char	*buff;
	int		out;
	int		envindex;

	out = redir_builtins(head);
	buff = NULL;
	buff = getcwd(NULL, 0);
	if (!buff)
	{
		envindex = get_envindex(env, "PWD");
		if (envindex >= 0)
			buff = get_value(env[envindex]);
	}	
	if (buff)
	{
		if (head->redir->fd_out == -2)
			ft_putstr_fd(buff, 1);
		else
			ft_putstr_fd(buff, out);
		ft_putstr_fd("\n", out);
		free(buff);
	}
	return (0);
}
