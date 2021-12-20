/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:28:17 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/20 19:28:59 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(int *pip, t_node *head, t_datas *datas)
{
	dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	execute_tree(head->left, datas);
	exit(0);
}

void	parent(int *pip, t_node *head, t_datas *datas)
{
	char	*cmd;

	if (head->right->redir->fd_out >= 0)
		dup2(head->right->redir->fd_out, STDOUT_FILENO);
	if (head->right->redir->fd_in >= 0)
		dup2(head->right->redir->fd_in, STDIN_FILENO);
	dup2(pip[0], STDIN_FILENO);
	close(pip[1]);
//	waitpid(-1, NULL, 0);
	cmd = check_exe(head->right->cmd->name, datas->env);
	execve(cmd, head->right->cmd->args, datas->env);
	free(cmd);
	exit(0);
}

void	first(t_node *head, t_datas *datas)
{
	char	*cmd;

	waitpid(-1, NULL, 0);
	if (head->redir->fd_out >= 0)
		dup2(head->redir->fd_out, STDOUT_FILENO);
	if (head->redir->fd_in >= 0)
		dup2(head->redir->fd_in, STDIN_FILENO);
	cmd = check_exe(head->cmd->name, datas->env);
	execve(cmd, head->cmd->args, datas->env);
	free(cmd);
	exit(0);
}

void	execute_tree(t_node *head, t_datas *datas)
{
	int		pip[2];
	int		pid;

	pipe(pip);
	if (!head->cmd->name)
	{
		pid = fork();
		if (pid == 0)
		{
			parent(pip, head, datas);
		}
		else
		{
			child(pip, head, datas);
//			waitpid(-1, NULL, 0);
		}
	}
	else
	{
		pid = fork();
		if (pid == 0)
			first(head, datas);
		waitpid(-1, NULL, 0);
	}
	close(pip[0]);
	close(pip[1]);
	waitpid(-1, NULL, 0);
}

int	interpret_command(char *command, t_datas *datas)
{
	char	**parsed_command;
	int		pid;

	parsed_command = lexer(command);
	if (parsed_command == NULL)
		return (0);
	if (parsed_command[1])
		datas->head = create_tree(parsed_command);
	else
		datas->head = create_node_command(&command[0]);
	pid = fork();
	if (pid == 0)
	{
		execute_tree(datas->head, datas);
//		waitpid(-1, NULL, 0);
	}
	waitpid(-1, NULL, 0);
//	waitpid(pid, NULL, 0); // attendre la fin de tout les processus
	ft_freetab(parsed_command);
	return (1);
}
