/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:14:03 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/03 16:18:19 by adylewsk         ###   ########.fr       */
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

void	ft_echo(char **strs)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (strs && strs[i])
	{
		while (strs[i] && check_option_n(strs[i]) == 1)
		{
			option = 1;
			i++;
		}
		while (strs[i])
		{
			printf("%s ", strs[i]);
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

int		ft_cd(char **args, t_datas *datas)
{
	int		result;
	char	*buff;
	char	*tmp;

	result = 0;
	if(args)
	{
		buff = getcwd(NULL, 0);
		tmp = ft_strjoin("OLDPWD=", buff);
		modify_env("OLDPWD=", tmp, datas);
		free(buff);
		if (args[1])
			result = chdir(args[1]);
		else
			result = go_home(datas);
		buff = getcwd(NULL, 0);
		tmp = ft_strjoin("PWD=", buff);
//		printf("PWD = |%s|", buff);
		modify_env("PWD=", tmp, datas);
		free(buff);
	}
	return (result);
}

void	ft_env(char **env)
{
	int		i;
	char	*index;

	i = 0;
	while (env[i])
	{
		index = NULL;
		index = ft_strchr(env[i], '=');
		if (index)
			printf("%s\n", env[i]);
		i++;
	}
}

void	ft_exit(t_datas *datas, t_node *head)
{
	ft_putstr("exit\n");
	if (head->cmd->args[1])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(datas->head->cmd->args[1], 2);
		ft_putstr_fd(": no argument required\n", 2);
	}
	free_tree(datas->head);
	ft_freetab(datas->env);
	free(datas->command);
	free(datas);
	exit(0);
}
