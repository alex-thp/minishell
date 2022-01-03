/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:40:59 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/03 17:43:41 by adylewsk         ###   ########.fr       */
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
	while (i < 7)
	{
		if (ft_strncmp(tab[i], name, ft_strlen(tab[i]) + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	exec_this_one(int i, t_node *head, t_datas *datas)
{
	if (i == 0)
		ft_cd(head->cmd->args, datas);
	else if (i == 1)
		ft_pwd();
	else if (i == 2)
		ft_echo(head->cmd->args);
	else if (i == 3)
		ft_unset(datas->env, head->cmd->args[1]);
	else if (i == 4)
		ft_export(&datas->env, &datas->len_env, head->cmd->args[1]);
	else if (i == 5)
		ft_env(datas->env);
	else if (i == 6)
		ft_exit(datas, head);
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
		{
			exec_this_one(i, head, datas);
			return (1);
		}
		i++;
	}
	return (0);
}
