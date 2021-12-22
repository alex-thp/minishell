/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:28:17 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/22 18:43:42 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	child(int *pip, t_node *head, t_datas *datas)
{
	char	*cmd;

	cmd= NULL;
	waitpid(-1, NULL, 0);
//	ft_putstr_fd(head->line, 2);
	head->redir = create_redir(head->line);
	head->cmd = create_cmd(head->line);
	if (head->redir->fd_out >= 0)
		dup2(head->redir->fd_out, STDOUT_FILENO);
	if (head->redir->fd_in >= 0)
		dup2(head->redir->fd_in, STDIN_FILENO);
	dup2(pip[0], STDIN_FILENO);
	close(pip[1]);
//	waitpid(-1, NULL, 0);
	cmd = check_exe(head->cmd->name, datas->env);
	if (is_execve(head->cmd->name) == -1)
		execve(cmd, head->cmd->args, datas->env);
	else if (exec_builtin(head, datas) == 0)
		printf("%s: command not found\n", head->cmd->name);
	free(cmd);
	exit(0);
}

void	first(t_node *head, t_datas *datas)
{
	char	*cmd;

	cmd= NULL;
	waitpid(-1, NULL, 0);
//	ft_putstr_fd(head->line, 2);
	head->redir = create_redir(head->line);
	head->cmd = create_cmd(head->line);
	if (head->redir->fd_out >= 0)
		dup2(head->redir->fd_out, STDOUT_FILENO);
	if (head->redir->fd_in >= 0)
		dup2(head->redir->fd_in, STDIN_FILENO);
	cmd = check_exe(head->cmd->name, datas->env);
	if (is_execve(head->cmd->name) == -1)
		execve(cmd, head->cmd->args, datas->env);
	else if (exec_builtin(head, datas) == 0)
		printf("%s: command not found\n", head->cmd->name);
	free(cmd);
	exit(0);
}

void	execute_tree(t_node *head, t_datas *datas)
{
	int		pip[2];
	int		pid;

	pipe(pip);
	pid = 0;
	if (!head->line)
	{
		pid = fork();
		if (pid == 0)
			child(pip, head->right, datas);
		else
			parent(pip, head, datas);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			first(head, datas);
		waitpid(pid, NULL, 0);
	}
	dup2(STDOUT_FILENO, pip[1]);
	dup2(STDIN_FILENO, pip[0]);
	close(pip[0]);
	close(pip[1]);
//	waitpid(-1, NULL, 0);
}

int	interpret_command(char *command, t_datas *datas)
{
	char	**parsed_command;
	int		pid;

	pid = 0;
	parsed_command = lexer(command);
	if (parsed_command == NULL)
		return (0);
	if (parsed_command[1])
	{
		datas->head = create_tree(parsed_command);
		execute_tree(datas->head, datas);
		waitpid(-1, NULL, 0);
	}
	else
	{
		datas->head = create_node(command);
		datas->head->redir = create_redir(datas->head->line);
		datas->head->cmd = create_cmd(datas->head->line);
		if (is_execve(datas->head->cmd->name) == -1)
		{
			pid = fork();
			if (pid == 0)
				first(datas->head, datas);
			waitpid(pid, NULL, 0);
		}
		else
			exec_builtin(datas->head, datas);
	}
	ft_freetab(parsed_command);
	return (1);
}
