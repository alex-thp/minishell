/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:20:12 by alex              #+#    #+#             */
/*   Updated: 2022/01/17 16:29:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait(int pid)
{
	int	status;
	int	result;

	status = 0;
	result = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
			write(2, "(core dumped)\n", 14);
		result = WTERMSIG(status);
		result += 128;
	}
	return (result);
}

int	ft_look2(char *str, int i, char type)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != type)
		j++;
	if (str[i + j] != 0)
		return (j);
	return (-1);
}

int	ft_look(char *str, int i, char type)
{
	i++;
	while (str[i] && str[i] != type)
		i++;
	if (str[i] != 0)
		return (i);
	return (-1);
}
