/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:11:45 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/19 14:49:10 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_node(t_node *head, t_datas *datas)
{
	int		value;
	char	*cmd;

	value = 0;
	cmd = check_exe(head->cmd->name, datas->env);
	if (is_execve(head->cmd->name) == -1)
		value = execve(cmd, head->cmd->args, datas->env);
	else
		value = exec_builtin(head, datas);
	if (value == -1)
	{
		ft_putstr_fd(head->cmd->name, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(cmd);
		exit(127);
	}
	free(cmd);
	g_variable = value;
}

void	parent(int *pip, t_node *head, t_datas *datas)
{
	int	pid;

	pid = 0;
	close(pip[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pip[1], STDOUT_FILENO);
		execute_tree(head->left, datas);
		exit(g_variable);
	}
	close(pip[1]);
	waitpid(pid, NULL, 0);
}

void	child(int *pip, t_node *head, t_datas *datas)
{
	dup2(pip[0], STDIN_FILENO);
	head = init_node(head, 0);
	close(pip[1]);
	if (head->cmd->name && head->redir->fd_in != -1)
		exec_node(head, datas);
	else
		ft_putstr_fd("permission denied\n", 2);
	exit(g_variable);
}

void	first(t_node *head, t_datas *datas)
{
	head = init_node(head, 0);
	if (head->cmd->name && head->redir->fd_in != -1)
		exec_node(head, datas);
	else
		ft_putstr_fd("permission denied\n", 2);
	exit(g_variable);
}

void	execute_tree(t_node *head, t_datas *datas)
{
	int		pip[2];
	int		pid;

	pipe(pip);
	signal(SIGCHLD, NULL);
	pid = 0;
	if (!head->line)
	{
		pid = fork();
		if (pid == 0)
			child(pip, head->right, datas);
		parent(pip, head, datas);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			first(head, datas);
		g_variable = ft_wait(pid);
	}
	waitpid(-1, NULL, 0);
	close(pip[0]);
	close(pip[1]);
}
