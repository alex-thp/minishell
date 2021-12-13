/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:35:25 by adylewsk          #+#    #+#             */
/*   Updated: 2021/06/28 19:09:29 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_findchar(char *str, char c)
{
	while (*str && *str != c)
		str++;
	if (*str == c)
		return (1);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1 && !s2)
		return (str = malloc(sizeof(char)));
	i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && *s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = 0;
	free(s1);
	return (str);
}

int	ft_firstline(char **save, char **line)
{
	size_t	i;
	int		end;
	char	*tmp;

	i = 0;
	end = ft_findchar(*save, '\n');
	if (**save == 0)
	{
		*line = malloc(sizeof(char));
		**line = 0;
		return (0);
	}
	while (*(*save + i) && *(*save + i) != '\n')
		i++;
	*line = ft_substr(*save, 0, i);
	tmp = ft_substr(*save, i + 1, ft_strlen(*save) - i - 1);
	free(*save);
	*save = tmp;
	return (end);
}

int	ft_readfile(int fd, char **save)
{
	char	*buffer;
	ssize_t	i;

	i = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (-1);
	*buffer = 0;
	while (i > 0 && !ft_findchar(buffer, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			free(buffer);
			return (-1);
		}
		buffer[i] = 0;
		*save = ft_strjoin_gnl(*save, buffer);
	}
	free(buffer);
	if (i > 0)
		return (1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*save = NULL;
	int			end;

	end = 0;
	*line = NULL;
	if (save && ft_findchar(save, '\n'))
	{
		ft_firstline(&save, line);
		return (1);
	}
	end = ft_readfile(fd, &save);
	if (end == -1)
	{
		*line = malloc(sizeof(char));
		**line = 0;
		return (-1);
	}
	ft_firstline(&save, line);
	if (end == 0)
	{
		free(save);
		save = 0;
	}
	return (end);
}
