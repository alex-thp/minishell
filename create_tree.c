/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/10 15:58:15 by adylewsk         ###   ########.fr       */
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
	redir->stdin = -2;
	redir->stdout = -2;
	redir->stdin_file = NULL;
	i = 0;
	while (command[i] != 0)
	{
		if (command[i] == '<' || command[i] == '>' )
		{
			if (command[i] == '<')
			{
				if (redir->stdin_file)
					free(redir->stdin_file);
				redir->stdin_file = get_value2(command, i);
			}
			else if (command[i] == '>')
			{
				to_open = get_value2(command, i);
				fd = open(to_open, O_CREAT | O_RDWR | O_TRUNC, 00664);
				free(to_open);
				redir->stdout = fd;
			}
		}
		i++;
	}
	return (redir);
}

t_command		*create_cmd(char *command)
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

t_node			*create_node_command(char *command)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->redir = create_redir(command);
	node->cmd = create_cmd(command);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node			*create_node_pipe(void)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	node->redir = NULL;
	node->cmd = create_cmd("pipe");
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node			*create_tree(char **command)
{
	int		i;
	t_node	*head;
	t_node	*tmp;

	i = 0;
	while(command[i])
		i++;
	tmp = create_node_pipe();
	head = tmp;
	i--;
	while (i > 0)
	{
		tmp->right = create_node_command(command[i]);
		if (i != 1)
			tmp->left = create_node_pipe();
		else{
			tmp->left = create_node_command(command[i - 1]);
		}
		tmp = tmp->left;
		i--;
	}
	return (head);
}
