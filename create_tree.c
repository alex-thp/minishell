/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:10:11 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 21:17:39 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_spaces(char *command)
{
	char	**result;
	int		i;
	int		j;
	int		index;

	while (*command == ' ')
		command++;
	index = 0;
	i = get_nb_words(command);
	result = malloc(sizeof(char *) * (i + 1));
	result[i] = NULL;
	j = 0;
	while (j < i)
	{
		result[j] = get_the_word(command, &index);
		if (result[j])
			result[j] = erase_quotes(result[j]);
		index++;
		j++;
	}
	return (result);
}

t_command	*create_cmd(char *command)
{
	t_command	*cmd;
	char		**args;

	cmd = (t_command *)malloc(sizeof(t_command));
	args = ft_split_spaces(command);
	if (args)
	{
		cmd->name = args[0];
		cmd->args = args;
	}
	return (cmd);
}

t_node	*init_node(t_node *node, int is_builtins)
{
	if (node->redir->in_list)
		node->redir->fd_in = get_fd_in(node->redir->in_list);
	if (node->redir->file_out)
		node->redir->fd_out = get_fd_out(node->redir->file_out,
				node->redir->append);
	if (!node->cmd)
		node->cmd = create_cmd(node->line);
	if (!is_builtins)
	{
		if (node->redir->fd_out >= 0)
			dup2(node->redir->fd_out, STDOUT_FILENO);
		if (node->redir->fd_in >= 0)
			dup2(node->redir->fd_in, STDIN_FILENO);
	}
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
