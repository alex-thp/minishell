/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:15:38 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/18 18:52:33 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_execve(char *name)
{
	int		i;
	char	*tab[7];

	tab[0] = "cd";
	tab[1] = "pwd";
	tab[2] = "echo";
	tab[3] = "unset";
	tab[4] = "export";
	tab[5] = "env";
	tab[6] = "exit";
	i = 0;
	if (!name)
		return (-1);
	while (i < 7)
	{
		if (ft_strncmp(tab[i], name, ft_strlen(tab[i]) + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_this_one(int i, t_node *head, t_datas *datas)
{
	if (i == 0)
		return (ft_cd(head->cmd->args, datas));
	else if (i == 1)
		return (ft_pwd(head, datas->env));
	else if (i == 2)
		return (ft_echo(head->cmd->args, head));
	else if (i == 3)
		return (ft_unset(datas->env, head->cmd->args[1]));
	else if (i == 4)
		return (ft_export(&datas->env, &datas->len_env, head->cmd->args[1]));
	else if (i == 5)
		return (ft_env(datas->env, head));
	else if (i == 6)
		return (ft_exit(datas, head));
	return (-1);
}

int	exec_builtin(t_node *head, t_datas *datas)
{
	int		i;
	char	*tab[7];

	tab[0] = "cd";
	tab[1] = "pwd";
	tab[2] = "echo";
	tab[3] = "unset";
	tab[4] = "export";
	tab[5] = "env";
	tab[6] = "exit";
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(head->cmd->name, tab[i], ft_strlen(tab[i]) + 1) == 0)
			return (exec_this_one(i, head, datas));
		i++;
	}
	return (-1);
}
