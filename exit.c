/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:00:12 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/16 18:14:54 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_node *node)
{
	if (node)
	{
		if (node->cmd)
		{
			ft_freetab(node->cmd->args);
			free(node->cmd);
		}
		if (node->redir)
			free(node->redir);
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
