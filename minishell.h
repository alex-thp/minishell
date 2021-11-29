/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:18:55 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/26 07:47:07 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_ptr_env
{
	struct s_env *first;
	struct s_env *last;
} t_ptr_env;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
    struct s_env	*previous;
}				t_env;

typedef struct s_datas
{
	t_ptr_env	env;
	char		**base_env;
}				t_datas;

/*
* manage_env.c
*/

t_datas	*manage_env(t_datas *datas);

/*
* utils.c
*/

char	**ft_split(char const *s, char c);

#endif