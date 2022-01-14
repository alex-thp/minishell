/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:28:17 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/14 00:00:31 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait(int pid)
{
	int	status;
	int result;

	status = 0;
	result = 0;
	waitpid(pid, &status, 0);
	//printf("pid ft_wait = %d\n", getpid());
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
			write(2, "(core dumped)\n", 14);
		result = WTERMSIG(status);
		result += 128;
	}
	//printf("%d\n", result);
	return (result);
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
		exit(0);
	}
	_variable = ft_wait(pid);
}

void	child(int *pip, t_node *head, t_datas *datas)
{
	char	*cmd;
	int		value;

	cmd = NULL;
	value = 0;
	// _variable = ft_wait(value);
	dup2(pip[0], STDIN_FILENO);
	head = init_node(head, 0);
	close(pip[1]);
	if (head->cmd->name && head->redir->fd_in != -1)
	{
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
		_variable = value;
	}
	else
		ft_putstr_fd("parse error\n", 2);
	free(cmd);
	exit(_variable);
}

void	first(t_node *head, t_datas *datas)
{
	char	*cmd;
	int		value;

	cmd = NULL;
	// waitpid(-1, NULL, 0);
	head = init_node(head, 0);
	value = 0;
	if (head->cmd->name && head->redir->fd_in != -1)
	{
		cmd = check_exe(head->cmd->name, datas->env);
		if (is_execve(head->cmd->name) == -1)
		{
			//printf("pid first = %d\n", getpid());
			value = execve(cmd, head->cmd->args, datas->env);
		}
		else
			value = exec_builtin(head, datas);
		if (value == -1)
		{
			ft_putstr_fd(head->cmd->name, 2);
			ft_putstr_fd(": command not found\n", 2);
			free(cmd);
			exit(127);
		}
		_variable = value;
	}
	else
		ft_putstr_fd("parse error\n", 2);
	free(cmd);
	exit(_variable);
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
		parent(pip, head, datas);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			first(head, datas);
		_variable =	ft_wait(pid);
	}
	close(pip[0]);
	close(pip[1]);
}

int	interpret_command(t_datas *datas)
{
	char	**parsed_command;
	int		pid;
	t_node	*tmp;
	struct	sigaction reset;

	pid = 0;
	datas->here_doc_limit = 0;
	reset.sa_handler = ft_sigreset;
	sigaction(SIGINT, &reset, NULL);
	parsed_command = lexer(datas->command, datas);
	if (parsed_command == NULL)
		return (0);
	if (parsed_command[1])
	{
		datas->head = create_tree(parsed_command);
		tmp = get_redir_tree(datas->head, datas);
		if (tmp != NULL)
		{
			datas->head = tmp;
			execute_tree(datas->head, datas);
			ft_wait(0);
		}
	}
	else
	{
		datas->head = create_node(parsed_command[0]);
		tmp = datas->head;
		tmp->redir = init_redir(parsed_command[0], datas);
		if (tmp->redir != NULL)
		{
			datas->head = tmp;
			datas->head->cmd = create_cmd(datas->head->line);
			if (is_execve(datas->head->cmd->name) == -1)
			{
				//printf("pid pere = %d\n", getpid());
				pid = fork();
				if (pid == 0)
				{
					//printf("pid enfant = %d\n", getpid());
					first(datas->head, datas);
				}
				_variable = ft_wait(pid);
			}
			else
			{
				datas->head = init_node(datas->head, 1);
				_variable = exec_builtin(datas->head, datas);
			}
		}
	}
	ft_freetab(parsed_command);
	return (1);
}
