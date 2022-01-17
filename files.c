/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:08:00 by adylewsk          #+#    #+#             */
/*   Updated: 2022/01/17 21:08:03 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_to_path(char *file, char *path)
{
	char	*result;
	int		file_len;
	int		path_len;

	file_len = ft_strlen(file);
	path_len = ft_strlen(path);
	result = malloc(sizeof(char) * (path_len + file_len + 2));
	if (!result)
		return (NULL);
	ft_strcpy(result, path);
	ft_strcpy(result + path_len, "/");
	ft_strcpy(result + path_len + 1, file);
	return (result);
}

char	**env_to_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_memcmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*relative_path(char *file, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (!ft_memcmp(envp[i], "PWD=", 4))
		{
			if (*file == '.' && *(file + 1) == '/')
				path = file_to_path(file + 2, envp[i] + 4);
			else
				path = file_to_path(file, envp[i] + 4);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*absolute_path(char *file, char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = NULL;
	paths = env_to_paths(envp);
	while (paths && paths[i])
	{
		if (path)
			free(path);
		path = file_to_path(file, paths[i]);
		if (!access(path, X_OK))
		{
			ft_freetab(paths);
			return (path);
		}
		i++;
	}
	if (paths)
		ft_freetab(paths);
	if (path)
		free(path);
	return (NULL);
}

char	*check_exe(char *file, char **envp)
{
	if (*file == '/')
		return (ft_strdup(file));
	else if (ft_strchr(file, '/'))
		return (relative_path(file, envp));
	return (absolute_path(file, envp));
}
