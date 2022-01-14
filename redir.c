/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:16:50 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/14 23:04:57 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_here_doc_name(t_datas *datas)
{
	char	*filename;
	char	*num;

	if (datas->here_doc_limit == 15)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		return (NULL);
	}
	filename = (char *)ft_calloc(sizeof(char *), 27);
	filename = ft_strcat(filename, "/tmp/here_doc_minishell_");
	num = ft_itoa(datas->here_doc_limit);
	filename = ft_strcat(filename, num);
	free(num);
	datas->here_doc_limit++;
	return (filename);
}

char	*here_doc(char *stop, t_datas *datas)
{
	char	*doc;
	char	*name;
	int		len_stop;
	int		fd;

	doc = NULL;
	len_stop = ft_strlen(stop);
	if (!len_stop)
	{	
		_variable = 2;
		ft_putstr_fd("minishell: syntax error\n",2);
		return (NULL);
	}
	name = get_here_doc_name(datas);
	if (name == NULL)
		return (NULL);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 00664);
	while (1)
	{
		doc = readline("> ");
		if (!doc)
		{
			ft_putstr_fd("bash: warning: here-document ", 2);
			ft_putstr_fd("delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(stop, 2);
			ft_putstr_fd("\')\n", 2);
			free(name);
			return (NULL);
		
		}
		if (ft_memcmp(doc, stop, len_stop + 1))
		{
			ft_putstr_fd(doc, fd);
			ft_putstr_fd("\n", fd);
			free(doc);
		}
		else
		{
			free(doc);
			close(fd);
			return (name);
		}
	}
	if (name)
		free(name);
	return (NULL);
}

t_in_list	*add_in_list(t_in_list *list, char *filename)
{
	t_in_list	*tmp;
	t_in_list	*ptr;
	
	tmp = malloc(sizeof(*tmp));
	tmp->fd = 0;
	tmp->filename = filename;
	tmp->next = NULL;
	if (list == NULL)
		return (tmp);
	ptr = list;
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = tmp;
	return (list);
}

t_in_list	*init_in_list(char *command, t_in_list *list, t_datas *datas)
{
	char	*filename;
	char	*tmp;

	if (command[1] == '<')
	{
		*command = ' ';
		command++;
		tmp = get_value2(command, 0);
		filename = here_doc(tmp, datas);
		free(tmp);
		if (filename == NULL)
			return (free_in_list(list));
		list = add_in_list(list, filename);
	}
	else
	{
		filename = get_value2(command, 0);
		if (!filename)
		{
			_variable = 2;
			ft_putstr_fd("minishell: syntax error\n",2);
			return (free_in_list(list));
		}
		list = add_in_list(list, filename);
	}
	return (list);
}

t_redirection	*create_output(char *command, t_redirection *redir)
{
	int		fd;

	if (command[1] == '>')
	{
		*command = ' ';
		command++;
		if (redir->file_out)
			free(redir->file_out);
		redir->file_out = get_value2(command, 0);
		redir->append = 1;
		fd = open(redir->file_out, O_CREAT | O_RDWR | O_APPEND, 00664);
	}
	else
	{
		if (redir->file_out)
			free(redir->file_out);
		redir->file_out = get_value2(command, 0);
		redir->append = 0;
		fd = open(redir->file_out, O_CREAT | O_RDWR | O_TRUNC, 00664);
	}
	if (fd < 0)
	{
		_variable = 2;
		ft_putstr_fd("minishell: syntax error\n",2);
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
