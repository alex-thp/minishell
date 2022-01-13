/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:26:48 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/13 23:51:26 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_nb_words(char *command)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			if (ft_look(command, i, command[i]) != -1)
				i = ft_look(command, i, command[i]);
		}
		if (command[i] == ' ' && command[i + 1] != ' ')
			count++;
		i++;
	}
	return (count);
}

int			get_word_length(char *command, int i)
{
	int		size;

	size = 0;
	while(command[i + size] && command[i + size] != ' ')
	{
		if (command[i + size] == '\'' || command[i + size] == '"')
		{
			if (ft_look2(command, i + size, command[i + size]) != -1)
				size += ft_look2(command, i + size, command[i + size]);
		}
		size++;
	}
	return (size);
}

char		*get_the_word(char *command, int *index)
{
	char	*result;
	int		size;
	int		i;

	i = 0;
	while (command[*index] == ' ')
		*index += 1;
	size = get_word_length(command, *index);
	if (!(command[*index]))
		return (NULL);
	result = malloc(sizeof(char) * (size + 1));
	size += *index;
	while (*index < size)
	{
		result[i] = command[*index];
		*index += 1;
		i++;
	}
	result[i] = 0;
	return (result);
}

char		**ft_split_spaces(char *command)
{
	char	**result;
	int		i;
	int		j;
	int		index;

	while (*command == ' ')
		command++;
	index = 0;
	i = get_nb_words(command);
	result = malloc(sizeof(char*) * (i + 1));
	result[i] = NULL;
	j = 0;
	while (j < i)
	{
		result[j] = get_the_word(command, &index);
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

int	get_fd_in(t_in_list *list)
{
	t_in_list	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (open(tmp->filename, O_RDONLY));
}

int	get_fd_out(char *filename, int	append)
{
	if (!append)
		return (open(filename, O_CREAT | O_RDWR | O_TRUNC, 00664));
	return (open(filename, O_CREAT | O_RDWR | O_APPEND, 00664));
}

t_node	*init_node(t_node *node, int is_builtins)
{
	if (node->redir->in_list)
		node->redir->fd_in = get_fd_in(node->redir->in_list);
	if (node->redir->file_out)
		node->redir->fd_out = get_fd_out(node->redir->file_out, node->redir->append);
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
