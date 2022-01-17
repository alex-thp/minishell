/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:15:54 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 21:15:56 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir(int fd, char *command, t_redirection *redir, int append)
{
	if (redir->file_out)
		free(redir->file_out);
	redir->file_out = get_value2(command);
	redir->append = append;
	if (append == 1)
		fd = open(redir->file_out, O_CREAT | O_RDWR | O_APPEND, 00664);
	else
		fd = open(redir->file_out, O_CREAT | O_RDWR | O_TRUNC, 00664);
	return (fd);
}

t_redirection	*create_output(char *command, t_redirection *redir)
{
	int		fd;

	fd = 0;
	if (command[1] == '>')
	{
		*command = ' ';
		command++;
		fd = open_redir(fd, command, redir, 1);
	}
	else
		fd = open_redir(fd, command, redir, 0);
	if (fd < 0)
	{
		g_variable = 2;
		ft_putstr_fd("minishell: syntax error\n", 2);
	}
	close(fd);
	return (redir);
}

t_redirection	*get_redir(char	*command, t_redirection *redir, t_datas *datas)
{
	int			i;
	t_in_list	*list;

	i = 0;
	while (command && command[i])
	{
		if (command[i] == '"' || command[i] == '\'')
			i += ft_closed_quote(command + i);
		else if (command[i] == '<')
		{
			list = init_in_list(command + i, redir->in_list, datas);
			if (list == NULL)
				return (free_redir(redir));
			redir->in_list = list;
		}
		else if (command[i] == '>')
		{
			redir = create_output(command + i, redir);
			if (!redir->file_out)
				return (free_redir(redir));
		}
		i++;
	}
	return (redir);
}

t_redirection	*init_redir(char *command, t_datas *datas)
{
	t_redirection	*redir;

	if (!command)
		return (NULL);
	redir = (t_redirection *)ft_calloc(1, sizeof(t_redirection));
	redir->fd_in = -2;
	redir->fd_out = -2;
	redir->append = 0;
	redir->file_out = NULL;
	redir->in_list = NULL;
	redir = get_redir(command, redir, datas);
	return (redir);
}

t_node	*get_redir_tree(t_node *head, t_datas *datas)
{
	if (!head->line)
	{
		if (!get_redir_tree(head->left, datas))
			return (NULL);
		head->right->redir = init_redir(head->right->line, datas);
		if (!head->right->redir)
			return (NULL);
		return (head);
	}
	else
		head->redir = init_redir(head->line, datas);
	if (!head->redir)
		return (NULL);
	return (head);
}
