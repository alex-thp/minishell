/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:00:12 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 21:05:55 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_in_list	*free_in_list(t_in_list *list)
{
	if (list)
	{
		if (list->next)
			free_in_list(list->next);
		if (list->filename)
			free(list->filename);
		free(list);
	}
	list = NULL;
	return (list);
}

t_redirection	*free_redir(t_redirection *redir)
{
	if (redir)
	{
		if (redir->file_out)
			free(redir->file_out);
		if (redir->in_list)
			free_in_list(redir->in_list);
		free(redir);
	}
	redir = NULL;
	return (redir);
}

t_node	*free_node(t_node *node)
{
	if (node)
	{
		if (node->cmd)
		{
			if (node->cmd->args)
				ft_freetab(node->cmd->args);
			free(node->cmd);
		}
		free_redir(node->redir);
		free(node);
	}
	node = NULL;
	return (node);
}

void	free_tree(t_node *head)
{
	if (head && head->left)
	{
		free_node(head->right);
		free_tree(head->left);
	}
	free_node(head);
	head = NULL;
}
