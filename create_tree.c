/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/10 16:55:21 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*create_redir(char *command)
{
	int				i;
	int				fd;
	t_redirection	*redir;
	char			*to_open;

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	redir->fd_in = -2;
	redir->fd_out = -2;
	i = 0;
	while (command[i] != 0)
	{
		if (command[i] == '<')
		{
			if (redir->fd_in)
				close(redir->fd_in);
			to_open = get_value2(command, i);
			fd = open(to_open, O_RDONLY);
			free(to_open); 
			redir->fd_in = fd;
		}
		else if (command[i] == '>')
		{
			if (command[i + 1] == '>')
			{
				command[i] = ' ';
				i++;
				to_open = get_value2(command, i);
				fd = open(to_open, O_CREAT | O_RDWR | O_APPEND, 00664);
			}
			else
			{
				to_open = get_value2(command, i);
				fd = open(to_open, O_CREAT | O_RDWR | O_TRUNC, 00664);
			}
			free(to_open);
			redir->fd_out = fd;
		}
		i++;
	}
	return (redir);
}

t_command	*create_cmd(char *command)
{
	t_command	*cmd;
	char		**args;

	cmd = (t_command *)malloc(sizeof(t_command));
	args = ft_split(command, ' ');
	if (args)
	{
		cmd->name = args[0];
		cmd->args = args;
	}
	return (cmd);
}

t_node	*init_node(t_node *node)
{
	if (!node->redir)
		node->redir = create_redir(node->line);
	if (!node->cmd)
		node->cmd = create_cmd(node->line);
	if (node->redir->fd_out >= 0)
		dup2(node->redir->fd_out, STDOUT_FILENO);
	if (node->redir->fd_in >= 0)
		dup2(node->redir->fd_in, STDIN_FILENO);
	return (node);
}

t_node	*create_node(char *command)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->line = command;
	node->redir = NULL;
	node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*create_tree(char **command)
{
	int		i;
	t_node	*head;
	t_node	*tmp;

	i = 0;
	while (command[i])
		i++;
	tmp = create_node(NULL);
	head = tmp;
	i--;
	while (i > 0)
	{
		tmp->right = create_node(command[i]);
		if (i != 1)
			tmp->left = create_node(NULL);
		else
			tmp->left = create_node(command[i - 1]);
		tmp = tmp->left;
		i--;
	}
	return (head);
}
