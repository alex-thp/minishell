/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:12:07 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 21:12:09 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd_in(t_in_list *list)
{
	t_in_list	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (open(tmp->filename, O_RDONLY));
}

int	get_fd_out(char *filename, int append)
{
	if (!append)
		return (open(filename, O_CREAT | O_RDWR | O_TRUNC, 00664));
	return (open(filename, O_CREAT | O_RDWR | O_APPEND, 00664));
}

int	get_nb_words(char *command)
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

int	get_word_length(char *command, int i)
{
	int		size;

	size = 0;
	while (command[i + size] && command[i + size] != ' ')
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

char	*get_the_word(char *command, int *index)
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
