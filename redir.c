/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:16:50 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/12 20:57:56 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_here_doc_name(t_datas *datas)
{
	char	*filename;
	char	*num;

	filename = (char *)ft_calloc(sizeof(char *), 27);
	filename = ft_strcat(filename, "/tmp/here_doc_minishell_");
	num = ft_itoa(datas->here_doc_limit);
	filename = ft_strcat(filename, num);
	free(num);
	datas->here_doc_limit--;
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
		return (NULL);
	name = get_here_doc_name(datas);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 00664);
	while (1)
	{
		doc = readline("> ");
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

t_input_list	*add_input_list(t_input_list *list, char *filename)
{
	t_input_list	*tmp;
	t_input_list	*ptr;
	
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
	return (ptr);
}

t_input_list	*init_input_list(char *command, t_datas *datas)
{
	char	*filename;
	char	*tmp;
	int	i;
	t_input_list	*list;

	i = 0;
	list = NULL;
	while (command && command[i])
	{
		if (command[i] == '"' || command[i] == '\'')
			i += ft_closed_quote(command + i);
		else
		{
			if (command[i] == '<')
			{ 
				if (command[i + 1] == '<')
				{
					command[i] = ' ';
					i++;
					tmp = get_value2(command, i);
					filename = here_doc(tmp, datas);
					free(tmp);
					list = add_input_list(list, filename);
					printf("here : %s\n", filename);
				}
				else
				{
					filename = get_value2(command, i);
					list = add_input_list(list, filename);
					printf("in : %s\n", filename);
				}
			}
		}
		i++;
	}
	return (list);
}

t_redirection	*init_redir(char *command, t_datas *datas)
{
	t_redirection	*redir;

	if (!command)
		return (NULL);
	redir = (t_redirection *)malloc(sizeof(t_redirection));
	redir->fd_in = -2;
	redir->fd_out = -2;
	redir->input_list = init_input_list(command, datas);
	return (redir);
}

t_node	*get_redir_tree(t_node *head, t_datas *datas)
{
	if (head->right)
	{
		get_redir_tree(head->left, datas);
		printf("%s\n", head->right->line);
		head->right->redir = init_redir(head->right->line, datas);
	}
	else
	{
		printf("%s\n", head->line);
		head->redir = init_redir(head->line, datas);
	}
	return (head);	
}
