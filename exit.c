/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:00:12 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/12 21:06:26 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_input_list(t_input_list *list)
{
	if (list->next)
	{
		free_input_list(list->next);
	}
	if (list->filename)
		free(list->filename);
	free(list);
}

void	free_node(t_node *node)
{
	if (node)
	{
		if (node->cmd)
		{
			if (node->cmd->args)
				ft_freetab(node->cmd->args);
			free(node->cmd);
		}
		if (node->redir)
		{
			if (node->redir->input_list)
				free_input_list(node->redir->input_list);
			free(node->redir);
		}
		free(node);
	}
}

void	free_tree(t_node *head)
{
	if (head && head->left)
	{
		free_node(head->right);
		free_tree(head->left);
	}
	free_node(head);
}
