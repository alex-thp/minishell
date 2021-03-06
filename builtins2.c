/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:07:41 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/18 21:09:10 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_builtins(t_node *head)
{
	if (head->redir->fd_out == -2)
		return (STDOUT_FILENO);
	return (head->redir->fd_out);
}

int	ft_cd(char **args, t_datas *datas)
{
	int		result;
	char	*buff;
	char	*tmp;

	result = 0;
	if (args)
	{
		if (!ft_check_dir(args))
			return (0);
		buff = getcwd(NULL, 0);
		tmp = ft_strjoin("OLDPWD=", buff);
		modify_env("OLDPWD=", tmp, datas);
		free(tmp);
		free(buff);
		if (args[1])
			result = chdir(args[1]);
		else
			result = go_home(datas);
		buff = getcwd(NULL, 0);
		tmp = ft_strjoin("PWD=", buff);
		modify_env("PWD=", tmp, datas);
		free(tmp);
		free(buff);
	}
	return (result);
}

int	ft_env(char **env, t_node *head)
{
	int		i;
	char	*index;
	int		out;

	i = 0;
	out = redir_builtins(head);
	while (env[i])
	{
		index = NULL;
		index = ft_strchr(env[i], '=');
		if (index)
		{
			ft_putstr_fd(env[i], out);
			ft_putstr_fd("\n", out);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_datas *datas, t_node *head)
{
	unsigned int	value;

	value = 0;
	if (datas->head->left == NULL)
		ft_putstr("exit\n");
	if (head->cmd->args[1])
	{
		if (!ft_strsupint(head->cmd->args[1]))
			value = ft_atoi(head->cmd->args[1]);
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(head->cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			value = 2;
		}
	}
	free_tree(datas->head);
	free(datas->command);
	ft_freetab(datas->env);
	free(datas);
	exit(value);
	return (0);
}
