/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:09:39 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 21:17:32 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_eof_heredoc(int fd, char *stop, char *doc)
{
	if (!doc)
	{
		ft_putstr_fd("bash: warning: here-document ", 2);
		ft_putstr_fd("delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(stop, 2);
		ft_putstr_fd("\')\n", 2);
		close(fd);
		exit(0);
	}
}

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

void	fork_here_doc(char *name, char *stop)
{
	int		fd;
	char	*doc;

	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 00664);
	signal(SIGINT, &ft_sighere);
	signal(SIGQUIT, &ft_sigquithere);
	free(name);
	while (1)
	{
		doc = readline("> ");
		ft_eof_heredoc(fd, stop, doc);
		if (ft_memcmp(doc, stop, ft_strlen(stop) + 1))
		{
			ft_putstr_fd(doc, fd);
			ft_putstr_fd("\n", fd);
			free(doc);
		}
		else
		{
			free(doc);
			close(fd);
			exit(0);
		}
	}
}

char	*here_doc(char *stop, t_datas *datas)
{
	char	*name;
	int		pid;
	int		result;

	result = 0;
	if (!ft_strlen(stop))
	{	
		g_variable = 2;
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (NULL);
	}
	name = get_here_doc_name(datas);
	if (name == NULL)
		return (NULL);
	pid = fork();
	if (!pid)
		fork_here_doc(name, stop);
	result = ft_wait(pid);
	if (result != 0)
	{
		free(name);
		g_variable = result;
		return (NULL);
	}
	return (name);
}
