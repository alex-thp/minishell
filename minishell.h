/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:18:55 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/30 13:29:34 by adylewsk         ###   ########.fr       */
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
# include "libft/libft.h"
//typedef struct s_ptr_env
//{
//	struct s_env *first;
//	struct s_env *last;
//} t_ptr_env;
//
//typedef struct s_env
//{
//	char			*name;
//	char			*value;
//	struct s_env	*next;
//    struct s_env	*previous;
//}				t_env;

typedef struct s_datas
{
	char		**env;
}				t_datas;

/*
* manage_env.c
*/

t_datas	*manage_env(t_datas *datas);
char	**envp_to_alloc_tab(char **envp);
char	**unset(char **env, int index);
int	get_envindex(char **env, char *var);

/*
* utils.c
*/

char	**ft_split(char const *s, char c);

#endif
