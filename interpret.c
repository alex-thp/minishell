/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:28:17 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/16 17:37:16 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(int *pip, t_node *head, t_datas *datas)
{
	dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	if (head->left)
	execute_tree(head->left, datas);

}

void	parent(int *pip, t_node *head, t_datas *datas)
{
	int		status;

	if (head->redir->fd_out >= 0)
		dup2(head->redir->fd_out, STDOUT_FILENO);
	if (head->redir->fd_in >= 0)
		dup2(head->redir->fd_in, STDIN_FILENO);
	else
		dup2(pip[0], STDIN_FILENO);
	close(pip[1]);
	waitpid(-1, &status, 0);
	execve(check_exe(head->cmd->name, datas->env), head->cmd->args, datas->env);
}

void	execute_tree(t_node *head, t_datas *datas)
{
	int		pip[2];
	int		pid;

	pipe(pip);
	if (!(head->cmd->name)) //PIPE
	{
		pid = fork();
		if (pid == 0)
			child(pip, head, datas);
		else
			parent(pip, head->right, datas);
	}
	else{ //On est arrive a la commande en bas a gauche
		parent(pip, head, datas);
	}
	close(pip[0]);
	close(pip[1]);
}

void	interpret_command(char *command, t_datas *datas)
{
	char	**parsed_command;
	int		pid;

	parsed_command = lexer(command);
	if (parsed_command == NULL)
		return ;
	if (parsed_command[1])
		datas->head = create_tree(parsed_command);
	else
		datas->head = create_node_command(&command[0]);
	pid = fork();
	if (pid == 0)
	{
		execute_tree(datas->head, datas);
		exit(0);
	}
	else{
		waitpid(0, &pid, 0);
	}
}

