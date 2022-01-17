/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:45:21 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 18:41:23 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_error(char *file, t_in_list *list, int error)
{
	if (!file)
	{
		g_variable = 2;
		if (error)
			ft_putstr_fd("minishell: syntax error\n", 2);
		free_in_list(list);
		return (1);
	}
	return (0);
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
		tmp = get_value2(command);
		filename = here_doc(tmp, datas);
		free(tmp);
		if (ft_list_error(filename, list, 0))
			return (NULL);
		list = add_in_list(list, filename);
	}
	else
	{
		filename = get_value2(command);
		if (ft_list_error(filename, list, 1))
			return (NULL);
		list = add_in_list(list, filename);
	}
	return (list);
}
